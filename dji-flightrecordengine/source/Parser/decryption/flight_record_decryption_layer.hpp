//
//  flight_record_decryption_layer.hpp
//  FlightRecordEngine
//
//  Copyright © 2019 DJISDK. All rights reserved.
//

#ifndef flight_record_decryption_layer_hpp
#define flight_record_decryption_layer_hpp

#include <stdio.h>
#include <FlightRecordProtocolEnum.h>
#include <set>
#include <map>
#include <Utils/buffer/flight_record_buffer.h>

namespace DJI {
    namespace FlightRecord {
    
        /// decryption layer
        /// @Note Responsible for decrypting the encryption schemes of the different modules, regardless of where the data is stored in the file. Unlike VersionDecoder
        class DecryptionLayer {
        public:
            DecryptionLayer();
            virtual ~DecryptionLayer();
            
            //MARK: - Decrypt Public Method
            
            /// Decrypted the detail body data.
            /// @param type the data type of the detail body.
            /// @param detailBody the detailed data that has been XORed.
            /// @return `the plaintext data.
            virtual BufferPtr decryptDetail(FlightRecordDataType type, BufferPtr detailBody);
            
            /// begin to parse a file.
            virtual void beginParser();
            
            /// end to parse a file.
            virtual void endParser();
            
            //MARK: - Decrypt Version Public Method
            
            VersionCategory version() const;
            
        protected:
            
            //MARK: - Decrypt Version Protected Method
        
            void set_version(VersionCategory version);
            
            VersionCategory version_;
        };
    
        using DecryptionLayerPtr = std::shared_ptr<DecryptionLayer>;
        typedef std::map<VersionCategory, DecryptionLayerPtr> DecryptionLayerMap;
        typedef std::map<VersionCategory, DecryptionLayerPtr>::iterator DecryptionLayerMapIt;
    }
}

#endif /* flight_record_decryption_layer_hpp */
