//
//  flight_record_rsa_tool.cpp
//  FlightRecordEngine
//
//  Copyright © 2019 DJISDK. All rights reserved.
//

#include "flight_record_rsa_tool.hpp"
#include <assert.h>
#include <string>
#include <assert.h>

using namespace DJI::FlightRecord;

static int const FR_Ciphertext_Length = 2048;

#ifndef WIN32
    __attribute__((visibility("hidden")))
#endif
BufferPtr DJI::FlightRecord::RSADecryptData(const BufferPtr& ciphertext,
                                            const BufferPtr& lparam,
                                            rsa_key& rsa_custom_key) {
    if (register_hash(&sha256_desc) == -1) {
        assert(false && "Error registering sha256.");
        return nullptr;
    }
    
    int hash_idx = find_hash("sha256");
    
    unsigned char plaintext[FR_Ciphertext_Length] = {0};
    unsigned long plaintext_len = sizeof(plaintext);
    
    int error_code;
    int stat = 0;
    error_code = rsa_decrypt_key_ex((const unsigned char *)ciphertext->buffer_pointer_,
                                    ciphertext->buffer_length_,
                                    plaintext,
                                    &plaintext_len,
                                    (const unsigned char *)lparam->buffer_pointer_,
                                    lparam->buffer_length_,
                                    hash_idx,
                                    LTC_PKCS_1_V1_5,
                                    &stat,
                                    &rsa_custom_key);
    
    if (error_code != CRYPT_OK) {
        assert(false && error_to_string(error_code));
        return nullptr;
    }
    
    if (stat != 1) {
        assert(false && "invalid plaintext text");
        return nullptr;
    }
    
    BufferPtr plaintext_buf = std::make_shared<Buffer>(plaintext, plaintext_len);
    
    return plaintext_buf;
}
