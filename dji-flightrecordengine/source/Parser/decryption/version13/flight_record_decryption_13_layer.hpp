//
//  flight_record_decryption_13_layer.hpp
//  FlightRecordEngine
//
//  Copyright © 2019 DJISDK. All rights reserved.
//

#ifndef flight_record_decryption_13_layer_hpp
#define flight_record_decryption_13_layer_hpp

#include <stdio.h>
#include <Parser/decryption/flight_record_decryption_layer.hpp>
#include <tomcrypt.h>
#include <Utils/keychain/flight_record_decrypt_keychain.h>
#include <Utils/keychain/aes/flight_record_aes_keychain.hpp>
#include <map>
#include <vector>
#include <Utils/featurePoint/flight_record_feature_point_enum.h>

namespace DJI {
    namespace FlightRecord {
        class Decryption13Layer : public DecryptionLayer {
        public:
            /// Have a key. Used by DJI Server.
            Decryption13Layer(const std::vector<std::map<FeaturePoint, AESKeychainPtr>>& aes_keychains_);
            
            /// No key usage. Used by App.
            Decryption13Layer();
            virtual ~Decryption13Layer();
            
            //MARK: - Decrypt Public Method
            
            /// Decrypted the detail body data.
            /// @param type the data type of the detail body.
            /// @param detailBody the detailed data that has been XORed.
            /// @return `the plaintext data.
            virtual BufferPtr decryptDetail(FlightRecordDataType type, BufferPtr detailBody) override;
            
            /// begin to parse a file.
            virtual void beginParser() override;
            
            /// end to parse a file.
            virtual void endParser() override;
            
        private:
            //MARK: - Parse Private Method
            
            /// Parse the AES ciphertext.
            /// @param aes_ciphertext the AES ciphertext.
            /// @return the plaintext. If failure, it will return nullptr.
            BufferPtr parseAESData(FlightRecordDataType type, BufferPtr aes_ciphertext);
            
            //MARK: - Private Variable
            
            std::vector<std::map<FeaturePoint, AESKeychainPtr>> all_aes_keychain_;
            
            int file_index_ = 0;
            
        protected:
            
            std::map<FlightRecordDataType, FeaturePoint> feature_point_map_;
        };
    }
}

#endif /* flight_record_decryption_13_layer_hpp */
