//
//  flight_record_version_decoder.h
//  FlightRecordEngine
//
//  Copyright © 2017 DJI. All rights reserved.
//

#ifndef flight_record_version_decoder_hpp
#define flight_record_version_decoder_hpp

#include <stdio.h>
#include <Parser/FlightRecordParserDataTypePublic.h>
#include <vector>
#include <functional>
#include <Utils/buffer/flight_record_buffer.h>
#include <iostream>
#include <memory>
#include <Utils/File/FlightRecordFileHandleUtils.h>
#include <Utils/Cache/FlightRecordFileCacheUtils.h>

// Old Encrypt Version
#define FREncryptVersion 7
#define Version13DecoderMaxVersion 13
#define Version13_2DecoderMaxVersion 14

namespace DJI {
    namespace FlightRecord {
        struct DetailDataMessage {
            uint64_t encryptMagicVersion;
            long detailDataHead;                // The header of the detail data block.
            long detailDataTail;                // The end of the detail data block.
            bool isMagicEncrypt;                // Is it different or encrypted?
            long imagePosition;
        };
    }
}

namespace DJI {
    namespace FlightRecord {
        typedef std::function<ParserResult (const FileHandlerUtilsPtr& file_handler, BufferPtr &output, BufferPtr &signature)> DJIDecodeDetailInfoFunction;
        typedef std::function<BufferPtr (const FileCacheUtilsPtr& cache)> DJIDecodeDetailDataFunction;
        typedef std::function<ParserResult (const FileHandlerUtilsPtr& file_handler, DetailDataMessage &message)> DJIGetDetailDataMessageFunction;
        
        /// Configuring different versions of the decoder, the interfaces here are mostly directly related to different parts of the file.
        /// @attention Each decoder has its own minimum version number to support decoding from this version. For FlightRecordParserEngine you can have multiple decoders for different versions of decoding.
        /// @Note The decoder is where the corresponding meaning field is resolved. For example, if the structure changes, you need to add a new decoder.
        class VersionDecoder {
        public:
            VersionDecoder();
            virtual ~VersionDecoder();
            
            /**
             * Decoding Data from Detail Info
             
             @param output Decoded content
             */
            virtual DJI::FlightRecord::ParserResult DecodeDetailInfo(const FileHandlerUtilsPtr& file_handler, BufferPtr &output, BufferPtr &signature);
            
            /// Decode the cipher detail data.
            /// It will read the detail data length, the cipher detail data and the end of the detail data.
            /// Please make sure without the data type at the begin of the cache('FileCacheUtilsPtr').
            /// @param cache the cache handler which the reading position is at the reading body length.
            /// @return return nil if the format is invalid or the end of the cache.
            virtual BufferPtr DecodeDetailData(const FileCacheUtilsPtr& cache);
            
            /**
             * Get information about Detail Data, such as whether it is different or encrypted, the location of the data in Detail Data
             
             @param message Detailed data information
             @result Results of access to information
             */
            virtual DJI::FlightRecord::ParserResult getDetailDataMessage(const FileHandlerUtilsPtr& file_handler, DetailDataMessage &message);
            
            //////////////////////////////// Getter ////////////////////////////////
            /**
             * Minimum supported version
             */
            virtual int minimum_support_version();
            virtual void set_minimum_support_version(int version);
            
            /**
             * Supported file encryption types
             */
            virtual VersionCategory support_decode_version_category();
            virtual void set_support_decode_version_category(VersionCategory version);
            
            // Explain why the above method uses lambda delivery
            // Lambda is used because the decryption may exist externally, at this point if it is an incoming heap object, who manages the lifecycle, does not match who creates and who destroys.
            // With smart pointers, shared_ptr is not very Android-friendly, and the current idea is to use lambda to encapsulate the decryption method between different modules.
            
            //////////////////////////////// Getter Lambda ////////////////////////////////
            virtual DJIDecodeDetailInfoFunction DecodeDetailInfoLambda();
            virtual DJIDecodeDetailDataFunction DecodeDetailDataLambda();
            virtual DJIGetDetailDataMessageFunction getDetailDataMessageLambda();
            
            //////////////////////////////// Setter Lambda ////////////////////////////////
            virtual void setDecodeDetailInfoLambda(DJIDecodeDetailInfoFunction lambda);
            virtual void setDecodeDetailDataLambda(DJIDecodeDetailDataFunction lambda);
            virtual void setGetDetailDataMessageLambda(DJIGetDetailDataMessageFunction lambda);
            
        protected:
            
            int minimum_support_version_;
            
            VersionCategory support_decode_version_category_;
            
        private:
            DJIDecodeDetailInfoFunction decode_detail_info_lambda_;
            DJIDecodeDetailDataFunction decode_detail_data_lambda_;
            DJIGetDetailDataMessageFunction get_detail_data_message_lambda_;
        };
    
        //MARK: - Version Category
        VersionExtension ParseVersion(const FileHandlerUtilsPtr& file_handler);
    }
}

typedef std::shared_ptr<DJI::FlightRecord::VersionDecoder> VersionDecoderSharePtr;
typedef std::vector<VersionDecoderSharePtr> VersionList;
typedef std::vector<VersionDecoderSharePtr>::iterator VersionListIt;

#endif /* flight_record_version_decoder_hpp */
