//
//  flight_record_decryption_13_layer.cpp
//  FlightRecordEngine
//
//  Copyright © 2019 DJISDK. All rights reserved.
//

#include <Parser/decryption/version13/flight_record_decryption_13_layer.hpp>
#include <assert.h>
#include <model/keychain/FlightRecordKeychainModel.h>
#include <Utils/encryption/FlightRecordEncryptUtils.h>
#include <Utils/featurePoint/frDataTypeMap/flight_record_feature_point_map.hpp>

using namespace DJI::FlightRecord;

Decryption13Layer::Decryption13Layer(const std::vector<std::map<FeaturePoint, AESKeychainPtr>>& aes_keychains_):
DecryptionLayer() {
    set_version(VersionCategory::Version13_1);
    feature_point_map_ = Version13_1FeaturePointMap();
    all_aes_keychain_ = aes_keychains_;
}

Decryption13Layer::Decryption13Layer():
DecryptionLayer() {
    set_version(VersionCategory::Version13_1);
    feature_point_map_ = Version13_1FeaturePointMap();
}

Decryption13Layer::~Decryption13Layer() {
    all_aes_keychain_.clear();
    feature_point_map_.clear();
}

//MARK: - Decrypt Public Method

BufferPtr Decryption13Layer::decryptDetail(FlightRecordDataType type, BufferPtr detailBody) {
    switch (type) {
        case KeyStorage:
        {
            return detailBody;
        }
        case FlightRecordRecover:
        {
            file_index_ ++;
        }
            break;
        case npzeXkozKlNHPjUQ:
            return nullptr;
            
        default:
        {
            return parseAESData(type, detailBody);
        }
            break;
    }
    
    return nullptr;
}

void Decryption13Layer::beginParser() {
    file_index_ = 0;
}

void Decryption13Layer::endParser() {
    file_index_ = 0;
}

//MARK: - Parse Private Method

BufferPtr Decryption13Layer::parseAESData(FlightRecordDataType type, BufferPtr aes_ciphertext) {
    auto feature_point_iter = feature_point_map_.find(type);
    if (feature_point_iter == feature_point_map_.end()) {
        return nullptr;
    }
    
    auto feature_point = (*feature_point_iter).second;
    if (feature_point == FeaturePoint::PlaintextFeature) {
        return aes_ciphertext;
    }
    
    if (all_aes_keychain_.size() <= file_index_) {
        return nullptr;
    }
    
    auto aes_keychain_iter = all_aes_keychain_[file_index_].find(feature_point);
    if (aes_keychain_iter == all_aes_keychain_[file_index_].end()) {
//        assert(false && "aes key should be exist");
        return nullptr;
    }
    auto aes_keychain = (*aes_keychain_iter).second;
    
    int error_code = register_cipher(&rijndael_desc);
    if (error_code != CRYPT_OK) {
        assert(false && error_to_string(error_code));
        return nullptr;
    }
    
    int idx = find_cipher("rijndael");
    if (idx == -1) {
        assert(false && "can't find aes cipher idx");
        return nullptr;
    }
    
    symmetric_CBC cbc;
    error_code = cbc_start(idx,
                           (const unsigned char *)aes_keychain->aes_iv_key()->buffer_pointer_,
                           (const unsigned char *)aes_keychain->aes_key()->buffer_pointer_,
                           (int)aes_keychain->aes_key()->buffer_length_,
                           0,
                           &cbc);
    if (error_code != CRYPT_OK) {
        assert(false && error_to_string(error_code));
        return nullptr;
    }
    
    BufferPtr plaintext_padding = std::make_shared<Buffer>(aes_ciphertext->buffer_length_);
    error_code = cbc_decrypt((const unsigned char *)aes_ciphertext->buffer_pointer_,
                             (unsigned char *)plaintext_padding->buffer_pointer_,
                             plaintext_padding->buffer_length_,
                             &cbc);
    if (error_code != CRYPT_OK) {
        assert(false && "aes decryption failure.");
        return nullptr;
    }
    
    cbc_getiv((unsigned char *)aes_keychain->aes_iv_key()->buffer_pointer_, (unsigned long *)&aes_keychain->aes_iv_key()->buffer_length_, &cbc);
    cbc_done(&cbc);
    
    BufferPtr plaintext = RemovePKCS7Padding(plaintext_padding->buffer_pointer_,
                                             plaintext_padding->buffer_length_,
                                             cbc.blocklen);
    
    return plaintext;
}
