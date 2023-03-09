//
//  flight_record_version13_decoder.cpp
//  FlightRecordEngine
//
//  Copyright © 2019 DJISDK. All rights reserved.
//

#include <Parser/decoder/version13/flight_record_version13_decoder.hpp>
#include <model/protocol/fr_protocol.h>
#include <Utils/File/FlightRecordFileHandleUtils.h>
#include <iostream>
#include <memory>
#include <model/info/FlightRecordInfoModel.h>
#include <Utils/encryption/FlightRecordEncryptUtils.h>
#include <assert.h>

using namespace DJI::FlightRecord;

static DJIDecodeDetailInfoFunction GetDecodeDetailInfoLambda();

//MARK: - Config

Version13Decoder::Version13Decoder():VersionDecoder() {
    minimum_support_version_ = 13;
    support_decode_version_category_ = VersionCategory::Version13_1;
}

Version13Decoder::~Version13Decoder() {
    
}

//MARK: - Decode

DJIDecodeDetailInfoFunction Version13Decoder::DecodeDetailInfoLambda() {
    return GetDecodeDetailInfoLambda();
}

DJIDecodeDetailDataFunction Version13Decoder::DecodeDetailDataLambda() {
    return [] (const FileCacheUtilsPtr& cache) -> BufferPtr {
        uint16_t dataLength;
        if (cache->read(&dataLength, sizeof(dataLength)) < sizeof(dataLength) != 0) {
            return nullptr;
        }

        if (dataLength == 0) {
            return nullptr;
        }

        auto body_buf = std::make_shared<Buffer>(dataLength);
        if (cache->read(body_buf->buffer_pointer_, dataLength) < dataLength) {
            return nullptr;
        }

        uint8_t endDataType;
        if (cache->read(&endDataType, sizeof(endDataType)) < sizeof(endDataType)) {
            return nullptr;
        }

        if (endDataType != (uint8_t)LineEndFlightRecordDataType) {
            return nullptr;
        }

        return body_buf;
    };
}

DJIGetDetailDataMessageFunction Version13Decoder::getDetailDataMessageLambda() {
    return [] (const FileHandlerUtilsPtr& file_handler, DetailDataMessage &message) {
        if (!file_handler) {
            return ParserResult::NoFileHandle;
        }
        
        DJIFlightRecordDetailFilePrefixStruct detailPrefix = {0};
        size_t detailPrefixSize = sizeof(DJIFlightRecordDetailFilePrefixStruct);
        file_handler->seekFromStart(0);
        if (detailPrefixSize != file_handler->read(&detailPrefix, detailPrefixSize)) {
            return ParserResult::ReadFileError;
        }
        
        DJIFlightRecordPrefixMagic prefixMagic;
        if (detailPrefix.detailInfoFormatVersion >= FREncryptVersion) {
            file_handler->read(&prefixMagic, sizeof(DJIFlightRecordPrefixMagic));
            
            if (prefixMagic.encryptMagicVersion <= CurrentFREncryptMagicVersion) {
                message.isMagicEncrypt = true;
                message.encryptMagicVersion = prefixMagic.encryptMagicVersion;
            } else {
                return ParserResult::DecodeFailed;
            }
        }
        
        message.detailDataHead = detailPrefix.detailDataOffsetFromHead;
        message.imagePosition = -1;
        message.detailDataTail = -1;
        
        // try to recover
        if (message.detailDataHead == 0) {
            do {
                size_t pre_offset = sizeof(DJIFlightRecordDetailFilePrefixStruct) + sizeof(DJIFlightRecordPrefixMagic);
                file_handler->seekFromStart(pre_offset);
                
                FlightRecordAuxiliaryStruct auxiliary_info;
                file_handler->read(&auxiliary_info, sizeof(auxiliary_info));
                
                if (auxiliary_info.type != FlightRecordAuxiliaryDataType::Info) {
                    assert(false && "should be the info auxiliary type");
                    break;
                }
                
                pre_offset += sizeof(auxiliary_info) + auxiliary_info.auxiliary_data.data_length;
                
                file_handler->seekFromStart(pre_offset);
                
                FlightRecordAuxiliaryStruct auxiliary_version_category;
                file_handler->read(&auxiliary_version_category, sizeof(auxiliary_version_category));
                
                if (auxiliary_version_category.type != FlightRecordAuxiliaryDataType::VersionExtension) {
                    assert(false && "should be the version category type");
                    break;
                }
                
                pre_offset += sizeof(auxiliary_version_category) + auxiliary_version_category.auxiliary_data.data_length;
                message.detailDataHead = pre_offset;
            } while (0);
        }
        
        auto getInfoLambda = GetDecodeDetailInfoLambda();
        BufferPtr info_buf;
        BufferPtr signature_buf;
        auto result = getInfoLambda(file_handler, info_buf, signature_buf);
        
        if (result != ParserResult::Success) {
            return result;
        }
        
        DJIFlightRecordDetailDataEndStruct *detailInfo = (DJIFlightRecordDetailDataEndStruct *)info_buf->buffer_pointer_;
        
        long imageCheckSumOffset = file_handler->m_FileSize;
        for (int i = 0; i < MomentPicNum; i ++) {
            imageCheckSumOffset -= detailInfo->momentPicImageBufferLen[i];
            imageCheckSumOffset -= detailInfo->momentPicShrinkImageBufferLen[i];
        }
        
        imageCheckSumOffset -= sizeof(int32_t);
        file_handler->seekFromStart(imageCheckSumOffset);
        int32_t imageCheckSum = 0;
        if (file_handler->read(&imageCheckSum, sizeof(int32_t)) != sizeof(int32_t)) {
            return ParserResult::Success;
        }
        
        if (imageCheckSum == detailInfoEndCheckSum) {
            message.imagePosition = file_handler->m_FileLocation;
            message.detailDataTail = file_handler->m_FileLocation - sizeof(int32_t);
        }
        
        return ParserResult::Success;
    };
}

