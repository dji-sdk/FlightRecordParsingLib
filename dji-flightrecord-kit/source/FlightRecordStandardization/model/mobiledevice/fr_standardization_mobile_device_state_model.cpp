//
//  fr_standardization_mobile_device_state_model.cpp
//  FlightRecordStandardization
//
//  Copyright © 2020 DJISDK. All rights reserved.
//

#include "fr_standardization_mobile_device_state_model.hpp"

using namespace DJIFR::standardization;

MobileDeviceStateImp::MobileDeviceStateImp() {
    
}

MobileDeviceStateImp::~MobileDeviceStateImp() {
    
}

std::shared_ptr<MobileDeviceStateImp> MobileDeviceStateImp::clone() {
    return std::shared_ptr<MobileDeviceStateImp>(new MobileDeviceStateImp(*this));
}

LocationCoordinate2DSharedPtr MobileDeviceStateImp::coordinate() const {
    return coordinate_;
}

void MobileDeviceStateImp::set_coordinate(const LocationCoordinate2DSharedPtr &coordinate) {
    coordinate_ = coordinate;
}

double MobileDeviceStateImp::horizontalAccuracy() const {
    return horizontalAccuracy_;
}

void MobileDeviceStateImp::set_horizontalAccuracy(double horizontalAccuracy) {
    horizontalAccuracy_ = horizontalAccuracy;
}
