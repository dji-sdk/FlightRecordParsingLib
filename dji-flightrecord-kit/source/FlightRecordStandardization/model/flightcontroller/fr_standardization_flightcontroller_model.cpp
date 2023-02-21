//
//  fr_standardization_flightcontroller_model.cpp
//  FlightRecordStandardization
//
//  Copyright © 2019 DJISDK. All rights reserved.
//

#include "fr_standardization_flightcontroller_model.hpp"

using namespace DJIFR::standardization;

//MARK: - VirtualStickFlightControlDataImp

VirtualStickFlightControlDataImp::VirtualStickFlightControlDataImp() :
pitch_(0),
roll_(0),
yaw_(0),
verticalThrottle_(0),
verticalControlMode_(VirtualStickVerticalControlMode::Unknown),
rollPitchControlMode_(VirtualStickRollPitchControlMode::Unknown),
yawControlMode_(VirtualStickYawControlMode::Unknown),
rollPitchCoordinateSystem_(VirtualStickFlightCoordinateSystem::Unknown) {
    
}

VirtualStickFlightControlDataImp::~VirtualStickFlightControlDataImp() {
    
}

float VirtualStickFlightControlDataImp::pitch() const {
    return pitch_;
}

void VirtualStickFlightControlDataImp::set_pitch(float pitch) {
    pitch_ = pitch;
}

float VirtualStickFlightControlDataImp::roll() const {
    return roll_;
}
void VirtualStickFlightControlDataImp::set_roll(float roll) {
    roll_ = roll;
}

float VirtualStickFlightControlDataImp::yaw() const {
    return yaw_;
}

void VirtualStickFlightControlDataImp::set_yaw(float yaw) {
    yaw_ = yaw;
}

float VirtualStickFlightControlDataImp::verticalThrottle() const {
    return verticalThrottle_;
}

void VirtualStickFlightControlDataImp::set_verticalThrottle(float verticalThrottle) {
    verticalThrottle_ = verticalThrottle;
}

VirtualStickVerticalControlMode VirtualStickFlightControlDataImp::verticalControlMode() const {
    return verticalControlMode_;
}

void VirtualStickFlightControlDataImp::set_verticalControlMode(VirtualStickVerticalControlMode verticalControlMode) {
    verticalControlMode_ = verticalControlMode;
}

VirtualStickRollPitchControlMode VirtualStickFlightControlDataImp::rollPitchControlMode() const {
    return rollPitchControlMode_;
}

void VirtualStickFlightControlDataImp::set_rollPitchControlMode(VirtualStickRollPitchControlMode rollPitchControlMode) {
    rollPitchControlMode_ = rollPitchControlMode;
}

VirtualStickYawControlMode VirtualStickFlightControlDataImp::yawControlMode() const {
    return yawControlMode_;
}

void VirtualStickFlightControlDataImp::set_yawControlMode(VirtualStickYawControlMode yawControlMode) {
    yawControlMode_ = yawControlMode;
}

VirtualStickFlightCoordinateSystem VirtualStickFlightControlDataImp::rollPitchCoordinateSystem() const {
    return rollPitchCoordinateSystem_;
}

void VirtualStickFlightControlDataImp::set_rollPitchCoordinateSystem(VirtualStickFlightCoordinateSystem rollPitchCoordinateSystem) {
    rollPitchCoordinateSystem_ = rollPitchCoordinateSystem;
}

//MARK: - FlightControllerStateImp

FlightControllerStateImp::FlightControllerStateImp() :
attitude_(nullptr),
velocity_(nullptr),
homeLocationCoordinate_(nullptr),
takeoffLocationAltitude_(0),
aircraftLocation_(nullptr),
altitude_(0),
flightMode_(FlightMode::Unknown),
gpsLevel_(GPSSignalLevel::Unknwon),
satelliteCount_(0),
remainingFlightTime_(0),
batteryPercentageNeededToLandFromCurrentHeight_(0),
batteryPercentageNeededToGoHome_(0),
smartRTHState_(SmartRTHState::Unknown),
behavior_(ConnectionFailSafeBehavior::Unknown),
virtualControlData_(nullptr),
isFailsafeEnabled_(false),
areMotorsOn_(false),
isHomeLocationSet_(false),
isLandingConfirmationNeeded_(false),
hasReachedMaxFlightHeight_(false),
hasReachedMaxFlightRadius_(false),
windWarning_(FlightWindWarning::Unknown),
countOfFlights_(0),
flightLogIndex_(0),
isFlying_(false),
smartRTHCountdown_(0),
drone_type_(0)
{
    
}

