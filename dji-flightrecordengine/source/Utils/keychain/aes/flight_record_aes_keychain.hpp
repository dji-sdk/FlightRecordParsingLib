//
//  flight_record_aes_keychain.hpp
//  FlightRecordEngine
//
//  Copyright © 2020 DJISDK. All rights reserved.
//

#ifndef flight_record_aes_keychain_hpp
#define flight_record_aes_keychain_hpp

#include <stdio.h>
#include <Utils/buffer/flight_record_buffer.h>

namespace DJI {
    namespace FlightRecord {
        class AESKeychain {
        public:
            AESKeychain(BufferPtr aes_key, BufferPtr aes_iv_key);
            ~AESKeychain();
            
            BufferPtr aes_key() const;
            
            BufferPtr aes_iv_key() const;
            
        private:
            
            BufferPtr aes_key_ = nullptr;
            
            BufferPtr aes_iv_key_ = nullptr;
        };
    
        using AESKeychainPtr = std::shared_ptr<AESKeychain>;
    }
}

#endif /* flight_record_aes_keychain_hpp */
