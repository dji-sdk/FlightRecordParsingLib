//
//  flight_record_decrypt_keychain.cpp
//  FlightRecordEngine
//
//  Copyright © 2017 DJI. All rights reserved.
//

#include <Utils/keychain/flight_record_decrypt_keychain.h>
#include <Utils/buffer/flight_record_buffer.h>
#include <assert.h>

using namespace DJI::FlightRecord;

DecryptKeyChainImp::DecryptKeyChainImp(const BufferPtr& private_rsa_key, const BufferPtr& lparam):
private_rsa_key_buffer_(private_rsa_key),
lparam_(lparam) {
    init_LTM();
    
    if (!lparam_ || !private_rsa_key_buffer_) {
        assert(false && "Invalid keychian. FRServer should have the rsa private key and lparam.");
        return;
    }
    
    int error;
    error = rsa_import((const unsigned char *)private_rsa_key_buffer_->buffer_pointer_,
                       private_rsa_key_buffer_->buffer_length_,
                       &private_rsa_key_);
    
    if (error != CRYPT_OK) {
        std::string error_description("rsa import error: ");
        error_description.append(error_to_string(error));
        assert(false && error_description.c_str());
        return;
    }
    
    is_private_rsa_key_exist = true;
}

DecryptKeyChainImp::~DecryptKeyChainImp() {
    private_rsa_key_buffer_ = nullptr;
    lparam_ = nullptr;
    
    if (is_private_rsa_key_exist) {
        rsa_free(&private_rsa_key_);
    }
}

BufferPtr DecryptKeyChainImp::private_rsa_key_buffer() const {
    return private_rsa_key_buffer_;
}

BufferPtr DecryptKeyChainImp::lparam() const {
    return lparam_;
}

rsa_key *DecryptKeyChainImp::private_rsa_key() {
    return &private_rsa_key_;
}
