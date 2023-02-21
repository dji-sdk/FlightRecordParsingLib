//
//  fr_standardization_frametime_model.cpp
//  FlightRecordStandardization
//
//  Copyright © 2019 DJISDK. All rights reserved.
//

#include "fr_standardization_frametime_model.hpp"

using namespace DJIFR::standardization;

FrameTimeStateImp::FrameTimeStateImp() {
    
}

FrameTimeStateImp::~FrameTimeStateImp() {
    
}

std::shared_ptr<FrameTimeStateImp> FrameTimeStateImp::clone() {
    auto clone = std::make_shared<FrameTimeStateImp>();
    clone->set_rcHardwareState(rcHardwareState_ ? rcHardwareState_->clone() : nullptr);
    std::map<int, std::shared_ptr<GimbalStateImp>> gimbalsState;
    for (auto iter = gimbalsState_.begin(); iter != gimbalsState_.end(); iter ++) {
        gimbalsState[(*iter).first] = ((*iter).second)->clone();
    }
    clone->gimbalsState() = gimbalsState;
    clone->set_flightControllerState(flightControllerState_ ? flightControllerState_->clone() : nullptr);
    std::map<int, std::shared_ptr<CameraStateImp>> camerasState;
    for (auto iter = camerasState_.begin(); iter != camerasState_.end(); iter ++) {
        camerasState[(*iter).first] = (*iter).second;
    }
    clone->camerasState() = camerasState;
    std::map<int, std::shared_ptr<BatteryStateImp>> batteriesState;
    for (auto iter = batteriesState_.begin(); iter != batteriesState_.end(); iter ++) {
        batteriesState[(*iter).first] = (*iter).second->clone();
    }
    clone->batteriesState() = batteriesState;
    clone->set_airlinkState(airlinkState_ ? airlinkState_->clone() : nullptr);
    clone->set_mobileDeviceState(mobileDeviceState_ ? mobileDeviceState_->clone() : nullptr);
    clone->set_visionState(visionState_ ? visionState_->clone() : nullptr);
    
    return clone;
}

RCHardwareStateSharedPtr FrameTimeStateImp::rcHardwareState() const {
    return rcHardwareState_;
}

std::shared_ptr<RCHardwareStateImp> FrameTimeStateImp::rcHardwareStateImp() {
    return rcHardwareState_;
}

void FrameTimeStateImp::set_rcHardwareState(const std::shared_ptr<RCHardwareStateImp>& rcHardwareState) {
    rcHardwareState_ = rcHardwareState;
}

MobileRemoteControllerStateSharedPtr FrameTimeStateImp::mobileRemoteController() const {
    return mobileRemoteController_;
}

std::shared_ptr<MobileRemoteControllerStateImp> FrameTimeStateImp::mobileRemoteControllerImp() {
    return mobileRemoteController_;
}

void FrameTimeStateImp::set_mobileRemoteController(const std::shared_ptr<MobileRemoteControllerStateImp>& mobileRemoteController) {
    mobileRemoteController_ = mobileRemoteController;
}

GimbalStateSharedPtr FrameTimeStateImp::gimbalState() const {
    auto gimbal_iter = gimbalsState_.find(0);
    if (gimbal_iter == gimbalsState_.end()) {
        return nullptr;
    }
    
    return (*gimbal_iter).second;
}

std::shared_ptr<GimbalStateImp> FrameTimeStateImp::gimbalStateImp() {
    auto gimbal_iter = gimbalsState_.find(0);
    if (gimbal_iter == gimbalsState_.end()) {
        return nullptr;
    }
    
    return (*gimbal_iter).second;
}

void FrameTimeStateImp::set_gimbalState(const std::shared_ptr<GimbalStateImp>& gimbalState) {
    gimbalsState_[0] = gimbalState;
}

std::map<int, GimbalStateSharedPtr> FrameTimeStateImp::gimbalsState() const {
    std::map<int, GimbalStateSharedPtr> gimbalsState;
    for (auto iter = gimbalsState_.begin(); iter != gimbalsState_.end(); iter ++) {
        gimbalsState[(*iter).first] = (*iter).second;
    }
    return gimbalsState;
}

std::map<int, std::shared_ptr<GimbalStateImp>> & FrameTimeStateImp::gimbalsState() {
    return gimbalsState_;
}

FlightControllerStateSharedPtr FrameTimeStateImp::flightControllerState() const {
    return flightControllerState_;
}

