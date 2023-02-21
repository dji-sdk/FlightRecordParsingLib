//
//  fr_standardization_airlink_model.cpp
//  FlightRecordStandardization
//
//  Copyright © 2020 DJISDK. All rights reserved.
//

#include "fr_standardization_airlink_model.hpp"

using namespace DJIFR::standardization;
using namespace DJI::FlightRecord;

//MARK: - AirLinkStateImp

AirLinkStateImp::AirLinkStateImp() {
    
}

AirLinkStateImp::~AirLinkStateImp() {
    
}

std::shared_ptr<AirLinkStateImp> AirLinkStateImp::clone() {
    return std::shared_ptr<AirLinkStateImp>(new AirLinkStateImp(*this));
}

int32_t AirLinkStateImp::downlinkSignalQuality() const {
    return downlinkSignalQuality_;
}

void AirLinkStateImp::set_downlinkSignalQuality(int32_t downlinkSignalQuality) {
    downlinkSignalQuality_ = downlinkSignalQuality;
}

bool AirLinkStateImp::has_downlinkSignalQuality() const {
    return has_downlinkSignalQuality_;
}

void AirLinkStateImp::set_has_downlinkSignalQuality(bool has_downlinkSignalQuality) {
    has_downlinkSignalQuality_ = has_downlinkSignalQuality;
}

int32_t AirLinkStateImp::uplinkSignalQuality() const {
    return uplinkSignalQuality_;
}

void AirLinkStateImp::set_uplinkSignalQuality(int32_t uplinkSignalQuality) {
    uplinkSignalQuality_ = uplinkSignalQuality;
}

bool AirLinkStateImp::has_uplinkSignalQuality() const {
    return has_uplinkSignalQuality_;
}

void AirLinkStateImp::set_has_uplinkSignalQuality(bool has_uplinkSignalQuality) {
    has_uplinkSignalQuality_ = has_uplinkSignalQuality;
}

//MARK: - Private Property

DroneType AirLinkStateImp::drone_type() const {
    return drone_type_;
}

void AirLinkStateImp::set_drone_type(DJI::FlightRecord::DroneType drone_type) {
    drone_type_ = drone_type;
}
