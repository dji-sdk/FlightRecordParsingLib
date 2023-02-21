//
//  flight_record_aes_keychain.cpp
//  FlightRecordEngine
//
//  Copyright © 2020 DJISDK. All rights reserved.
//

#include "flight_record_aes_keychain.hpp"
#include <assert.h>
#include <string>

using namespace DJI::FlightRecord;

//MARK: - AESKeychain

AESKeychain::AESKeychain(BufferPtr aes_key, BufferPtr aes_iv_key):
aes_key_(aes_key),
aes_iv_key_(aes_iv_key) {
    
}

AESKeychain::~AESKeychain() {
    aes_key_ = nullptr;
    aes_iv_key_ = nullptr;
}

BufferPtr AESKeychain::aes_key() const {
    return aes_key_;
}

BufferPtr AESKeychain::aes_iv_key() const {
    return aes_iv_key_;
}
