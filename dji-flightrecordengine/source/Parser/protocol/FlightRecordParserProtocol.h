//
//  FlightRecordParserProtocol.hpp
//  FlightRecordEngine
//
//  Copyright © 2017 DJI. All rights reserved.
//

#ifndef FlightRecordParser_hpp
#define FlightRecordParser_hpp

#include <stdio.h>
#include <functional>
#include <vector>
#include <Utils/File/FlightRecordFileHandleUtils.h>
#include <Parser/FlightRecordParserDataTypePublic.h>
#include <model/protocol/fr_protocol.h>
#include <Parser/decoder/flight_record_version_decoder.h>
#include <Parser/decryption/flight_record_decryption_layer.hpp>
#include <iostream>
#include <memory>

/////////////////////////////////////////////////////
//
//  All the Parser using the max Version to distinguish
//
//  FlightRecordVersionFiveParser only support less than version 5 (detailInfoFormatVersion), The file should be ParserFlightRecordFile
//  FlightRecordVersionFiveParser only support less than version 10 (detailInfoFormatVersion), The file should be ParserFlightRecordFile
//
/////////////////////////////////////////////////////

namespace DJI {
    namespace FlightRecord {
        
        class FileCacheUtils;
        
        class FlightRecordParserProtocol {
        public:
            //////////////////////////////// Create / Dealloc ////////////////////////////////
            FlightRecordParserProtocol();
            virtual ~FlightRecordParserProtocol();
            
            //////////////////////////////// Set Property ////////////////////////////////
            void setFileHandler(std::shared_ptr<FileHandlerUtils> fileHandler);
            
            //////////////////////////////// Get Property ////////////////////////////////
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
            
            //////////////////////////////// Parser Method ////////////////////////////////
            void parseImageData(ParseImageType imageType, std::function<void (int, uint8_t *, long)> callBack);
            
            ParserResult parseDetailData(FlightRecordParseDetailDataProtocolLambda callBack);
            bool parseDetailDataLocation(FlightRecordDetailBufferOffset &bufferOffset);
            
            //////////////////////////////// Security ////////////////////////////////
            //MARK: - Decoder Public Method
            
            ParserResult AddVersionDecoder(VersionDecoder &decoder);
            
            //MARK: - Decryption Public Method
            
            /// Add the decryption layer into `all_decryption_layer_`
            /// @param layer the new layer
            ParserResult addDecryptionLayer(DecryptionLayerPtr &layer);
            
        private:
            //MARK: Private Method
            
            //////////////////////////////// Parser Method ////////////////////////////////
            ParserResult parserInfoAndCheck();
            
            //////////////////////////////// Utils Method ////////////////////////////////
            
            bool readUtilLineEnd(std::shared_ptr<FileCacheUtils> cache);
            
            //////////////////////////////// Container Operation Method ////////////////////////////////
            void addNewDecoder(VersionDecoder &decoder);
            std::shared_ptr<VersionDecoder> getDecoderWithVersion(int version, VersionCategory version_category);
            
            //MARK: - Decryption Private Method

            /// Get the decryption layer
            /// @param version the version category
            /// @return If not exist in `all_decryption_layer_`, will return nullptr.
            DecryptionLayerPtr getDecryptionLayer(VersionCategory version);
            
        private:
            /**
             * Store all existing versions of the parser, from the lowest supported version number to the largest one in front
             **/
            VersionList all_decoder_;
            
            DecryptionLayerMap all_decryption_layer_;
            
            // Need to resolve the detail to know its true interval
            bool has_detail_buffer_offset_;
            FlightRecordDetailBufferOffset detail_buffer_offset_;
            
            std::shared_ptr<FileHandlerUtils> m_FileReader;
            
            VersionExtension version_extension_;
            
            /**
             *  the detail info / Generalized flight record information was recorded.
             */
            std::shared_ptr<DJIFlightRecordDetailDataEndStruct> m_info;
            
            /**
             *  the first data need to parse, DJIFlightRecordDetailDataEndStruct
             */
            std::shared_ptr<DJIFlightRecordDetailFilePrefixStruct> m_prefixInfo;
            
            /**
             *  It is a mark about parse the info data, and store them
             */
            bool m_isParseInfo;
        };
    }
}

#endif /* FlightRecordParser_hpp */
