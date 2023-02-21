//
//  FlightRecordParserEngine.h
//  FlightRecordEngine
//
//  Copyright © 2017 DJI. All rights reserved.
//

#ifndef FlightRecordParserEngine_h
#define FlightRecordParserEngine_h

#include <vector>
#include <Parser/FlightRecordParserDataTypePublic.h>
#include <model/protocol/fr_protocol.h>
#include <Parser/decoder/flight_record_version_decoder.h>
#include <Parser/decryption/flight_record_decryption_layer.hpp>
#include <iostream>
#include <memory>

namespace DJI {
    namespace FlightRecord {
        class FlightRecordParserProtocol;
        class Worker;
        class FileHandlerUtils;
    }
}

namespace DJI {
    namespace FlightRecord {
        
        /**
         *  The class will parse the flight record file. It will support all the version ( version >= 3).
         *
         *  Pay Attention: All the method is not safe in thread.
         *  It should be used in serial thread. But you can create several FlightRecordParserEngine to parse serveral files in parallel
         *  in the upper application layer to ensure thread safe.
         *
         *  此类是非线程安全，设计成非线程安全，使用时请使用串行线程调用。
         *  但是也因此可以支持并行解析多个飞行记录文件
         */
        class FlightRecordParserEngine {
        public:
            
            FlightRecordParserEngine();
            ~FlightRecordParserEngine();
            
            //////////////////////////////// Configuration ////////////////////////////////
            /**
             *  @param filePath --- Sets folder to parser the flight records. / 设置解析飞行记录文件的路径
             *  @return result 返回值会告知执行是否成功 / the enum value to show result
             */
            ParserResult SetFilePath(std::string filePath);
            
            //////////////////////////////// Get Data ////////////////////////////////
            /**
             *  @param info --- 解析文件的info信息 / Parse to get the info data
             *  @return result 返回值会告知执行是否成功 / the enum value to show result
             */
            ParserResult obtainInfo(DJIFlightRecordDetailDataEndStruct &info);
            
            /**
             Get the version of the flight record.
             
             @param version the param to get the version.
             @return the operation result.
             */
            ParserResult obtainVersion(uint8_t &version);
            
            /// Get the version category.
            /// @param version the param to get the version category.
            /// @return the operation result.
            ParserResult obtainVersionExtension(VersionExtension &version);
            
            /**
             *  The method can get image data, such as snapshot, thumbnail. The block will call immediately
             *
             *  @param imageType --- 需要解析的图片类型 / Need to Parse image type
             *  @param callback --- 回调返回图片数据 / call back to return picture data
             */
            ParserResult parseImageData(ParseImageType imageType,
                                        std::function<void (FlightRecordParserEngine*, int, uint8_t*, long)> callback);
            
            /**
             *  Parse each flight log data. only support ParserFlightRecordFile File Type.
             *
             *  @param callback --- 回调返回每条飞行记录 / call back to return each flight log
             */
            ParserResult parseDetailData(FlightRecordParseDetailDataEngineLambda callback);
            
            /**
             *  Parse detail data location
             *
             *  @param bufferOffset --- detail信息位置 / localtion message
             */
            ParserResult parseDetailDataLocation(FlightRecordDetailBufferOffset &bufferOffset);
            
            //////////////////////////////// Security ////////////////////////////////
            /**
             *  add Version Decoder
             *
             *  @param decoder --- different version of Decoder
             */
            ParserResult AddVersionDecoder(VersionDecoder &decoder);
            
            //MARK: - Decryption Private Method
            
            /// Add the decryption layer into `all_decryption_layer_`
            /// @param layer the new layer
            ParserResult addDecryptionLayer(DecryptionLayerPtr &layer);
            
        public:
            //////////////////////////////// Public Property ////////////////////////////////
            uint8_t m_InfoFormatVersion;
            
        private:
            //////////////////////////////// Configuration ////////////////////////////////
            
            ParserResult createFileParser(uint8_t formatVersion);
            
        private:
            /**
             *  Paraser the flight record file(ParserFlightRecordFile type)
             *  Support all the version ( >= 3 )
             */
            std::shared_ptr<FlightRecordParserProtocol> m_FlightRecordParser;
        };
        
        using FlightRecordParserEngineSharedPtr = std::shared_ptr<FlightRecordParserEngine>;
    }
}

#endif /* FlightRecordParserEngine_h */
