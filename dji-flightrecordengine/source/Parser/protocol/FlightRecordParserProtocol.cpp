//
//  FlightRecordParser.cpp
//  FlightRecordEngine
//
//  Copyright © 2017 DJI. All rights reserved.
//

#include <Parser/protocol/FlightRecordParserProtocol.h>
#include <stdio.h>
#include <algorithm>
#include <iostream>
#include <Utils/encryption/FlightRecordEncryptUtils.h>
#include <Utils/Cache/FlightRecordFileCacheUtils.h>
#include <Parser/decoder/flight_record_version_decoder.h>
#include <string.h>
#include <Parser/decryption/flight_record_decryption_layer.hpp>
#include <assert.h>

#define detailInfoEndCheckSum 12345

using namespace DJI::FlightRecord;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//  FlightRecordParserProtocol
//
/////////////////////////////////////////////////////////////////////////////////////////////////////////////

//////////////////////////////// Create / Dealloc ////////////////////////////////
FlightRecordParserProtocol::FlightRecordParserProtocol():
has_detail_buffer_offset_(false),
detail_buffer_offset_({0}),
m_FileReader(nullptr),
m_info(nullptr),
m_prefixInfo(nullptr),
m_isParseInfo(false) {
    
}

FlightRecordParserProtocol::~FlightRecordParserProtocol() {
    all_decoder_.clear();
}

//////////////////////////////// Set Property ////////////////////////////////

void FlightRecordParserProtocol::setFileHandler(std::shared_ptr<FileHandlerUtils> fileHandler) {
    m_FileReader = fileHandler;
}

//////////////////////////////// Get Property ////////////////////////////////

ParserResult FlightRecordParserProtocol::obtainInfo(DJIFlightRecordDetailDataEndStruct &info) {
    if (!m_FileReader) {
        return ParserResult::NoFileHandle;
    }
    
    ParserResult parserInfoResult = parserInfoAndCheck();
    if (parserInfoResult != ParserResult::Success) {
        return parserInfoResult;
    }
    
    if (!m_isParseInfo) {
        return ParserResult::Failure;
    }
    
    if (m_info) {
        info = (*m_info.get());
        
        return ParserResult::Success;
    }
    
    return ParserResult::Failure;
}

ParserResult FlightRecordParserProtocol::obtainVersion(uint8_t &version) {
    if (!m_FileReader) {
        return ParserResult::NoFileHandle;
    }
    
    DJIFlightRecordDetailFilePrefixStruct detailPrefix = {{0}};
    size_t detailPrefixSize = sizeof(DJIFlightRecordDetailFilePrefixStruct);
    m_FileReader->seekFromStart(0);
    if (detailPrefixSize != m_FileReader->read(&detailPrefix, detailPrefixSize)) {
        return ParserResult::ReadFileError;
    }
    
    version = detailPrefix.detailInfoFormatVersion;
    
    return ParserResult::Success;
}

ParserResult FlightRecordParserProtocol::obtainVersionExtension(VersionExtension &version) {
    if (!m_FileReader) {
        return ParserResult::NoFileHandle;
    }
    
    if (!m_FileReader) {
        return ParserResult::NoFileHandle;
    }
    
    version_extension_ = ParseVersion(m_FileReader);
    if (version_extension_.version == VersionCategory::None) {
        return ParserResult::VersionNotSupport;
    }
    
    version = version_extension_;
    
    return ParserResult::Success;
}

//////////////////////////////// Parser Method ////////////////////////////////

