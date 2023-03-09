//
//  fr_standardization_battery_filler.cpp
//  FlightRecordStandardization
//
//  Copyright © 2019 DJISDK. All rights reserved.
//

#include "fr_standardization_battery_filler.hpp"
#include <model/protocol/fr_protocol.h>
#include <string.h>
#include <model/protocol/fr_protocol.h>

using namespace DJIFR::standardization;
using namespace DJI::FlightRecord;

//MARK: - CenterBatteryFlightRecordDataType

static bool FillCenterBattery(const dji_centerboard_push_battery_common_info_push& data_source,
                              std::shared_ptr<BatteryStateImp>& output) {
    output->set_voltage(data_source.current_voltage);
    
    output->set_current(data_source.current);
    
    output->set_temperature(data_source.temperature / 10.0 - 273.15);
    
    output->set_fullChargeCapacity(data_source.full_capacity);
    
    output->set_lifetimeRemaining(data_source.battery_life);
    
    output->set_chargeRemaining(data_source.current_capacity);
    
    output->set_numberOfDischarges(data_source.batery_circle_time);
    
    int numberOfCells = 6;
    switch (output->drone_type()) {
        case DroneType::YQqHWaFYevzieChe:
        case DroneType::axPYBMhqOPxIAmRT:
        case DroneType::gwijeEWNaJaeGehp:
        case DroneType::DctuROpGZjRKFcMe:
        case DroneType::YQqHWaFYevzieChe2:
        case DroneType::zbrTIBekxqBMpinl:
        case DroneType::jzdPaWJwlLoyHJVW:
        case DroneType::KlVwDfaUzMhdaFSv:
        case DroneType::oImFwySwNIGpDxKw:
        case DroneType::sQBPYEgXEgrpdfrj:
        case DroneType::iJauKGIrFHvVAAKZ:
        case DroneType::GmarlGbRlqfSoaKD:
        case DroneType::EbeKfeODxZwEYpPS:
        case DroneType::iUDZbWKZULbBLQaC:
        case DroneType::eaaxmyeNLEOTJxYR:
        case DroneType::nZgzsaZeSVoFDbCU:
        case DroneType::VajTqWfawuZTCdTz:
        case DroneType::CMDBsWvfrkHQsQzP:
        case DroneType::gvEBDHARYJjdhoer:
        case DroneType::xtRdpvrXtxzvwDzF:
        case DroneType::VgtTrHQftoHtijqi:
            numberOfCells = 6;
            break;
        case DroneType::eXWvzQSyEIakaYNB:
        case DroneType::SjtZVcHLcFvOrATk:
        case DroneType::kqZiGqPiBuJtGbXI:
        case DroneType::yjPSxNFfUVSgCwsk:
        case DroneType::eXWvzQSyEIakaYNBE:
        case DroneType::dYxdHETreaRpuiyw:
        case DroneType::NJaWiOHsBzaJEsKG:
        case DroneType::LnJMmgAzSGznmAhd:
        case DroneType::eIlvuUOAbBgHAEbk:
        case DroneType::hRTDkEYSnjeHrRQl:
        case DroneType::tuEiAQlJpLvETOaR:
        case DroneType::LJuBJkTjHePPllir:
            numberOfCells = 4;
            break;
        case DroneType::dfolRWzAEaPrGlNw:
        case DroneType::dZHFAjNYqzCRJVjl:
        case DroneType::BHjzymzgwTEeueKI:
            numberOfCells = 3;
            break;
            
        default:
            break;
    }
    
    int max_cell_count = sizeof(dji_center_single_battery_voltage) / sizeof(uint16_t);
    std::vector<int32_t> cellVotages;
    for (int i = 0; i < numberOfCells && i < max_cell_count; i ++) {
        uint16_t cell_voltage = data_source.single_batterys.current_voltage[i];
        if (cell_voltage == 0 ||
            cell_voltage == 2 ||
            cell_voltage > 10000) { // a workaround for P3 battery
            continue;
        }
        
        cellVotages.push_back(cell_voltage);
    }
    output->set_cellVoltages(cellVotages);
    
    return true;
}

//MARK: - OSDFlightRecordDataType

