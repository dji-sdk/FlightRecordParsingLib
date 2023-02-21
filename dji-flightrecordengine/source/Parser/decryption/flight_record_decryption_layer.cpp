//
//  flight_record_decryption_layer.cpp
//  FlightRecordEngine
//
//  Copyright © 2019 DJISDK. All rights reserved.
//

#include <Parser/decryption/flight_record_decryption_layer.hpp>
#include <Parser/decryption/version13/flight_record_decryption_13_layer.hpp>

using namespace DJI::FlightRecord;

DecryptionLayer::DecryptionLayer():
version_(VersionCategory::None) {
    
}

DecryptionLayer::~DecryptionLayer() {
    
}

//MARK: - Decrypt Public Method

BufferPtr DecryptionLayer::decryptDetail(FlightRecordDataType type, BufferPtr detailBody) {
    return detailBody;
}

void DecryptionLayer::beginParser() {
    
}

void DecryptionLayer::endParser() {
    
}

//MARK: - Decrypt Version Public Method

VersionCategory DecryptionLayer::version() const {
    return version_;
}

//MARK: - Decrypt Version Protected Method

void DecryptionLayer::set_version(VersionCategory version) {
    version_ = version;
}