void FlightRecordParserProtocol::parseImageData(ParseImageType imageType,
                                                std::function<void (int imageIndex, uint8_t *buffer, long bufferLen)> callBack) {
    if (!callBack) {
        return;
    }
    
    parserInfoAndCheck();
    
    if (!m_isParseInfo) {
        return;
    }
    
    std::shared_ptr<VersionDecoder> suitableDecoder = getDecoderWithVersion(m_prefixInfo->detailInfoFormatVersion, version_extension_.version);
    if (!suitableDecoder) {
        return;
    }
    
    DetailDataMessage encryptMessage;
    if (suitableDecoder->getDetailDataMessage(m_FileReader, encryptMessage) != ParserResult::Success) {
        return;
    }
    
    if (encryptMessage.imagePosition <= 0) {
        return;
    }
    
    switch (imageType) {
        case ParseImageType::Snapshot:
        {
            long snapShotImageOffset = encryptMessage.imagePosition;
            m_FileReader->seekFromStart(snapShotImageOffset);
            for (int i = 0; i < MomentPicNum; i ++) {
                int32_t imageLength = m_info->momentPicImageBufferLen[i];
                
                if (imageLength <= 0) {
                    continue;
                }
                
                uint8_t *buffer = (uint8_t *)malloc(imageLength);
                if (m_FileReader->read(buffer, imageLength) != imageLength) {
                    free(buffer);
                    
                    continue;
                }
                
                callBack(i, buffer, imageLength);
                free(buffer);
            }
        }
            break;
        case ParseImageType::Thumbnail:
        {
            long thumbnailImageOffset = encryptMessage.imagePosition;
            for (int i = 0; i < MomentPicNum; i ++) {
                thumbnailImageOffset += (long)m_info->momentPicImageBufferLen[i];
            }
            
            m_FileReader->seekFromStart(thumbnailImageOffset);
            for (int i = 0; i < MomentPicNum; i ++) {
                int32_t imageLength = m_info->momentPicShrinkImageBufferLen[i];
                
                if (imageLength <= 0) {
                    continue;
                }
                
                uint8_t *buffer = (uint8_t*)malloc(imageLength);
                if (m_FileReader->read(buffer, imageLength) <= 0) {
                    free(buffer);
                    
                    continue;
                }
                
                callBack(i, buffer, imageLength);
                free(buffer);
            }
        }
            break;
            
        default:
            break;
    }
}