std::shared_ptr<FlightControllerStateImp> FlightControllerStateImp::clone() {
    return std::shared_ptr<FlightControllerStateImp>(new FlightControllerStateImp(*this));
}

FlightControllerStateImp::~FlightControllerStateImp() {
    
}

AttitudeSharedPtr FlightControllerStateImp::attitude() const {
    return attitude_;
}

void FlightControllerStateImp::set_attitude(const AttitudeSharedPtr& attitude) {
    attitude_ = attitude;
}

VelocitySharedPtr FlightControllerStateImp::velocity() const {
    return velocity_;
}

void FlightControllerStateImp::set_velocity(const VelocitySharedPtr& velocity) {
    velocity_ = velocity;
}

LocationCoordinate2DSharedPtr FlightControllerStateImp::homeLocationCoordinate() const {
    return homeLocationCoordinate_;
}

void FlightControllerStateImp::set_homeLocationCoordinate(const LocationCoordinate2DSharedPtr& homeLocationCoordinate) {
    homeLocationCoordinate_ = homeLocationCoordinate;
}

float FlightControllerStateImp::takeoffLocationAltitude() const {
    return takeoffLocationAltitude_;
}

void FlightControllerStateImp::set_takeoffLocationAltitude(float takeoffLocationAltitude) {
    takeoffLocationAltitude_ = takeoffLocationAltitude;
}

LocationCoordinate2DSharedPtr FlightControllerStateImp::aircraftLocation() const {
    return aircraftLocation_;
}

void FlightControllerStateImp::set_aircraftLocation(const LocationCoordinate2DSharedPtr& aircraftLocation) {
    aircraftLocation_ = aircraftLocation;
}

float FlightControllerStateImp::altitude() const {
    return altitude_;
}

void FlightControllerStateImp::set_altitude(float altitude) {
    altitude_ = altitude;
}

FlightMode FlightControllerStateImp::flightMode() const {
    return flightMode_;
}

void FlightControllerStateImp::set_flightMode(FlightMode flightMode) {
    flightMode_ = flightMode;
}

bool FlightControllerStateImp::isGPSBeingUsed() const {
    return isGPSBeingUsed_;
}

void FlightControllerStateImp::set_isGPSBeingUsed(bool isGPSBeingUsed) {
    isGPSBeingUsed_ = isGPSBeingUsed;
}

GPSSignalLevel FlightControllerStateImp::gpsLevel() const {
    return gpsLevel_;
}

void FlightControllerStateImp::set_gpsLevel(GPSSignalLevel level) {
    gpsLevel_ = level;
}

int32_t FlightControllerStateImp::satelliteCount() const {
    return satelliteCount_;
}

void FlightControllerStateImp::set_satelliteCount(int32_t satelliteCount) {
    satelliteCount_ = satelliteCount;
}

int32_t FlightControllerStateImp::remainingFlightTime() const {
    return remainingFlightTime_;
}

void FlightControllerStateImp::set_remainingFlightTime(int32_t remainingFlightTime) {
    remainingFlightTime_ = remainingFlightTime;
}

int32_t FlightControllerStateImp::batteryPercentageNeededToLandFromCurrentHeight() const {
    return batteryPercentageNeededToLandFromCurrentHeight_;
}

void FlightControllerStateImp::set_batteryPercentageNeededToLandFromCurrentHeight(int32_t batteryPercentageNeededToLandFromCurrentHeight) {
    batteryPercentageNeededToLandFromCurrentHeight_ = batteryPercentageNeededToLandFromCurrentHeight;
}

int32_t FlightControllerStateImp::batteryPercentageNeededToGoHome() const {
    return batteryPercentageNeededToGoHome_;
}

void FlightControllerStateImp::set_batteryPercentageNeededToGoHome(int32_t batteryPercentageNeededToGoHome) {
    batteryPercentageNeededToGoHome_ = batteryPercentageNeededToGoHome;
}

SmartRTHState FlightControllerStateImp::smartRTHState() const {
    return smartRTHState_;
}

void FlightControllerStateImp::set_smartRTHState(SmartRTHState smartRTHState) {
    smartRTHState_ = smartRTHState;
}

ConnectionFailSafeBehavior FlightControllerStateImp::behavior() const {
    return behavior_;
}

