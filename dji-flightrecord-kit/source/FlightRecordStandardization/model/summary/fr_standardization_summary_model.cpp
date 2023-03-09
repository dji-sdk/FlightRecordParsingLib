//
//  fr_standardization_summary_model.cpp
//  FlightRecordStandardization
//
//  Copyright © 2019 DJISDK. All rights reserved.
//

#include "fr_standardization_summary_model.hpp"

using namespace DJIFR::standardization;

//MARK: - ComponentInformationImp

ComponentInformationImp::ComponentInformationImp() :
index_(0),
serialNumber_("") {
    
}

ComponentInformationImp::~ComponentInformationImp() {
    
}

int32_t ComponentInformationImp::index() const {
    return index_;
}

void ComponentInformationImp::set_index(int32_t index) {
    index_ = index;
}

std::vector<int32_t> ComponentInformationImp::firmwareVersion() const {
    return firmwareVersion_;
}

void ComponentInformationImp::set_firmwareVersion(std::vector<int32_t> firmwareVersion) {
    firmwareVersion_ = firmwareVersion;
}

std::string ComponentInformationImp::serialNumber() const {
    return serialNumber_;
}

void ComponentInformationImp::set_serialNumber(const std::string& serialNumber) {
    serialNumber_ = serialNumber;
}

//MARK: - SummaryInformationImp

SummaryInformationImp::SummaryInformationImp() :
platform_(Platform::Unknown),
remoteControllerInformation_(nullptr),
flightControllerInformation_(nullptr),
aircraftName_(""),
startCoordinate_(nullptr) {
    
}

SummaryInformationImp::~SummaryInformationImp() {
    
}

Platform SummaryInformationImp::platform() const {
    return platform_;
}

void SummaryInformationImp::set_platform(Platform platform) {
    platform_ = platform;
}

std::vector<int32_t> SummaryInformationImp::appVersion() const {
    return appVersion_;
}

void SummaryInformationImp::set_appVersion(const std::vector<int32_t>& appVersion) {
    appVersion_ = appVersion;
}

std::map<int32_t, ComponentInformationSharedPtr> SummaryInformationImp::batteriesInformation() const {
    std::map<int32_t, ComponentInformationSharedPtr> batteries;
    for (auto iter = batteriesInformation_.begin(); iter != batteriesInformation_.end(); iter ++) {
        batteries[(*iter).first] = (*iter).second;
    }
    
    return batteries;
}

std::map<int32_t, std::shared_ptr<ComponentInformationImp>>* SummaryInformationImp::batteriesInformationImp() {
    return &batteriesInformation_;
}

std::map<int32_t, ComponentInformationSharedPtr> SummaryInformationImp::camerasInformation() const {
    std::map<int32_t, ComponentInformationSharedPtr> cameras;
    for (auto iter = camerasInformation_.begin(); iter != camerasInformation_.end(); iter ++) {
        cameras[(*iter).first] = (*iter).second;
    }
    return cameras;
}

std::map<int32_t, std::shared_ptr<ComponentInformationImp>>* SummaryInformationImp::camerasInformationImp() {
    return &camerasInformation_;
}

std::map<int32_t, ComponentInformationSharedPtr> SummaryInformationImp::gimbalsInformation() const {
    std::map<int32_t, ComponentInformationSharedPtr> gimbals;
    for (auto iter = gimbalsInformation_.begin(); iter != gimbalsInformation_.end(); iter ++) {
        gimbals[(*iter).first] = (*iter).second;
    }
    return gimbals;
}

std::map<int32_t, std::shared_ptr<ComponentInformationImp>>* SummaryInformationImp::gimbalsInformationImp() {
    return &gimbalsInformation_;
}

ComponentInformationSharedPtr SummaryInformationImp::remoteControllerInformation() const {
    return remoteControllerInformation_;
}

std::shared_ptr<ComponentInformationImp> SummaryInformationImp::remoteControllerInformationImp() {
    return remoteControllerInformation_;
}

void SummaryInformationImp::set_remoteControllerInformation(const std::shared_ptr<ComponentInformationImp>& remoteControllerInformation) {
    remoteControllerInformation_ = remoteControllerInformation;
}

ComponentInformationSharedPtr SummaryInformationImp::flightControllerInformation() const {
    return flightControllerInformation_;
}

std::shared_ptr<ComponentInformationImp> SummaryInformationImp::flightControllerInformationImp() {
    return flightControllerInformation_;
}

void SummaryInformationImp::set_flightControllerInformation(const std::shared_ptr<ComponentInformationImp>& flightControllerInformation) {
    flightControllerInformation_ = flightControllerInformation;
}

std::string SummaryInformationImp::aircraftName() const {
    return aircraftName_;
}

void SummaryInformationImp::set_aircraftName(const std::string& aircraftName) {
    aircraftName_ = aircraftName;
}

double SummaryInformationImp::startTime() const {
    return startTime_;
}

void SummaryInformationImp::set_startTime(double startTime) {
    startTime_ = startTime;
}

LocationCoordinate2DSharedPtr SummaryInformationImp::startCoordinate() const {
    return startCoordinate_;
}

void SummaryInformationImp::set_startCoordinate(const LocationCoordinate2DSharedPtr& startCoordinate) {
    startCoordinate_ = startCoordinate;
}

float SummaryInformationImp::totalDistance() const {
    return totalDistance_;
}

void SummaryInformationImp::set_totalDistance(float totalDistance) {
    totalDistance_ = totalDistance;
}

double SummaryInformationImp::totalTime() const {
    return totalTime_;
}

void SummaryInformationImp::set_totalTime(double totalTime) {
    totalTime_ = totalTime;
}

int SummaryInformationImp::samplingRate() const {
    return samplingRate_;
}

void SummaryInformationImp::set_samplingRate(int samplingRate) {
    samplingRate_ = samplingRate;
}

float SummaryInformationImp::maxHeight() const {
    return maxHeight_;
}

void SummaryInformationImp::set_maxHeight(float maxHeight) {
    maxHeight_ = maxHeight;
}

float SummaryInformationImp::maxHorizontalSpeed() const {
    return maxHorizontalSpeed_;
}

void SummaryInformationImp::set_maxHorizontalSpeed(float maxHorizontalSpeed) {
    maxHorizontalSpeed_ = maxHorizontalSpeed;
}

float SummaryInformationImp::maxVirticalSpeed() const {
    return maxVirticalSpeed_;
}

void SummaryInformationImp::set_maxVirticalSpeed(float maxVirticalSpeed) {
    maxVirticalSpeed_ = maxVirticalSpeed;
}

std::string SummaryInformationImp::uuid() const {
    return uuid_;
}

void SummaryInformationImp::set_uuid(const std::string& uuid) {
    uuid_ = uuid;
}

DJI::FlightRecord::ProductType SummaryInformationImp::product_type() const {
    return product_type_;
}

void SummaryInformationImp::set_product_type(DJI::FlightRecord::ProductType product_type) {
    product_type_ = product_type;
}