ParserResult FlightRecordParserProtocol::parseDetailData(FlightRecordParseDetailDataProtocolLambda callBack) {
    if (!m_FileReader) {
        return ParserResult::NoParser;
    }
    
    if (!callBack) {
        return ParserResult::InvalidParam;
    }
    
    parserInfoAndCheck();
    
    if (!m_prefixInfo) {
        return ParserResult::VerifyFileFailed;
    }
    
    std::shared_ptr<VersionDecoder> suitableDecoder = getDecoderWithVersion(m_prefixInfo->detailInfoFormatVersion, version_extension_.version);
    if (!suitableDecoder) {
        return ParserResult::DecoderNotFound;
    }
    
    DetailDataMessage encryptMessage = {0};
    if (suitableDecoder->getDetailDataMessage(m_FileReader, encryptMessage) != ParserResult::Success) {
        return ParserResult::DecodeFailed;
    }
    
    m_FileReader->seekFromStart(encryptMessage.detailDataHead);

    long maxReadLength = encryptMessage.detailDataTail - encryptMessage.detailDataHead;
    if (encryptMessage.detailDataHead > encryptMessage.detailDataTail) {
        maxReadLength = m_FileReader->m_FileSize;
    }
    
    long cacheLength = maxReadLength;
    std::shared_ptr<FileCacheUtils> tempCacheData = std::make_shared<FileCacheUtils>(m_FileReader, encryptMessage.detailDataHead, cacheLength);
    
    int detailDataLines = 18000;
    if (m_info) {
        detailDataLines = m_info->recordLineCount > 0 ? m_info->recordLineCount : detailDataLines;
    }
    
    detail_buffer_offset_.location = encryptMessage.detailDataHead;
    bool is_stopped_by_user = false;
    
    auto decryption_layer = getDecryptionLayer(version_extension_.version);
    if (!decryption_layer) {
        assert(false && "please use the `addDecryptionLayer` to add the correct decryption layer.");
        return ParserResult::DecoderNotFound;
    }
    decryption_layer->beginParser();
    
    ParserResult result = ParserResult::Success;
    for (int i = 0; i <= detailDataLines;) {
        uint8_t dataType;
        if (tempCacheData->read(&dataType, sizeof(dataType)) < sizeof(dataType)) {
            break;
        }
        
        if (i == detailDataLines && dataType != npzeXkozKlNHPjUQ) {
            break;
        }
        
        auto ciphertext_buf = suitableDecoder->DecodeDetailData(tempCacheData);
        
        if (ciphertext_buf && dataType > 0) {
            if (dataType >= FlightRecordTypeKindNum) {
                assert("Unrecognized data type, find and add it to key_map!");
                continue;
            }
            bool isNeedToStop = false;
            detail_buffer_offset_.length = tempCacheData->m_location;
            
            bool is_parser_success = false;
            
            if (encryptMessage.isMagicEncrypt) {
                if (ciphertext_buf->buffer_length_ <= 2) {
                    result = ParserResult::FileDataContamination;
                    break;
                }
                
                auto dest_buf = std::make_shared<Buffer>(ciphertext_buf->buffer_length_ - 2);
                uint64_t result_len = deEncryptData((uint8_t *)dest_buf->buffer_pointer_,
                                                    (uint8_t *)ciphertext_buf->buffer_pointer_,
                                                    ciphertext_buf->buffer_length_,
                                                    dataType,
                                                    encryptMessage.encryptMagicVersion);
                
                if (result_len == dest_buf->buffer_length_) {
                    auto plaintext = decryption_layer->decryptDetail((FlightRecordDataType)dataType, dest_buf);
                    if (plaintext) {
                        is_parser_success = true;
                        
                        if (callBack) {
                            callBack((FlightRecordDataType)dataType, i, (uint8_t *)plaintext->buffer_pointer_, (uint64_t)plaintext->buffer_length_, &isNeedToStop);
                        }
                    }
                } else {
                    assert("Invalid detail data");
                    std::cout << "decode failure: " << dataType << std::endl;
                }
            } else {
                is_parser_success = true;
                if (callBack) {
                    callBack((FlightRecordDataType)dataType, i, (uint8_t *)ciphertext_buf->buffer_pointer_, (uint64_t)ciphertext_buf->buffer_length_, &isNeedToStop);
                }
            }
            
            if (dataType == OSDFlightRecordDataType && is_parser_success) {
                i ++;
            }
            
            // If outside need to stop, and break it.
            if (isNeedToStop) {
                is_stopped_by_user = true;
                break;
            }
            
            continue;
        }
        
        if (!readUtilLineEnd(tempCacheData)) {
            break;
        } else {
            detail_buffer_offset_.length = tempCacheData->m_location;
        }
    } // for loop end
    
    decryption_layer->endParser();
    
    if (!is_stopped_by_user) {
        has_detail_buffer_offset_ = true;
    }
    
    return result;
}

bool FlightRecordParserProtocol::parseDetailDataLocation(FlightRecordDetailBufferOffset &bufferOffset) {
    if (!has_detail_buffer_offset_) {
        return false;
    }
    
    bufferOffset = detail_buffer_offset_;
    
    return true;
}

//MARK: - Decoder Public Method

ParserResult FlightRecordParserProtocol::AddVersionDecoder(VersionDecoder &decoder) {
    int index = 0;
    std::shared_ptr<VersionDecoder> newKeyChain = std::make_shared<VersionDecoder>();
    newKeyChain->set_minimum_support_version(decoder.minimum_support_version());
    newKeyChain->setDecodeDetailInfoLambda(decoder.DecodeDetailInfoLambda());
    newKeyChain->setDecodeDetailDataLambda(decoder.DecodeDetailDataLambda());
    newKeyChain->setGetDetailDataMessageLambda(decoder.getDetailDataMessageLambda());
    newKeyChain->set_support_decode_version_category(decoder.support_decode_version_category());
    
    for (VersionListIt it = all_decoder_.begin(); it != all_decoder_.end(); it ++) {
        if (decoder.minimum_support_version() > (*it)->minimum_support_version()) {
            all_decoder_.insert(it, newKeyChain);
            
            break;
        } else if (decoder.minimum_support_version() == (*it)->minimum_support_version()) {
            if ((*it)->support_decode_version_category() == decoder.support_decode_version_category()) {
                all_decoder_[index] = newKeyChain;
            } else {
                all_decoder_.insert(it, newKeyChain);
            }
            
            break;
        }
        
        index ++;
    }
    
    all_decoder_.push_back(newKeyChain);
    
    return ParserResult::Success;
}