static bool FillOSDData(const dji_fc_osd_push& data_source,
                        std::shared_ptr<BatteryStateImp>& output) {
    
    output->set_drone_type((DroneType)data_source.droneType);
    
    return true;
}

//MARK: - PushedBatteryFlightRecordDataType

static bool FillPushBattery(const dji_fc_electricity_push& data_source,
                            std::shared_ptr<BatteryStateImp>& output) {
    output->set_chargeRemainingInPercent(data_source.power_percent);
    
    output->set_lowBatteryWarningThreshold(data_source.battery_warning_value);
    
    output->set_seriousLowBatteryWarningThreshold(data_source.serious_battery_warning_value);
    
    int single_battery_flag = (1 << 15);
    output->set_isInSingleBatteryMode(data_source.smart_battery_state & single_battery_flag);
    
    return true;
}

//MARK: - SmartBatteryGroupDataType

static bool FillSmartBattery(void *buffer,
                             long length,
                             std::map<int, std::shared_ptr<BatteryStateImp>> &output) {
    if (length <= 2) {
        return false;
    }
    
    FlightRecordSmartbatteryGroupDataType dataType;
    memcpy(&dataType, buffer, sizeof(uint8_t));
    
    long bufferLeft = length - sizeof(uint8_t);
    
    int index = 0;
    bool needOffset = false;
    if (output.size() > 0) {
        switch ((*output.begin()).second->drone_type()) {
            case DJI::FlightRecord::DroneType::YQqHWaFYevzieChe2:
            case DJI::FlightRecord::DroneType::zbrTIBekxqBMpinl:
            case DJI::FlightRecord::DroneType::jzdPaWJwlLoyHJVW:
            case DJI::FlightRecord::DroneType::KlVwDfaUzMhdaFSv:
            case DJI::FlightRecord::DroneType::oImFwySwNIGpDxKw:
            case DJI::FlightRecord::DroneType::sQBPYEgXEgrpdfrj:
            case DJI::FlightRecord::DroneType::iJauKGIrFHvVAAKZ:
            case DJI::FlightRecord::DroneType::GmarlGbRlqfSoaKD:
                needOffset = true;
                break;
                
            default:
                break;
        }
    }
    
    switch (dataType) {
        case SmartbatteryGroupDataType_StaticInfo: {
            dji_smart_battery_get_static_info_ios internalData;

            if (bufferLeft < sizeof(dji_smart_battery_get_static_info_ios)) {
                return false;
            }

            memcpy(&internalData, (uint8_t*)buffer + 1, sizeof(dji_smart_battery_get_static_info_ios));
            
            if (needOffset && internalData.index == 0) {
                return true;
            }
            
            int index = needOffset ? internalData.index - 1 : internalData.index;
            if (index > 6) {
                return false;
            }
            
            auto find_iter = output.find(index);
            std::shared_ptr<BatteryStateImp> battery;
            if (find_iter == output.end()) {
                battery = std::make_shared<BatteryStateImp>();
                battery->set_index(internalData.index - 1);
                output[index] = battery;
            } else {
                battery = (*find_iter).second;
            }
            
            battery->set_lifetimeRemaining(internalData.battery_life);
            battery->set_designCapacity(internalData.designed_capacity);
            battery->set_numberOfDischarges(internalData.loop_times);
        }
            break;
        case SmartbatteryGroupDataType_DynamicInfo: {
            dji_battery_dynamic_info internalData;
            
            if (bufferLeft < sizeof(dji_battery_dynamic_info)) {
                return false;
            }
            
            memcpy(&internalData, (uint8_t*)buffer + 1, sizeof(dji_battery_dynamic_info));
            
            if (needOffset && internalData.index == 0) {
                return true;
            }
            
            int index = needOffset ? internalData.index - 1 : internalData.index;
            if (index > 6) {
                return false;
            }
            
            auto find_iter = output.find(index);
            std::shared_ptr<BatteryStateImp> battery;
            if (find_iter == output.end()) {
                battery = std::make_shared<BatteryStateImp>();
                battery->set_index(internalData.index - 1);
                output[index] = battery;
            } else {
                battery = (*find_iter).second;
            }
            
            battery->set_voltage(internalData.current_voltage);
            battery->set_current(internalData.current_current);
            battery->set_temperature(internalData.temperature * 0.1);
            battery->set_chargeRemainingInPercent(internalData.capacity_percent);
            battery->set_fullChargeCapacity(internalData.full_capacity);
            battery->set_chargeRemaining(internalData.remained_capacity);
        }
            break;
        case SmartbatteryGroupDataType_SingleVoltage: {
            dji_cell_voltage_info internalData;
            
            if (bufferLeft < sizeof(dji_cell_voltage_info)) {
                return false;
            }
            
            memcpy(&internalData, (uint8_t*)buffer + 1, sizeof(dji_cell_voltage_info));
            
            size_t finalInternalDataLength = sizeof(dji_cell_voltage_info) + sizeof(uint16_t) * internalData.cell_count;
            if (finalInternalDataLength > bufferLeft) {
                return false;
            }
            dji_cell_voltage_info *finalInternalData = (dji_cell_voltage_info *)malloc(finalInternalDataLength);
            memcpy(finalInternalData, (uint8_t *)buffer + 1, finalInternalDataLength);
            
            if (needOffset && internalData.index == 0) {
                free(finalInternalData);
                return true;
            }
            
            int index = needOffset ? internalData.index - 1 : internalData.index;
            if (index > 6) {
                return false;
            }
            
            auto find_iter = output.find(index);
            std::shared_ptr<BatteryStateImp> battery;
            if (find_iter == output.end()) {
                battery = std::make_shared<BatteryStateImp>();
                battery->set_index(internalData.index - 1);
                output[index] = battery;
            } else {
                battery = (*find_iter).second;
            }
            
            std::vector<int32_t> cells;
            for (int i = 0; i < finalInternalData->cell_count; i ++) {
                cells.push_back(finalInternalData->cell_voltage[i]);
            }
            battery->set_cellVoltages(cells);
            
            free(finalInternalData);
        }
            break;
            
        default:
            break;
    }
    
    return true;
}