void FlightControllerStateImp::set_behavior(ConnectionFailSafeBehavior behavior) {
    behavior_ = behavior;
}

VirtualStickFlightControlDataSharedPtr FlightControllerStateImp::virtualControlData() const {
    return virtualControlData_;
}

void FlightControllerStateImp::set_virtualControlData(const VirtualStickFlightControlDataSharedPtr& virtualControlData) {
    virtualControlData_ = virtualControlData;
}

bool FlightControllerStateImp::isFailsafeEnabled() const {
    return isFailsafeEnabled_;
}

void FlightControllerStateImp::set_isFailsafeEnabled(bool isFailsafeEnabled) {
    isFailsafeEnabled_ = isFailsafeEnabled;
}

bool FlightControllerStateImp::areMotorsOn() const {
    return areMotorsOn_;
}

void FlightControllerStateImp::set_areMotorsOn(bool areMotorsOn) {
    areMotorsOn_ = areMotorsOn;
}

bool FlightControllerStateImp::isHomeLocationSet() const {
    return isHomeLocationSet_;
}

void FlightControllerStateImp::set_isHomeLocationSet(bool isHomeLocationSet) {
    isHomeLocationSet_ = isHomeLocationSet;
}

bool FlightControllerStateImp::isLandingConfirmationNeeded() const {
    return isLandingConfirmationNeeded_;
}

void FlightControllerStateImp::set_isLandingConfirmationNeeded(bool isLandingConfirmationNeeded) {
    isLandingConfirmationNeeded_ = isLandingConfirmationNeeded;
}

bool FlightControllerStateImp::hasReachedMaxFlightHeight() const {
    return hasReachedMaxFlightHeight_;
}

void FlightControllerStateImp::set_hasReachedMaxFlightHeight(bool hasReachedMaxFlightHeight) {
    hasReachedMaxFlightHeight_ = hasReachedMaxFlightHeight;
}

bool FlightControllerStateImp::hasReachedMaxFlightRadius() const {
    return hasReachedMaxFlightRadius_;
}

void FlightControllerStateImp::set_hasReachedMaxFlightRadius(bool hasReachedMaxFlightRadius) {
    hasReachedMaxFlightRadius_ = hasReachedMaxFlightRadius;
}

FlightWindWarning FlightControllerStateImp::windWarning() const {
    return windWarning_;
}

void FlightControllerStateImp::set_windWarning(FlightWindWarning windWarning) {
    windWarning_ = windWarning;
}

int32_t FlightControllerStateImp::countOfFlights() const {
    return countOfFlights_;
}

void FlightControllerStateImp::set_countOfFlights(int32_t countOfFlights) {
    countOfFlights_ = countOfFlights;
}

int32_t FlightControllerStateImp::flightLogIndex() const {
    return flightLogIndex_;
}

void FlightControllerStateImp::set_flightLogIndex(int32_t flightLogIndex) {
    flightLogIndex_ = flightLogIndex;
}

bool FlightControllerStateImp::isFlying() const {
    return isFlying_;
}

void FlightControllerStateImp::set_isFlying(bool isFlying) {
    isFlying_ = isFlying;
}

double FlightControllerStateImp::flightTimeInSeconds() const {
    return flightTimeInSeconds_;
}

void FlightControllerStateImp::set_flightTimeInSeconds(double flightTimeInSeconds) {
    flightTimeInSeconds_ = flightTimeInSeconds;
}

double FlightControllerStateImp::cumulativeFlightDistance() const {
    return cumulativeFlightDistance_;
}

void FlightControllerStateImp::set_cumulativeFlightDistance(double cumulativeFlightDistance) {
    cumulativeFlightDistance_ = cumulativeFlightDistance;
}

int32_t FlightControllerStateImp::smartRTHCountdown() const {
    return smartRTHCountdown_;
}

void FlightControllerStateImp::set_smartRTHCountdown(int32_t smartRTHCountdown) {
    smartRTHCountdown_ = smartRTHCountdown;
}

uint8_t FlightControllerStateImp::versionC() const {
    return versionC_;
}

void FlightControllerStateImp::set_versionC(uint8_t versionC) {
    versionC_ = versionC;
}

uint8_t FlightControllerStateImp::drone_type() const {
    return drone_type_;
}

void FlightControllerStateImp::set_drone_type(uint8_t drone_type) {
    drone_type_ = drone_type;
}
