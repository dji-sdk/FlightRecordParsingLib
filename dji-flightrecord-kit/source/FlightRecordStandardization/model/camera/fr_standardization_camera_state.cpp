//
//  fr_standardization_camera_state.cpp
//  FlightRecordStandardization
//
//  Copyright © 2019 DJISDK. All rights reserved.
//

#include "fr_standardization_camera_state.hpp"

using namespace DJIFR::standardization;

CameraStateImp::CameraStateImp() :
isRecording_(false),
isShootingSinglePhoto_(false) {
    
}

CameraStateImp::~CameraStateImp() {
    
}

std::shared_ptr<CameraStateImp> CameraStateImp::clone() {
    auto clone = std::make_shared<CameraStateImp>();
    clone->set_isRecording(isRecording());
    clone->set_isShootingSinglePhoto(false);
    clone->set_isInserted(isInserted());
    clone->set_isInitializing(isInitializing());
    clone->set_hasError(hasError());
    clone->set_isVerified(isVerified());
    clone->set_isFull(isFull());
    clone->set_isFormatted(isFormatted());
    clone->set_isFormatting(isFormatting());
    clone->set_isInvalidFormat(isInvalidFormat());
    clone->set_isReadOnly(isReadOnly());
    clone->set_totalSpaceInMB(totalSpaceInMB());
    clone->set_remainingSpaceInMB(remainingSpaceInMB());
    clone->set_availableCaptureCount(availableCaptureCount());
    clone->set_availableRecordingTimeInSeconds(availableRecordingTimeInSeconds());
    
    return clone;
}

//MARK: - Property Set & Get

int CameraStateImp::index() const {
    return index_;
}

void CameraStateImp::set_index(int index) {
    index_ = index;
}

bool CameraStateImp::isRecording() const {
    return isRecording_;
}

void CameraStateImp::set_isRecording(bool isRecording) {
    isRecording_ = isRecording;
}

bool CameraStateImp::isShootingSinglePhoto() const {
    return isShootingSinglePhoto_;
}

void CameraStateImp::set_isShootingSinglePhoto(bool isShootingSinglePhoto) {
    isShootingSinglePhoto_ = isShootingSinglePhoto;
}

bool CameraStateImp::isInserted() const {
    return isInserted_;
}

void CameraStateImp::set_isInserted(bool isInserted) {
    isInserted_ = isInserted;
}

bool CameraStateImp::isInitializing() const {
    return isInitializing_;
}

void CameraStateImp::set_isInitializing(bool isInitializing) {
    isInitializing_ = isInitializing;
}

bool CameraStateImp::hasError() const {
    return hasError_;
}

void CameraStateImp::set_hasError(bool hasError) {
    hasError_ = hasError;
}

bool CameraStateImp::isVerified() const {
    return isVerified_;
}

void CameraStateImp::set_isVerified(bool isVerified) {
    isVerified_ = isVerified;
}

bool CameraStateImp::isFull() const {
    return isFull_;
}

void CameraStateImp::set_isFull(bool isFull) {
    isFull_ = isFull;
}

bool CameraStateImp::isFormatted() const {
    return isFormatted_;
}

void CameraStateImp::set_isFormatted(bool isFormatted) {
    isFormatted_ = isFormatted;
}

bool CameraStateImp::isFormatting() const {
    return isFormatting_;
}

void CameraStateImp::set_isFormatting(bool isFormatting) {
    isFormatting_ = isFormatting;
}

bool CameraStateImp::isInvalidFormat() const {
    return isInvalidFormat_;
}

void CameraStateImp::set_isInvalidFormat(bool isInvalidFormat) {
    isInvalidFormat_ = isInvalidFormat;
}

bool CameraStateImp::isReadOnly() const {
    return isReadOnly_;
}

void CameraStateImp::set_isReadOnly(bool isReadOnly) {
    isReadOnly_ = isReadOnly;
}

uint32_t CameraStateImp::totalSpaceInMB() const {
    return totalSpaceInMB_;
}

void CameraStateImp::set_totalSpaceInMB(uint32_t totalSpaceInMB) {
    totalSpaceInMB_ = totalSpaceInMB;
}

uint32_t CameraStateImp::remainingSpaceInMB() const {
    return remainingSpaceInMB_;
}

void CameraStateImp::set_remainingSpaceInMB(uint32_t remainingSpaceInMB) {
    remainingSpaceInMB_ = remainingSpaceInMB;
}

uint32_t CameraStateImp::availableCaptureCount() const {
    return availableCaptureCount_;
}

void CameraStateImp::set_availableCaptureCount(uint32_t availableCaptureCount) {
    availableCaptureCount_ = availableCaptureCount;
}

uint32_t CameraStateImp::availableRecordingTimeInSeconds() const {
    return availableRecordingTimeInSeconds_;
}

void CameraStateImp::set_availableRecordingTimeInSeconds(uint32_t availableRecordingTimeInSeconds) {
    availableRecordingTimeInSeconds_ = availableRecordingTimeInSeconds;
}

CameraMode CameraStateImp::mode() const {
    return mode_;
}

void CameraStateImp::set_mode(CameraMode mode) {
    mode_ = mode;
}
