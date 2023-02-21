//
//  flight_record_decrypt_keychain.h
//  FlightRecordEngine
//
//  Copyright © 2017 DJI. All rights reserved.
//

#ifndef flight_record_decrypt_keychain_hpp
#define flight_record_decrypt_keychain_hpp

#include <Utils/buffer/flight_record_buffer.h>
#include <tomcrypt.h>
#include <Utils/keychain/interface/flight_record_keychain_interface.h>

namespace DJI {
    namespace FlightRecord {
        class Buffer;
        
        class DecryptKeyChainImp : public DecryptKeyChain {
        public:
            DecryptKeyChainImp(const BufferPtr& private_rsa_key, const BufferPtr& lparam);
            virtual ~DecryptKeyChainImp();
            
            BufferPtr private_rsa_key_buffer() const override;
            
            BufferPtr lparam() const override;
            
            rsa_key *private_rsa_key();
            
        private:
            
            //MARK: - Private Variable
            
            BufferPtr private_rsa_key_buffer_ = nullptr;
            
            BufferPtr lparam_ = nullptr;
            
            rsa_key private_rsa_key_;
            
            bool is_private_rsa_key_exist = false;
        };
    
        using DecryptKeyChainImpPtr = std::shared_ptr<DecryptKeyChainImp>;
    }
}

#endif /* flight_record_decrypt_keychain_hpp */
