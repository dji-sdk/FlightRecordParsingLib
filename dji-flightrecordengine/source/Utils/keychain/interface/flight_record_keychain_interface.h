//
//  flight_record_keychain_interface.h
//  FlightRecordEngine
//
//  Copyright © 2020 DJISDK. All rights reserved.
//

#ifndef flight_record_keychain_interface_h
#define flight_record_keychain_interface_h

#include <stdio.h>
#include <string>
#include <iostream>
#include <memory>

namespace DJI {
    namespace FlightRecord {
        class Buffer;
    
        class DecryptKeyChain {
        public:
            virtual std::shared_ptr<Buffer> private_rsa_key_buffer() const = 0;
            
            virtual std::shared_ptr<Buffer> lparam() const = 0;
        };
    
        using DecryptKeyChainPtr = std::shared_ptr<DecryptKeyChain>;
    }
}

#endif /* flight_record_keychain_interface_h */
