//
//  fr_standardization_mobile_rc_model.cpp
//  FlightRecordStandardization
//
//  Copyright © 2019 DJISDK. All rights reserved.
//

#include "fr_standardization_mobile_rc_model.hpp"

using namespace DJIFR::standardization;

MobileRemoteControllerStateImp::MobileRemoteControllerStateImp() :
leftStickVertical_(0),
leftStickHorizontal_(0),
rightStickVertical_(0),
rightStickHorizontal_(0) {
    
}

MobileRemoteControllerStateImp::~MobileRemoteControllerStateImp() {
    
}

float MobileRemoteControllerStateImp::leftStickVertical() const {
    return leftStickVertical_;
}

void MobileRemoteControllerStateImp::set_leftStickVertical(float leftStickVertical) {
    leftStickVertical_ = leftStickVertical;
}

float MobileRemoteControllerStateImp::leftStickHorizontal() const {
    return leftStickHorizontal_;
}

void MobileRemoteControllerStateImp::set_leftStickHorizontal(float leftStickHorizontal) {
    leftStickHorizontal_ = leftStickHorizontal;
}

float MobileRemoteControllerStateImp::rightStickVertical() const {
    return rightStickVertical_;
}

void MobileRemoteControllerStateImp::set_rightStickVertical(float rightStickVertical) {
    rightStickVertical_ = rightStickVertical;
}

float MobileRemoteControllerStateImp::rightStickHorizontal() const {
    return rightStickHorizontal_;
}

void MobileRemoteControllerStateImp::set_rightStickHorizontal(float rightStickHorizontal) {
    rightStickHorizontal_ = rightStickHorizontal;
}
