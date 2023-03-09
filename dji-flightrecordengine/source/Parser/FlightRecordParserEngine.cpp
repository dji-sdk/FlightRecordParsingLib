//
//  FlightRecordParser.cpp
//  FlightRecordEngine
//
//  Copyright © 2017 DJI. All rights reserved.
//

#include <stdio.h>
#include <iostream>
#include <Parser/FlightRecordParserEngine.h>
#include <Parser/protocol/FlightRecordParserProtocol.h>
#include <Parser/decoder/flight_record_version_decoder.h>
#include <memory>

using namespace DJI::FlightRecord;
using namespace std;

FlightRecordParserEngine::FlightRecordParserEngine() {

}

FlightRecordParserEngine::~FlightRecordParserEngine() {
    m_FlightRecordParser = nullptr;
}

/////////////////////////////////// Configuration Method //////////////////////////////////

ParserResult FlightRecordParserEngine::SetFilePath(std::string filePath) {
    std::shared_ptr<FileHandlerUtils> tempFileHandler;
    
    tempFileHandler = std::make_shared<FileHandlerUtils>(filePath, FileHandleType::FileHandlerReader);
    if (tempFileHandler->canRead() != ParserResult::Success) {
        return tempFileHandler->canRead();
    }
    
    DJIFlightRecordDetailFilePrefixStruct detailPrefix = {{0}};
    size_t detailPrefixSize = sizeof(DJIFlightRecordDetailFilePrefixStruct);
    if (detailPrefixSize != tempFileHandler->read(&detailPrefix, detailPrefixSize)) {
        return ParserResult::ReadFileError;
    }
    
    m_InfoFormatVersion = detailPrefix.detailInfoFormatVersion;
    
    ParserResult result = createFileParser(detailPrefix.detailInfoFormatVersion);
    
    if (m_FlightRecordParser) {
        m_FlightRecordParser->setFileHandler(tempFileHandler);
    }
    
    return result;
}

/////////////////////////////////// Get Data Method //////////////////////////////////

ParserResult FlightRecordParserEngine::obtainInfo(DJIFlightRecordDetailDataEndStruct &info) {
    if (!m_FlightRecordParser) {
        return ParserResult::NoParser;
    }
    
    ParserResult result = m_FlightRecordParser->obtainInfo(info);
    
    return result;
}

ParserResult FlightRecordParserEngine::obtainVersion(uint8_t &version) {
    if (!m_FlightRecordParser) {
        return ParserResult::NoParser;
    }
    
    return m_FlightRecordParser->obtainVersion(version);
}

ParserResult FlightRecordParserEngine::obtainVersionExtension(VersionExtension &version) {
    if (!m_FlightRecordParser) {
        return ParserResult::NoParser;
    }
    
    return m_FlightRecordParser->obtainVersionExtension(version);
}

ParserResult FlightRecordParserEngine::parseImageData(ParseImageType imageType,
                                                      std::function<void (FlightRecordParserEngine*, int, uint8_t*, long)> callback) {
    if (!m_FlightRecordParser) {
        return ParserResult::NoParser;
    }
    
    auto parserBlock = [this, callback] (int imageIndex, uint8_t *buffer, long bufferLen) {
        if (!callback) {
            return;
        }
        
        callback(this, imageIndex, buffer, bufferLen);
    };
    
    if (m_FlightRecordParser) {
        m_FlightRecordParser->parseImageData(imageType, parserBlock);
    }
    
    return ParserResult::Success;
}

ParserResult FlightRecordParserEngine::parseDetailData(FlightRecordParseDetailDataEngineLambda callback) {
    if (!m_FlightRecordParser) {
        return ParserResult::NoParser;
    }
    
    auto parseBlock = [this, callback] (FlightRecordDataType dataType, int index, uint8_t *buffer, uint64_t bufferLen, bool *stop) {
        if (!callback) {
            return;
        }
        
        callback(this, dataType, index, buffer, bufferLen, stop);
    };
    
    return m_FlightRecordParser->parseDetailData(parseBlock);
}

ParserResult FlightRecordParserEngine::parseDetailDataLocation(FlightRecordDetailBufferOffset &bufferOffset) {
    if (!m_FlightRecordParser) {
        return ParserResult::NoParser;
    }
    
    if (m_FlightRecordParser) {
        if (!m_FlightRecordParser->parseDetailDataLocation(bufferOffset)) {
            return ParserResult::Failure;
        }
    }
    
    return ParserResult::Success;
}

//////////////////////////////// Security ////////////////////////////////

ParserResult FlightRecordParserEngine::AddVersionDecoder(VersionDecoder &decoder) {
    if (m_FlightRecordParser) {
        m_FlightRecordParser->AddVersionDecoder(decoder);
        
        return ParserResult::Success;
    }
    
    return ParserResult::Failure;
}

//MARK: - Decryption Private Method

ParserResult FlightRecordParserEngine::addDecryptionLayer(DecryptionLayerPtr &layer) {
    return m_FlightRecordParser ? m_FlightRecordParser->addDecryptionLayer(layer) : ParserResult::Failure;
}

/////////////////////////////////// Configuration Method //////////////////////////////////

ParserResult FlightRecordParserEngine::createFileParser(uint8_t formatVersion) {
    std::shared_ptr<FlightRecordParserProtocol> tempParser = nullptr;
    
    if (formatVersion < Version13DecoderMaxVersion) {
        return ParserResult::VersionNotSupport;
    }
    
    tempParser = make_shared<FlightRecordParserProtocol>();
    
    if (tempParser) {
        m_FlightRecordParser = tempParser;
        
        return ParserResult::Success;
    }
    
    return ParserResult::Failure;
}
