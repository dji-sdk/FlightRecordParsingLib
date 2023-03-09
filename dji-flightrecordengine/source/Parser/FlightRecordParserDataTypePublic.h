//
//  FlightRecordParserDataTypePublic.h
//  FlightRecordEngine
//
//  Copyright © 2017 DJI. All rights reserved.
//

#ifndef FlightRecordParserDataTypePublic_h
#define FlightRecordParserDataTypePublic_h

#include <stdio.h>
#include <FlightRecordProtocolEnum.h>
#include <iostream>
#include <memory>
#include <functional>

namespace DJI {
    namespace FlightRecordKit {
        class Buffer;
    }
    
    namespace FlightRecord {
        class FlightRecordParserEngine;
        
        enum class ParserResult {
            /// unknow failure
            Failure = 0,
            Success,
            /// without parser to use
            NoParser,
            /// with file handle to parse file
            NoFileHandle,
            /// read the file abnormal. Maybe the file is damage.
            ReadFileError,
            /// verify the file complete fail.
            /// 1. checksum can't match '12345'.
            /// 2. Condition is not established.
            VerifyFileFailed,
            /// init the file handle failed.
            InitFileHandleFailed,
            /// not support this version to parse ( version < 3 )
            VersionNotSupport,
            /// not found suitable decoder
            DecoderNotFound,
            /// decode failed
            DecodeFailed,
            /// Invalid Param
            InvalidParam,
            /// Feature not supported error.
            FeatureNotSupported,
            /// File data contamination
            FileDataContamination,
        };
        
        enum class ParseImageType {
            None = 0,
            Thumbnail,
            Snapshot,
        };
    }
}

typedef struct {
    size_t location;
    size_t length;
} FlightRecordDetailBufferOffset;

//typedef void(*FlightRecordParseImage) (DJI::FlightRecord::FlightRecordParserEngine *parser, int imageIndex, int8_t *buffer, long bufferLen);
typedef std::function<void (DJI::FlightRecord::FlightRecordParserEngine* engine, FlightRecordDataType dataType, int index, uint8_t *buffer, uint64_t length, bool *stop)> FlightRecordParseDetailDataEngineLambda;
typedef std::function<void (FlightRecordDataType dataType, int index, uint8_t *buffer, uint64_t length, bool *stop)> FlightRecordParseDetailDataProtocolLambda;
typedef std::function<void (FlightRecordDataType dataType, int index, std::shared_ptr<DJI::FlightRecordKit::Buffer> serializeBuffer, bool *stop)> FlightRecordParseDetailDataKitLambda;

#endif /* FlightRecordParserDataTypePublic_h */
