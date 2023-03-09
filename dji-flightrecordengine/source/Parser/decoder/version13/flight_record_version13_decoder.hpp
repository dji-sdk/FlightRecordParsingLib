//
//  flight_record_version13_decoder.hpp
//  FlightRecordEngine
//
//  Copyright © 2019 DJISDK. All rights reserved.
//

#ifndef flight_record_version13_decoder_hpp
#define flight_record_version13_decoder_hpp

#include <Parser/decoder/flight_record_version_decoder.h>

namespace DJI {
    namespace FlightRecord {
        /// Decoded version 13 of the flight record.
        class Version13Decoder : public VersionDecoder {
        public:
            //MARK: - Config
            Version13Decoder();
            virtual ~Version13Decoder();
            
            //MARK: - Decode
            
            /// Decoding Data from Detail Info
            virtual DJIDecodeDetailInfoFunction DecodeDetailInfoLambda() override;
            
            /// Decoding Data for Detail Data
            virtual DJIDecodeDetailDataFunction DecodeDetailDataLambda() override;
            
            /// Get information about Detail Data, such as whether it is different or encrypted, the location of the data in Detail Data
            virtual DJIGetDetailDataMessageFunction getDetailDataMessageLambda() override;
        };
    
        //MARK: - Version Category
    
        /// Get the version category by using the version 13 decode.
        /// @param file_handler  the file handler.
        /// @return If successful, it will return the correct version. If failure, it will return the None.
        VersionExtension GetVersionCategoryBy13Decoder(const FileHandlerUtilsPtr& file_handler);
    }
}

#endif /* flight_record_version13_decoder_hpp */