//MARK: - Public

bool DJIFR::standardization::Filler(std::map<int, std::shared_ptr<BatteryStateImp>> &output,
                                    FlightRecordDataType data_type,
                                    uint8_t *buffer,
                                    uint64_t length) {
    switch (data_type) {
        case OSDFlightRecordDataType:
        {
            dji_fc_osd_push data_source = {0};
            uint64_t data_length = std::min(length, (uint64_t)sizeof(data_source));
            if (data_length <= 0) {
                return false;
            }
            
            memcpy(&data_source, buffer, data_length);
            
            std::shared_ptr<BatteryStateImp> battery = nullptr;
            auto find_iter = output.begin();
            if (find_iter == output.end()) {
                return true;
            }
            
            battery = (*find_iter).second;
            
            return FillOSDData(data_source, battery);
        }
            break;
        case CenterBatteryFlightRecordDataType:
        {
            dji_centerboard_push_battery_common_info_push data_source = {0};
            uint64_t data_length = std::min(length, (uint64_t)sizeof(data_source));
            if (data_length <= 0) {
                return false;
            }
            
            memcpy(&data_source, buffer, data_length);
            
            std::shared_ptr<BatteryStateImp> battery = nullptr;
            auto find_iter = output.find(0);
            if (find_iter == output.end()) {
                battery = std::make_shared<BatteryStateImp>();
                output[0] = battery;
            } else {
                battery = (*find_iter).second;
            }
            
            return FillCenterBattery(data_source, battery);
        }
            break;
        case PushedBatteryFlightRecordDataType:
        {
            dji_fc_electricity_push data_source = {0};
            uint64_t data_length = std::min(length, (uint64_t)sizeof(data_source));
            if (data_length <= 0) {
                return false;
            }
            
            memcpy(&data_source, buffer, data_length);
            
            std::shared_ptr<BatteryStateImp> battery = nullptr;
            auto find_iter = output.find(0);
            if (find_iter == output.end()) {
                battery = std::make_shared<BatteryStateImp>();
                output[0] = battery;
            } else {
                battery = (*find_iter).second;
            }
            
            return FillPushBattery(data_source, battery);
        }
            break;
        case SmartBatteryGroupDataType:
        {
            return FillSmartBattery(buffer, length, output);
        }
            break;
            
        default:
            break;
    }
    
    return false;
}
