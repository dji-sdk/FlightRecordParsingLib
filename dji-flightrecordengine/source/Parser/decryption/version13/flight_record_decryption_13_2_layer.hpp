//
//  flight_record_decryption_13_2_layer.hpp
//  FlightRecordEngine
//
//

#ifndef flight_record_decryption_13_2_layer_hpp
#define flight_record_decryption_13_2_layer_hpp

#include <stdio.h>
#include <Parser/decryption/version13/flight_record_decryption_13_layer.hpp>

namespace DJI {
    namespace FlightRecord {
        class Decryption13V2Layer : public Decryption13Layer {
        public:
            Decryption13V2Layer(const std::vector<std::map<FeaturePoint, AESKeychainPtr>>& aes_keychains);
            
            /// No key usage. Used by App.
            Decryption13V2Layer();
            
            ~Decryption13V2Layer();
        };
    }
}

#endif /* flight_record_decryption_13_2_layer_hpp */