//MARK: - Info Static function

#ifndef WIN32
    __attribute__((visibility("hidden")))
#endif
DJIDecodeDetailInfoFunction GetDecodeDetailInfoLambda() {
    return [] (const FileHandlerUtilsPtr& file_handler, BufferPtr& output, BufferPtr &signature) {
        if (!file_handler) {
            return ParserResult::NoFileHandle;
        }
        
        DJIFlightRecordDetailFilePrefixStruct detailPrefix = {0};
        size_t detailPrefixSize = sizeof(DJIFlightRecordDetailFilePrefixStruct);
        file_handler->seekFromStart(0);
        if (detailPrefixSize != file_handler->read(&detailPrefix, detailPrefixSize) ||
            (detailPrefix.detailInfoFormatVersion < Version13DecoderMaxVersion ||
             detailPrefix.detailInfoFormatVersion > Version13_2DecoderMaxVersion)) {
            return ParserResult::ReadFileError;
        }
        
        DJIFlightRecordPrefixMagic prefixMagic;
        if (file_handler->read(&prefixMagic, sizeof(prefixMagic)) != sizeof(prefixMagic)) {
            return ParserResult::ReadFileError;
        }
        
        FlightRecordAuxiliaryStruct auxiliary_data;
        if (file_handler->read(&auxiliary_data, sizeof(auxiliary_data)) != sizeof(auxiliary_data)) {
            return ParserResult::ReadFileError;
        }
        
        if (auxiliary_data.type != FlightRecordAuxiliaryDataType::Info) {
            return ParserResult::VerifyFileFailed;
        }
        
        BufferPtr auxiliary_data_buf = std::make_shared<Buffer>(auxiliary_data.auxiliary_data.data_length);
        if (file_handler->read(auxiliary_data_buf->buffer_pointer_, auxiliary_data_buf->buffer_length_) != auxiliary_data_buf->buffer_length_) {
            return ParserResult::ReadFileError;
        }
        
        BufferPtr all_info_plaintext_buf = std::make_shared<Buffer>(auxiliary_data.auxiliary_data.data_length);
        uint64_t all_info_plaintext_len = deEncryptData((uint8_t *)all_info_plaintext_buf->buffer_pointer_,
                                                        (uint8_t *)auxiliary_data_buf->buffer_pointer_,
                                                        auxiliary_data.auxiliary_data.data_length,
                                                        (int)FlightRecordAuxiliaryDataType::Info,
                                                        (uint64_t)CurrentFREncryptMagicVersion);
        if (all_info_plaintext_len != auxiliary_data.auxiliary_data.data_length - 2) {
            return ParserResult::DecodeFailed;
        }
        
        FlightRecordInfoPlaintext *all_info = (FlightRecordInfoPlaintext *)all_info_plaintext_buf->buffer_pointer_;
        switch (all_info->version) {
            case FlightRecordInfoVersion::Version1:
            {
                if (all_info->info_data.data_length != sizeof(DJIFlightRecordDetailDataEndStruct)) {
                    assert(false && "invalid info data");
                    return ParserResult::VerifyFileFailed;
                }
                
                DJIFlightRecordDetailDataEndStruct *info = (DJIFlightRecordDetailDataEndStruct *)all_info->info_data.data;
                if (info->detailInfoCheckSum != detailInfoEndCheckSum) {
                    return ParserResult::VerifyFileFailed;
                }
                
                output = std::make_shared<Buffer>(all_info->info_data.data, all_info->info_data.data_length);
                
                FlightRecordCommonData *signature_data = (FlightRecordCommonData *)((uint8_t *)all_info->info_data.data + all_info->info_data.data_length);
                
                signature = std::make_shared<Buffer>(signature_data->data, signature_data->data_length);
            }
                break;
                
            default:
                assert(false && "should adapter the new version info");
                return ParserResult::Failure;
        }
        
        return ParserResult::Success;
    };
}

//MARK: - Version Category

#ifndef WIN32
    __attribute__((visibility("hidden")))
#endif
VersionExtension DJI::FlightRecord::GetVersionCategoryBy13Decoder(const FileHandlerUtilsPtr& file_handler) {
    auto getInfoLambda = GetDecodeDetailInfoLambda();
    BufferPtr info_buf;
    BufferPtr signature_buf;
    auto result = getInfoLambda(file_handler, info_buf, signature_buf);
    
    VersionExtension version_extension;
    version_extension.department = Department::Unknown;
    version_extension.version = VersionCategory::None;
    
    if (result != ParserResult::Success) {
        return version_extension;
    }
    
    FlightRecordAuxiliaryStruct version_data;
    if (file_handler->read(&version_data, sizeof(version_data)) != sizeof(version_data)) {
        return version_extension;
    }
    
    if (version_data.type != FlightRecordAuxiliaryDataType::VersionExtension ||
        version_data.auxiliary_data.data_length != sizeof(version_extension)) {
        assert("need to check. The version auxiliary should be behind the info.");
        return version_extension;
    }
    
    if (file_handler->read(&version_extension, sizeof(version_extension)) != sizeof(version_extension)) {
        return version_extension;
    }
    
    return version_extension;
}
