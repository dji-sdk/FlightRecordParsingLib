//
//  fr_standardization_battery_state.cpp
//  FlightRecordStandardization
//
//  Copyright © 2019 DJISDK. All rights reserved.
//

#include "fr_standardization_battery_state.hpp"

using namespace DJIFR::standardization;
using namespace DJI::FlightRecord;

BatteryStateImp::BatteryStateImp() :
voltage_(-1),
current_(-1),
temperature_(-1),
chargeRemainingInPercent_(-1),
lowBatteryWarningThreshold_(-1),
seriousLowBatteryWarningThreshold_(-1),
drone_type_(DroneType::Unknown){
    
}

BatteryStateImp::~BatteryStateImp() {
    
}

std::shared_ptr<BatteryStateImp> BatteryStateImp::clone() {
    return std::shared_ptr<BatteryStateImp>(new BatteryStateImp(*this));
}

//MARK: - Property Set & Get

int BatteryStateImp::index() const {
    return index_;
}

void BatteryStateImp::set_index(int index) {
    index_ = index;
}

int32_t BatteryStateImp::voltage() const {
    return voltage_;
}

void BatteryStateImp::set_voltage(int32_t voltage) {
    voltage_ = voltage;
}

int32_t BatteryStateImp::current() const {
    return current_;
}

void BatteryStateImp::set_current(int32_t current) {
    current_ = current;
}

double BatteryStateImp::temperature() const {
    return temperature_;
}

void BatteryStateImp::set_temperature(double temperature) {
    temperature_ = temperature;
}

std::vector<int32_t> BatteryStateImp::cellVoltages() const {
    return cellVoltages_;
}

void BatteryStateImp::set_cellVoltages(const std::vector<int32_t>& cellVoltages) {
    cellVoltages_ = cellVoltages;
}

int32_t BatteryStateImp::chargeRemainingInPercent() const {
    return chargeRemainingInPercent_;
}

void BatteryStateImp::set_chargeRemainingInPercent(int32_t chargeRemainingInPercent) {
    chargeRemainingInPercent_ = chargeRemainingInPercent;
}

int32_t BatteryStateImp::lowBatteryWarningThreshold() const {
    return lowBatteryWarningThreshold_;
}

void BatteryStateImp::set_lowBatteryWarningThreshold(int32_t lowBatteryWarningThreshold) {
    lowBatteryWarningThreshold_ = lowBatteryWarningThreshold;
}

int32_t BatteryStateImp::seriousLowBatteryWarningThreshold() const {
    return seriousLowBatteryWarningThreshold_;
}

void BatteryStateImp::set_seriousLowBatteryWarningThreshold(int32_t seriousLowBatteryWarningThreshold) {
    seriousLowBatteryWarningThreshold_ = seriousLowBatteryWarningThreshold;
}

int32_t BatteryStateImp::lifetimeRemaining() const {
    return lifetimeRemaining_;
}

void BatteryStateImp::set_lifetimeRemaining(int32_t lifetimeRemaining) {
    lifetimeRemaining_ = lifetimeRemaining;
}

int32_t BatteryStateImp::designCapacity() const {
    return designCapacity_;
}
void BatteryStateImp::set_designCapacity(int32_t designCapacity) {
    designCapacity_ = designCapacity;
}

int32_t BatteryStateImp::numberOfDischarges() const {
    return numberOfDischarges_;
}

void BatteryStateImp::set_numberOfDischarges(int32_t numberOfDischarges) {
    numberOfDischarges_ = numberOfDischarges;
}

bool BatteryStateImp::isInSingleBatteryMode() const {
    return isInSingleBatteryMode_;;
}

void BatteryStateImp::set_isInSingleBatteryMode(bool isInSingleBatteryMode) {
    isInSingleBatteryMode_ = isInSingleBatteryMode;
}

uint32_t BatteryStateImp::fullChargeCapacity() const {
    return fullChargeCapacity_;
}

void BatteryStateImp::set_fullChargeCapacity(uint32_t fullChargeCapacity) {
    fullChargeCapacity_ = fullChargeCapacity;
}

uint32_t BatteryStateImp::chargeRemaining() const {
    return chargeRemaining_;
}

void BatteryStateImp::set_chargeRemaining(uint32_t chargeRemaining) {
    chargeRemaining_ = chargeRemaining;
}

//MARK: - Private Property

DroneType BatteryStateImp::drone_type() const {
    return drone_type_;
}

void BatteryStateImp::set_drone_type(DroneType drone_type) {
    drone_type_ = drone_type;
}