//MARK: - Decryption Public Method

ParserResult FlightRecordParserProtocol::addDecryptionLayer(DecryptionLayerPtr &layer) {
    if (layer == nullptr) {
        assert(false && "can't pass the nullptr Decryption layer");
        return ParserResult::InvalidParam;
    }
    
    if (layer->version() == VersionCategory::None) {
        assert(false && "can't pass the Decryption layer which the version equal to None");
        return ParserResult::InvalidParam;
    }
    
    all_decryption_layer_[layer->version()] = layer;
    
    return ParserResult::Success;
}

//MARK: Private Method

//////////////////////////////// Parser Method ////////////////////////////////
ParserResult FlightRecordParserProtocol::parserInfoAndCheck() {
    if (m_isParseInfo) {
        return ParserResult::Success;
    }
    
    if (!m_FileReader) {
        return ParserResult::NoFileHandle;
    }
    
    DJIFlightRecordDetailFilePrefixStruct detailPrefix = {{0}};
    size_t detailPrefixSize = sizeof(DJIFlightRecordDetailFilePrefixStruct);
    m_FileReader->seekFromStart(0);
    if (detailPrefixSize != m_FileReader->read(&detailPrefix, detailPrefixSize)) {
        return ParserResult::ReadFileError;
    }
    
    VersionExtension version_extension;
    auto version_extension_result = obtainVersionExtension(version_extension);
    if (version_extension_result != ParserResult::Success) {
        return version_extension_result;
    }
    
    // store the prefix info
    m_prefixInfo = std::make_shared<DJIFlightRecordDetailFilePrefixStruct>();
    memcpy(m_prefixInfo.get(), &detailPrefix, detailPrefixSize);
    
    std::shared_ptr<VersionDecoder> suitableDecoder = getDecoderWithVersion(detailPrefix.detailInfoFormatVersion, version_extension_.version);
    
    if (!suitableDecoder) {
        return ParserResult::DecoderNotFound;
    }
    
    std::shared_ptr<Buffer> detailInfoBuffer;
    std::shared_ptr<Buffer> signature_buffer;
    ParserResult decodeDetailInfoResult = suitableDecoder->DecodeDetailInfo(m_FileReader, detailInfoBuffer, signature_buffer);
    
    if (decodeDetailInfoResult != ParserResult::Success) {
        return decodeDetailInfoResult;
    }
    
    m_info = std::make_shared<DJIFlightRecordDetailDataEndStruct>();
    memcpy(m_info.get(), detailInfoBuffer->buffer_pointer_, detailInfoBuffer->buffer_length_);
    
    m_isParseInfo = true;
    
    return ParserResult::Success;
}

//////////////////////////////// Utils Method ////////////////////////////////

bool FlightRecordParserProtocol::readUtilLineEnd(std::shared_ptr<FileCacheUtils> cache) {
    if (!cache) {
        return true;
    }
    
    int8_t readDataType;
    do {
        if (cache->read(&readDataType, sizeof(readDataType)) < sizeof(readDataType)) {
            return false;
        }
    } while (readDataType != LineEndFlightRecordDataType);
    
    return true;
}

//////////////////////////////// Container Operation Method ////////////////////////////////

std::shared_ptr<VersionDecoder> FlightRecordParserProtocol::getDecoderWithVersion(int version, VersionCategory version_category) {
    std::shared_ptr<VersionDecoder> item = nullptr;
    
    for (int i = 0; i < all_decoder_.size(); i ++) {
        item = all_decoder_[i];
        if (version >= item->minimum_support_version() && item->support_decode_version_category() == version_category) {
            return item;
        } else {
            item = nullptr;
        }
    }
    
    return item;
}

//MARK: - Decryption Private Method

DecryptionLayerPtr FlightRecordParserProtocol::getDecryptionLayer(VersionCategory version) {
    auto find = all_decryption_layer_.find(version);
    if (find != all_decryption_layer_.end()) {
        return (*find).second;
    }
    
    return nullptr;
}
