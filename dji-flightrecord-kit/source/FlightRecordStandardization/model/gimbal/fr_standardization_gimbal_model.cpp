//
//  fr_standardization_gimbal_model.cpp
//  FlightRecordStandardization
//
//  Copyright © 2019 DJISDK. All rights reserved.
//

#include "fr_standardization_gimbal_model.hpp"

using namespace DJIFR::standardization;

//MARK: - GimbalStateImp

GimbalStateImp::GimbalStateImp() :
atitude_(nullptr),
fineTunedRoll_(0),
fineTunedPitch_(0),
fineTunedYaw_(0),
isRollAtStop_(false),
isYawAtStop_(false),
isPitchAtStop_(false),
yawRelativeToAircraftHeading_(0),
mode_(GimbalMode::Free) {
    
}

GimbalStateImp::~GimbalStateImp() {
    atitude_ = nullptr;
}

std::shared_ptr<GimbalStateImp> GimbalStateImp::clone() {
    return std::shared_ptr<GimbalStateImp>(new GimbalStateImp(*this));
}

int GimbalStateImp::index() const {
    return index_;
}

void GimbalStateImp::set_index(int index) {
    index_ = index;
}

AttitudeSharedPtr GimbalStateImp::attitude() const {
    return atitude_;
}

void GimbalStateImp::set_attitude(const AttitudeSharedPtr& atitude) {
    atitude_ = atitude;
}

float GimbalStateImp::fineTunedRoll() const {
    return fineTunedRoll_;
}

void GimbalStateImp::set_fineTunedRoll(float fineTunedRoll) {
    fineTunedRoll_ = fineTunedRoll;
}

float GimbalStateImp::fineTunedPitch() const {
    return fineTunedPitch_;
}

void GimbalStateImp::set_fineTunedPitch(float fineTunedPitch) {
    fineTunedPitch_ = fineTunedPitch;
}

float GimbalStateImp::fineTunedYaw() const {
    return fineTunedYaw_;
}

void GimbalStateImp::set_fineTunedYaw(float fineTunedYaw) {
    fineTunedYaw_ = fineTunedYaw;
}

bool GimbalStateImp::isRollAtStop() const {
    return isRollAtStop_;
}

void GimbalStateImp::set_isRollAtStop(bool isRollAtStop) {
    isRollAtStop_ = isRollAtStop;
}

bool GimbalStateImp::isYawAtStop() const {
    return isYawAtStop_;
}

void GimbalStateImp::set_isYawAtStop(bool isYawAtStop) {
    isYawAtStop_ = isYawAtStop;
}

bool GimbalStateImp::isPitchAtStop() const {
    return isPitchAtStop_;
}

void GimbalStateImp::set_isPitchAtStop(bool isPitchAtStop) {
    isPitchAtStop_ = isPitchAtStop;
}

double GimbalStateImp::yawRelativeToAircraftHeading() const {
    return yawRelativeToAircraftHeading_;
}

void GimbalStateImp::set_yawRelativeToAircraftHeading(double yawRelativeToAircraftHeading) {
    yawRelativeToAircraftHeading_ = yawRelativeToAircraftHeading;
}

GimbalMode GimbalStateImp::mode() const {
    return mode_;
}

void GimbalStateImp::set_mode(GimbalMode mode) {
    mode_ = mode;
}