std::shared_ptr<FlightControllerStateImp> FrameTimeStateImp::flightControllerStateImp() {
    return flightControllerState_;
}

void FrameTimeStateImp::set_flightControllerState(const std::shared_ptr<FlightControllerStateImp>& flightControllerState) {
    flightControllerState_ = flightControllerState;
}

CameraStateSharedPtr FrameTimeStateImp::cameraState() const {
    auto find_iter = camerasState_.find(0);
    if (find_iter == camerasState_.end()) {
        return nullptr;
    }
    
    return (*find_iter).second;
}

std::shared_ptr<CameraStateImp> FrameTimeStateImp::cameraStateImp() {
    auto find_iter = camerasState_.find(0);
    if (find_iter == camerasState_.end()) {
        return nullptr;
    }
    
    return (*find_iter).second;
}

void FrameTimeStateImp::set_cameraState(const std::shared_ptr<CameraStateImp>& cameraState) {
    camerasState_[0] = cameraState;
}

std::map<int, CameraStateSharedPtr> FrameTimeStateImp::camerasState() const {
    std::map<int, CameraStateSharedPtr> camerasState;
    for (auto iter = camerasState_.begin(); iter != camerasState_.end(); iter++) {
        camerasState[(*iter).first] = (*iter).second;
    }
    return camerasState;
}

std::map<int, std::shared_ptr<CameraStateImp>> & FrameTimeStateImp::camerasState() {
    return camerasState_;
}

BatteryStateSharedPtr FrameTimeStateImp::batteryState() const {
    auto find_iter = batteriesState_.find(0);
    if (find_iter == batteriesState_.end()) {
        return nullptr;
    }
    
    return (*find_iter).second;
}

std::shared_ptr<BatteryStateImp> FrameTimeStateImp::batteryStateImp() {
    auto find_iter = batteriesState_.find(0);
    if (find_iter == batteriesState_.end()) {
        return nullptr;
    }
    
    return (*find_iter).second;
}

void FrameTimeStateImp::set_batteryState(const std::shared_ptr<BatteryStateImp>& batteryState) {
    batteriesState_[0] = batteryState;
}

std::map<int, BatteryStateSharedPtr> FrameTimeStateImp::batteriesState() const {
    std::map<int, BatteryStateSharedPtr> batteries;
    for (auto iter = batteriesState_.begin(); iter != batteriesState_.end(); iter ++) {
        batteries[(*iter).first] = (*iter).second;
    }
    return batteries;
}

std::map<int, std::shared_ptr<BatteryStateImp>> & FrameTimeStateImp::batteriesState() {
    return batteriesState_;
}

AirLinkStateSharedPtr FrameTimeStateImp::airlinkState() const {
    return airlinkState_;
}

std::shared_ptr<AirLinkStateImp> FrameTimeStateImp::airlinkStateImp() {
    return airlinkState_;
}

void FrameTimeStateImp::set_airlinkState(const std::shared_ptr<AirLinkStateImp>& airlinkState) {
    airlinkState_ = airlinkState;
}

GOBusinessDataSharedPtr FrameTimeStateImp::goBusinessData() const {
    return goBusiness_;
}

std::shared_ptr<GOBusinessDataImp> FrameTimeStateImp::goBusinessDataImp() {
    return goBusiness_;
}

void FrameTimeStateImp::set_goBusinessData(const std::shared_ptr<GOBusinessDataImp>& goBusiness) {
    goBusiness_ = goBusiness;
}

MobileDeviceStateSharedPtr FrameTimeStateImp::mobileDeviceState() const {
    return mobileDeviceState_;
}

std::shared_ptr<MobileDeviceStateImp> FrameTimeStateImp::mobileDeviceStateImp() {
    return mobileDeviceState_;
}

void FrameTimeStateImp::set_mobileDeviceState(const std::shared_ptr<MobileDeviceStateImp>& mobileDeviceState) {
    mobileDeviceState_ = mobileDeviceState;
}

VisionStateSharedPtr FrameTimeStateImp::visionState() const {
    return visionState_;
}

std::shared_ptr<VisionStateImp> FrameTimeStateImp::visionStateImp() {
    return visionState_;
}

void FrameTimeStateImp::set_visionState(const std::shared_ptr<VisionStateImp>& visionState) {
    visionState_ = visionState;
}
