//
//  fr_standardization_rc_model.cpp
//  FlightRecordStandardization
//
//  Copyright © 2019 DJISDK. All rights reserved.
//

#include "fr_standardization_rc_model.hpp"

using namespace DJIFR::standardization;

//MARK: - StickImp

StickImp::StickImp() :
horizontalPosition_(0),
verticalPosition_(0) {
    
}

StickImp::~StickImp() {
    
}

int32_t StickImp::horizontalPosition() const {
    return horizontalPosition_;
}

void StickImp::set_horizontalPosition(int32_t horizontalPosition) {
    horizontalPosition_ = horizontalPosition;
}

int32_t StickImp::verticalPosition() const {
    return verticalPosition_;
}

void StickImp::set_verticalPosition(int32_t verticalPosition) {
    verticalPosition_ = verticalPosition;
}

//MARK: - RCRightWheelImp

RCRightWheelImp::RCRightWheelImp():
isPresent_(false),
isTurned_(false),
isClicked_(false),
value_(0) {
    
}

RCRightWheelImp::~RCRightWheelImp() {
    
}

bool RCRightWheelImp::isPresent() const {
    return isPresent_;
}

void RCRightWheelImp::set_isPresent(bool isPresent) {
    isPresent_ = isPresent;
}

bool RCRightWheelImp::isTurned() const {
    return isTurned_;
}

void RCRightWheelImp::set_isTurned(bool isTurned) {
    isTurned_ = isTurned;
}

bool RCRightWheelImp::isClicked() const {
    return isClicked_;
}

void RCRightWheelImp::set_isClicked(bool isClicked) {
    isClicked_ = isClicked;
}

int32_t RCRightWheelImp::value() const {
    return value_;
}

void RCRightWheelImp::set_value(int32_t value) {
    value_ = value;
}

//MARK: - RCButtonImp

RCButtonImp::RCButtonImp() {
    
}

RCButtonImp::~RCButtonImp() {
    
}

bool RCButtonImp::isPresent() const {
    return isPresent_;
}

void RCButtonImp::set_isPresent(bool isPresent) {
    isPresent_ = isPresent;
}

bool RCButtonImp::isClicked() const {
    return isClicked_;
}

void RCButtonImp::set_isClicked(bool isClicked) {
    isClicked_ = isClicked;
}

//MARK: - RCGPSData

RCGPSTimeImp::RCGPSTimeImp() {
    
}

RCGPSTimeImp::~RCGPSTimeImp() {
    
}

uint8_t RCGPSTimeImp::hour() const {
    return hour_;
}

void RCGPSTimeImp::set_hour(uint8_t hour) {
    hour_ = hour;
}

uint8_t RCGPSTimeImp::minute() const {
    return minute_;
}

void RCGPSTimeImp::set_minute(uint8_t minute) {
    minute_ = minute;
}

uint8_t RCGPSTimeImp::second() const {
    return second_;
}

void RCGPSTimeImp::set_second(uint8_t second) {
    second_ = second;
}

uint16_t RCGPSTimeImp::year() const {
    return year_;
}

void RCGPSTimeImp::set_year(uint16_t year) {
    year_ = year;
}

uint8_t RCGPSTimeImp::month() const {
    return month_;
}

void RCGPSTimeImp::set_month(uint8_t month) {
    month_ = month;
}

uint8_t RCGPSTimeImp::day() const {
    return day_;
}

void RCGPSTimeImp::set_day(uint8_t day) {
    day_ = day;
}

RCGPSDataImp::RCGPSDataImp() {
    
}

RCGPSDataImp::~RCGPSDataImp() {
    
}

RCGPSTimeSharedPtr RCGPSDataImp::time() const {
    return time_;
}

void RCGPSDataImp::set_time(const std::shared_ptr<RCGPSTimeImp>& time) {
    time_ = time;
}

LocationCoordinate2DSharedPtr RCGPSDataImp::location() const {
    return location_;
}

void RCGPSDataImp::set_location(const std::shared_ptr<LocationCoordinate2DImp>& location) {
    location_ = location;
}

float RCGPSDataImp::eastSpeed() const {
    return eastSpeed_;
}

void RCGPSDataImp::set_eastSpeed(float speed) {
    eastSpeed_ = speed;
}

float RCGPSDataImp::northSpeed() const {
    return northSpeed_;
}

void RCGPSDataImp::set_northSpeed(float northSpeed) {
    northSpeed_ = northSpeed;
}

int RCGPSDataImp::satelliteCount() const {
    return satelliteCount_;
}

