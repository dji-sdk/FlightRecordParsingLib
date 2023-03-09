//
//  flight_record_decryption_13_2_layer.cpp
//  FlightRecordEngine
//
//

#include "flight_record_decryption_13_2_layer.hpp"
#include <Utils/featurePoint/frDataTypeMap/flight_record_feature_point_map.hpp>

using namespace DJI::FlightRecord;

Decryption13V2Layer::Decryption13V2Layer(const std::vector<std::map<FeaturePoint, AESKeychainPtr>>& aes_keychains):
Decryption13Layer(aes_keychains) {
    set_version(VersionCategory::Version13_2);
    feature_point_map_ = Version13_2FeaturePointMap();
}

Decryption13V2Layer::Decryption13V2Layer() {
    set_version(VersionCategory::Version13_2);
    feature_point_map_ = Version13_2FeaturePointMap();
}

Decryption13V2Layer::~Decryption13V2Layer() {
    
}
