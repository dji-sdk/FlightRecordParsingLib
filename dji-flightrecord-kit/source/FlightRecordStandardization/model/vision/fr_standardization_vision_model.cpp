//
//  fr_standardization_vision_model.cpp
//  FlightRecordKitCpp
//
//

#include "fr_standardization_vision_model.hpp"

using namespace DJIFR::standardization;

ObstacleDetectionSectorImp::ObstacleDetectionSectorImp() {
    
}

ObstacleDetectionSectorImp::~ObstacleDetectionSectorImp() {
    
}

std::shared_ptr<ObstacleDetectionSectorImp> ObstacleDetectionSectorImp::clone() {
    return std::shared_ptr<ObstacleDetectionSectorImp>(new ObstacleDetectionSectorImp(*this));
}

double ObstacleDetectionSectorImp::obstacleDistanceInMeters() const {
    return obstacleDistanceInMeters_;;
}

void ObstacleDetectionSectorImp::set_obstacleDistanceInMeters(double obstacleDistanceInMeters) {
    obstacleDistanceInMeters_ = obstacleDistanceInMeters;
}

ObstacleDetectionSectorWarning ObstacleDetectionSectorImp::warningLevel() const {
    return warningLevel_;
}

void ObstacleDetectionSectorImp::set_warningLevel(ObstacleDetectionSectorWarning warningLevel) {
    warningLevel_ = warningLevel;
}

VisionDetectionStateImp::VisionDetectionStateImp() {
    
}

VisionDetectionStateImp::~VisionDetectionStateImp() {
    
}

std::shared_ptr<VisionDetectionStateImp> VisionDetectionStateImp::clone() {
    auto clone = std::shared_ptr<VisionDetectionStateImp>(new VisionDetectionStateImp(*this));
    std::vector<std::shared_ptr<ObstacleDetectionSectorImp>> detectionSectors;
    for (auto iter = detectionSectors_.begin(); iter != detectionSectors_.end(); iter ++) {
        detectionSectors.push_back((*iter)->clone());
    }
    clone->detectionSectors() = detectionSectors;
    
    return clone;
}

VisionSensorPosition VisionDetectionStateImp::position() const {
    return position_;
}

void VisionDetectionStateImp::set_position(VisionSensorPosition position) {
    position_ = position;
}

bool VisionDetectionStateImp::isSensorBeingUsed() const {
    return isSensorBeingUsed_;
}

void VisionDetectionStateImp::set_isSensorBeingUsed(bool isSensorBeingUsed) {
    isSensorBeingUsed_ = isSensorBeingUsed;
}

VisionSystemWarning VisionDetectionStateImp::systemWarning() const {
    return systemWarning_;
}

void VisionDetectionStateImp::set_systemWarning(VisionSystemWarning systemWarning) {
    systemWarning_ = systemWarning;
}

double VisionDetectionStateImp::obstacleDistanceInMeters() const {
    return obstacleDistanceInMeters_;
}

void VisionDetectionStateImp::set_obstacleDistanceInMeters(double obstacleDistanceInMeters) {
    obstacleDistanceInMeters_ = obstacleDistanceInMeters;
}

std::vector<ObstacleDetectionSectorSharedPtr> VisionDetectionStateImp::detectionSectors() const {
    std::vector<ObstacleDetectionSectorSharedPtr> clone;
    for (auto iter = detectionSectors_.begin(); iter != detectionSectors_.end(); iter ++) {
        clone.push_back((*iter));
    }
    return clone;
}

std::vector<std::shared_ptr<ObstacleDetectionSectorImp>> & VisionDetectionStateImp::detectionSectors() {
    return detectionSectors_;
}

VisionControlStateImp::VisionControlStateImp() {
    
}

VisionControlStateImp::~VisionControlStateImp() {
    
}

std::shared_ptr<VisionControlStateImp> VisionControlStateImp::clone() {
    return std::shared_ptr<VisionControlStateImp>(new VisionControlStateImp(*this));
}

bool VisionControlStateImp::isAscentLimitedByObstacle() const {
    return isAscentLimitedByObstacle_;
}

void VisionControlStateImp::set_isAscentLimitedByObstacle(bool isAscentLimitedByObstacle) {
    isAscentLimitedByObstacle_ = isAscentLimitedByObstacle;
}

bool VisionControlStateImp::isAvoidingActiveObstacleCollision() const {
    return isAvoidingActiveObstacleCollision_;
}

void VisionControlStateImp::set_isAvoidingActiveObstacleCollision(bool isAvoidingActiveObstacleCollision) {
    isAvoidingActiveObstacleCollision_ = isAvoidingActiveObstacleCollision;
}

bool VisionControlStateImp::isBraking() const {
    return isBraking_;
}

void VisionControlStateImp::set_isBraking(bool isBraking) {
    isBraking_ = isBraking;
}

bool VisionControlStateImp::isPerformingPrecisionLanding() const {
    return isPerformingPrecisionLanding_;
}

void VisionControlStateImp::set_isPerformingPrecisionLanding(bool isPerformingPrecisionLanding) {
    isPerformingPrecisionLanding_ = isPerformingPrecisionLanding;
}

VisionStateImp::VisionStateImp() {
    
}

VisionStateImp::~VisionStateImp() {
    
}

std::shared_ptr<VisionStateImp> VisionStateImp::clone() {
    auto clone = std::shared_ptr<VisionStateImp>(new VisionStateImp(*this));
    clone->set_controlState(controlState_ == nullptr ? nullptr : controlState_->clone());
    
    std::map<VisionSensorPosition, std::shared_ptr<VisionDetectionStateImp>> detectionStateMap;
    for (auto iter = detectionStateMap_.begin(); iter != detectionStateMap_.end(); iter ++) {
        detectionStateMap[(*iter).first] = (*iter).second->clone();
    }
    clone->detectionStateMap() = detectionStateMap;
    
    return clone;
}

//MARK: - Property Set & Get

bool VisionStateImp::collisionAvoidanceEnabled() const {
    return collisionAvoidanceEnabled_;
}

void VisionStateImp::set_collisionAvoidanceEnabled(bool collisionAvoidanceEnabled) {
    collisionAvoidanceEnabled_ = collisionAvoidanceEnabled;
}

VisionControlStateSharedPtr VisionStateImp::controlState() const {
    return controlState_;
}

std::shared_ptr<VisionControlStateImp> VisionStateImp::controlStateImp() {
    return controlState_;
}

void VisionStateImp::set_controlState(const std::shared_ptr<VisionControlStateImp>& controlState) {
    controlState_ = controlState;
}

std::map<VisionSensorPosition, VisionDetectionStateSharedPtr> VisionStateImp::detectionStateMap() const {
    std::map<VisionSensorPosition, VisionDetectionStateSharedPtr> map;
    for (auto iter = detectionStateMap_.begin(); iter != detectionStateMap_.end(); iter ++) {
        map[(*iter).first] = (*iter).second;
    }
    return map;
}

std::map<VisionSensorPosition, std::shared_ptr<VisionDetectionStateImp>>& VisionStateImp::detectionStateMap() {
    return detectionStateMap_;
}