void RCGPSDataImp::set_satelliteCount(int satelliteCount) {
    satelliteCount_ = satelliteCount;
}

float RCGPSDataImp::accuracy() const {
    return accuracy_;
}

void RCGPSDataImp::set_accuracy(float accuracy) {
    accuracy_ = accuracy;
}

bool RCGPSDataImp::isValid() const {
    return isValid_;
}

void RCGPSDataImp::set_isValid(bool isValid) {
    isValid_ = isValid;
}

//MARK: - RCHardwareStateImp

RCHardwareStateImp::RCHardwareStateImp() :
leftStick_(nullptr),
rightStick_(nullptr),
leftWheel_(0),
rightWheel_(nullptr),
flightModeSwitch_(RCFlightModelSwitch::Unknown),
goHomeButton_(nullptr),
recordButton_(nullptr),
shutterButton_(nullptr),
playbackButton_(nullptr),
pauseButton_(nullptr),
style_(RCAircraftMappingStyle::Unknown) {
    
}

RCHardwareStateImp::~RCHardwareStateImp() {
    leftStick_ = nullptr;
    rightStick_ = nullptr;
    rightWheel_ = nullptr;
    goHomeButton_ = nullptr;
    recordButton_ = nullptr;
    shutterButton_ = nullptr;
    playbackButton_ = nullptr;
    pauseButton_ = nullptr;
}

std::shared_ptr<RCHardwareStateImp> RCHardwareStateImp::clone() {
    return std::shared_ptr<RCHardwareStateImp>(new RCHardwareStateImp(*this));
}

StickSharedPtr RCHardwareStateImp::leftStick() const {
    return leftStick_;
}

void RCHardwareStateImp::set_leftStick(const StickSharedPtr& leftStick) {
    leftStick_ = leftStick;
}

StickSharedPtr RCHardwareStateImp::rightStick() const {
    return rightStick_;
}

void RCHardwareStateImp::set_rightStick(const StickSharedPtr& rightStick) {
    rightStick_ = rightStick;
}

int32_t RCHardwareStateImp::leftWheel() const {
    return leftWheel_;
}

void RCHardwareStateImp::set_leftWheel(int32_t leftWheel) {
    leftWheel_ = leftWheel;
}

RCRightWheelSharedPtr RCHardwareStateImp::rightWheel() const {
    return rightWheel_;
}

void RCHardwareStateImp::set_rightWheel(const RCRightWheelSharedPtr& rightWheel) {
    rightWheel_ = rightWheel;
}

RCFlightModelSwitch RCHardwareStateImp::flightModeSwitch() const {
    return flightModeSwitch_;
}

void RCHardwareStateImp::set_flightModeSwitch(RCFlightModelSwitch flightModeSwitch) {
    flightModeSwitch_ = flightModeSwitch;
}

RCButtonSharedPtr RCHardwareStateImp::goHomeButton() const {
    return goHomeButton_;
}

void RCHardwareStateImp::set_goHomeButton(const RCButtonSharedPtr& goHomeButton) {
    goHomeButton_ = goHomeButton;
}

RCButtonSharedPtr RCHardwareStateImp::recordButton() const {
    return recordButton_;
}

void RCHardwareStateImp::set_recordButton(const RCButtonSharedPtr& recordButton) {
    recordButton_ = recordButton;
}

RCButtonSharedPtr RCHardwareStateImp::shutterButton() const {
    return shutterButton_;
}

void RCHardwareStateImp::set_shutterButton(const RCButtonSharedPtr& shutterButton) {
    shutterButton_ = shutterButton;
}

RCButtonSharedPtr RCHardwareStateImp::playbackButton() const {
    return playbackButton_;
}

void RCHardwareStateImp::set_playbackButton(const RCButtonSharedPtr& playbackButton) {
    playbackButton_ = playbackButton;
}

RCButtonSharedPtr RCHardwareStateImp::pauseButton() const {
    return pauseButton_;
}

void RCHardwareStateImp::set_pauseButton(const RCButtonSharedPtr& pauseButton) {
    pauseButton_ = pauseButton;
}

RCAircraftMappingStyle RCHardwareStateImp::style() const {
    return style_;
}

void RCHardwareStateImp::set_style(RCAircraftMappingStyle style) {
    style_ = style;
}

RCGPSDataSharedPtr RCHardwareStateImp::GPSData() const {
    return GPSData_;
}

void RCHardwareStateImp::set_GPSData(const RCGPSDataSharedPtr& GPSData) {
    GPSData_ = GPSData;
}
