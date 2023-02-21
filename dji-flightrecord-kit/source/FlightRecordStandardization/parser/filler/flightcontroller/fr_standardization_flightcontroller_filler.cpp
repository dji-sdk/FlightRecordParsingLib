//
//  fr_standardization_flightcontroller_filler.cpp
//  FlightRecordStandardization
//
//  Copyright © 2019 DJISDK. All rights reserved.
//

#include "fr_standardization_flightcontroller_filler.hpp"
#include <model/protocol/fr_protocol.h>
#include "ZucGZjOtwWrgqCCe.h"
#include <Utils/math/FlightRecordMaths.h>
#include <model/protocol/fr_protocol.h>
#include <model/protocol/dji_product_type.h>
#include <string.h>

using namespace DJIFR::standardization;
using namespace DJI::FlightRecord;

//MARK: - OSDFlightRecordDataType

static bool FillOSDData(const dji_fc_osd_push& data_source,
                        std::shared_ptr<FlightControllerStateImp>& output) {
    auto attitude = std::make_shared<AttitudeImp>(data_source.pitch, data_source.roll, data_source.yaw);
    output->set_attitude(attitude);
    
    auto velocity = std::make_shared<VelocityImp>(data_source.speed_x * 0.1, data_source.speed_y * 0.1, data_source.speed_z * 0.1);
    output->set_velocity(velocity);
    
    auto latitude_degree = Rad2deg(data_source.latitude);
    auto longitude_degree = Rad2deg(data_source.longitude);
    
    auto aircraft_location = std::make_shared<LocationCoordinate2DImp>(latitude_degree, longitude_degree);
    output->set_aircraftLocation(aircraft_location);
    
    output->set_altitude(data_source.barometer_height * 0.1);
    
    output->set_flightMode((FlightMode)data_source.control_mode);
    
    output->set_isGPSBeingUsed(data_source.isGPSValid);
    
    output->set_gpsLevel((GPSSignalLevel)data_source.gpsSignalLevel);
    
    output->set_satelliteCount(data_source.gps_num);
    
    output->set_versionC(data_source.versionC);
    
    output->set_drone_type(data_source.droneType);
    
    output->set_isFailsafeEnabled(data_source.rc_outcontrol);
    
    output->set_areMotorsOn(data_source.isMotorUp);
    
    output->set_countOfFlights(data_source.startUpTimes);
    
    output->set_flightTimeInSeconds(data_source.lastFlightTime * 0.1f);
    
    output->set_isFlying((AircraftPosition)data_source.groundOrSky == AircraftPosition::In_the_air);
    
    return true;
}

//MARK: - OSDHomeFlightRecordDataType

static bool FillOSDHome(const dji_fc_fc_osd_lowfreq_push& data_source,
                        std::shared_ptr<FlightControllerStateImp>& output) {
    
    auto home_location = std::make_shared<LocationCoordinate2DImp>(Rad2deg(data_source.latitude), Rad2deg(data_source.longitude));
    output->set_homeLocationCoordinate(home_location);
    output->set_takeoffLocationAltitude(data_source.altitude);
    
    // if there is home location.
    output->set_isHomeLocationSet(true);
    
    output->set_hasReachedMaxFlightHeight(data_source.isNearHeightLimit);
    
    output->set_hasReachedMaxFlightRadius(data_source.isNearDistanceLimit);
    
    if (data_source.gale_serious_warning) {
        output->set_windWarning(FlightWindWarning::Level2);
    } else if (data_source.gale_warning) {
        output->set_windWarning(FlightWindWarning::Level1);
    } else {
        output->set_windWarning(FlightWindWarning::Level0);
    }
    
    output->set_flightLogIndex(data_source.currentFlightRecordIndex);
    
    return true;
}

//MARK: - MCParamDataType

static bool FillMCParam(const DJIFlightRecordCollectMCParamStruct& data_source,
                        std::shared_ptr<FlightControllerStateImp>& output) {
    
    output->set_behavior((ConnectionFailSafeBehavior)data_source.failSafeProtection);
    
    return true;
}

//MARK: - AppVirtualStickDataType

static bool FillVirtualStick(const GSJoystickData& joystick,
                             std::shared_ptr<FlightControllerStateImp>& output) {
    
    auto virtual_stick = std::make_shared<VirtualStickFlightControlDataImp>();
    
    virtual_stick->set_pitch(joystick.mPitch);
    virtual_stick->set_roll(joystick.mRoll);
    
    if (output->versionC() >= 16 &&
        (DroneType)output->drone_type() >= DroneType::dfolRWzAEaPrGlNw &&
        (DroneType)output->drone_type() != DroneType::DctuROpGZjRKFcMe) {
        virtual_stick->set_yaw(joystick.mThrottle);
        virtual_stick->set_verticalThrottle(joystick.mYaw);
    }
    
    uint8_t vertial_control_mode = joystick.mFlag;
    vertial_control_mode = (vertial_control_mode >> 4) & 0x03;
    virtual_stick->set_verticalControlMode((VirtualStickVerticalControlMode)vertial_control_mode);
    
    uint8_t roll_pitch_control_mode = joystick.mFlag;
    roll_pitch_control_mode = (roll_pitch_control_mode >> 6) & 0x03;
    virtual_stick->set_rollPitchControlMode((VirtualStickRollPitchControlMode)roll_pitch_control_mode);
    
    uint8_t yaw_control_mode = joystick.mFlag;
    yaw_control_mode = (yaw_control_mode >> 3) & 0x01;
    virtual_stick->set_yawControlMode((VirtualStickYawControlMode)yaw_control_mode);
    
    uint8_t roll_pitch_coordinateSystem = joystick.mFlag;
    roll_pitch_coordinateSystem = (roll_pitch_coordinateSystem >> 1) & 0x3;
    virtual_stick->set_yawControlMode((VirtualStickYawControlMode)roll_pitch_coordinateSystem);
    
    output->set_virtualControlData(virtual_stick);
    
    return true;
}

//MARK: - VisionGroupDataType

static bool FillVisionGroupDataType(const TMEcHTnPNccJUFVk *data_source,
                                    std::shared_ptr<FlightControllerStateImp>& output) {
    output->set_isLandingConfirmationNeeded(data_source->avoid_ground_force_landing_flag);
    
    return true;
}

//MARK: - PushedBatteryFlightRecordDataType

static SmartRTHState ConvertToSmartRTHState(const dji_fc_electricity_push& data_source) {
    switch (data_source.need_gohome) {
        case 0:
        {
            if (data_source.cancel_count > 0) {
                return SmartRTHState::CountingDown;
            } else {
                return SmartRTHState::Idle;
            }
        }
            break;
        case 1:
            return SmartRTHState::Executed;
        case 2:
            return SmartRTHState::Cancelled;
            
        default:
            break;
    }
    
    return SmartRTHState::Unknown;
}

static bool FillPushedBattery(const dji_fc_electricity_push& data_source,
                              std::shared_ptr<FlightControllerStateImp>& output) {
    output->set_remainingFlightTime(data_source.remain_fly_time);
    
    output->set_batteryPercentageNeededToLandFromCurrentHeight(data_source.land_electricity);
    
    output->set_batteryPercentageNeededToGoHome(data_source.gohome_electricity);
    
    output->set_smartRTHState(ConvertToSmartRTHState(data_source));
    
    output->set_smartRTHCountdown(data_source.cancel_count);
    
    return true;
}

//MARK: - Public

bool DJIFR::standardization::Filler(std::shared_ptr<FlightControllerStateImp>& output,
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
            return FillOSDData(data_source, output);
        }
            break;
        case OSDHomeFlightRecordDataType:
        {
            dji_fc_fc_osd_lowfreq_push data_source = {0};
            uint64_t data_length = std::min(length, (uint64_t)sizeof(data_source));
            if (data_length <= 0) {
                return false;
            }
            
            memcpy(&data_source, buffer, data_length);
            return FillOSDHome(data_source, output);
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
            return FillPushedBattery(data_source, output);
        }
            break;
        case MCParamDataType:
        {
            DJIFlightRecordCollectMCParamStruct data_source = {0};
            uint64_t data_length = std::min(length, (uint64_t)sizeof(data_source));
            
            if (data_length <= 0) {
                return false;
            }
            
            memcpy(&data_source, buffer, data_length);
            return FillMCParam(data_source, output);
        }
            break;
        case AppVirtualStickDataType:
        {
            GSJoystickData data_source = {0};
            uint64_t data_length = std::min(length, (uint64_t)sizeof(data_source));
            
            if (data_length <= 0) {
                return false;
            }
            
            memcpy(&data_source, buffer, data_length);
            return FillVirtualStick(data_source, output);
        }
            break;
        case VisionGroupDataType:
        {
            if (buffer == nullptr || length <= 2) {
                return false;
            }
            
            // using to get the buffer data;
            auto readBlockBody = [](void *readBuffer, long readBufferLength, void *dstPtr, long dstSize, long *needOffset) -> bool {
                long needOffsetValue = *needOffset;
                if (needOffsetValue + dstSize >= readBufferLength) {
                    return false;
                }
                
                uint8_t *dstPtrSrc = (uint8_t *)readBuffer + needOffsetValue;
                memcpy(dstPtr, dstPtrSrc, dstSize);
                needOffsetValue += dstSize;
                
                if (needOffsetValue + 1 > readBufferLength) {
                    return false;
                }
                
                uint8_t endFlag;
                uint8_t *endFlagSrc = (uint8_t *)readBuffer + needOffsetValue;
                memcpy(&endFlag, endFlagSrc, sizeof(endFlag));
                needOffsetValue += sizeof(endFlag);
                
                if (endFlag != VisionGroupDataType_End) {
                    return false;
                }
                
                *needOffset = needOffsetValue;
                
                return true;
            };
            
            // using to get the block type, block size
            auto readBlockHeader = [](void *readBuffer, long readBufferLength, long *needOffset, FlightRecordVisionGroupDataType *blockType, uint8_t *blockSize) -> bool {
                long needOffsetValue = *needOffset;
                if (needOffsetValue + sizeof(FlightRecordVisionGroupDataType) + sizeof(uint8_t) >= readBufferLength) {
                    return false;
                }
                
                uint8_t *blockTypeSrc = (uint8_t *)readBuffer + needOffsetValue;
                memcpy(blockType, blockTypeSrc, sizeof(FlightRecordVisionGroupDataType));
                needOffsetValue += sizeof(FlightRecordVisionGroupDataType);
                
                uint8_t *blockSizeSrc = (uint8_t *)readBuffer + needOffsetValue;
                memcpy(blockSize, blockSizeSrc, sizeof(uint8_t));
                needOffsetValue += sizeof(uint8_t);
                
                *needOffset = needOffsetValue;
                
                return true;
            };
            
            auto readBlockOneByOne = [readBlockBody, readBlockHeader](void *allBlockBuffer, long allBlockLength, std::shared_ptr<FlightControllerStateImp>& output, long *needOffset) -> bool {
                FlightRecordVisionGroupDataType dataType;
                uint8_t dataSize;
                if (!readBlockHeader(allBlockBuffer, allBlockLength, needOffset, &dataType, &dataSize)) {
                    return false;
                }
                
                switch (dataType) {
                    case VisionGroupDataType_VisionDetectionRadarFront:
                    case VisionGroupDataType_VisionDetectionRadarBack:
                    case VisionGroupDataType_VisionDetectionRadarRight:
                    case VisionGroupDataType_VisionDetectionRadarLeft:
                    case VisionGroupDataType_VisionDetectionRadarDown:
                    {
                        if (dataSize < sizeof(GSXuwjcwajRoXzYA)) {
                            return false;
                        }
                        
                        GSXuwjcwajRoXzYA *internalData = nullptr;
                        bool result = true;
                        
                        do {
                            internalData = (GSXuwjcwajRoXzYA *)malloc(dataSize);
                            if (!readBlockBody(allBlockBuffer, allBlockLength, internalData, dataSize, needOffset)) {
                                result = false;
                                break;
                            }
                            
                        } while (0);
                        
                        if (internalData) {
                            free(internalData);
                        }
                        
                        if (!result) {
                            return result;
                        }
                    }
                        break;
                    case VisionGroupDataType_MCAvoidStatus:
                    {
                        if (dataSize < sizeof(TMEcHTnPNccJUFVk)) {
                            return false;
                        }
                        
                        TMEcHTnPNccJUFVk *internalData = nullptr;
                        bool result = true;
                        
                        do {
                            internalData = (TMEcHTnPNccJUFVk *)malloc(dataSize);
                            if (!readBlockBody(allBlockBuffer, allBlockLength, internalData, dataSize, needOffset)) {
                                result = false;
                                break;
                            }
                            
                            // can fill the mc avoid status data.
                            result = FillVisionGroupDataType(internalData, output);
                        } while (0);
                        
                        if (internalData) {
                            free(internalData);
                        }
                        
                        if (!result) {
                            return result;
                        }
                    }
                        break;
                    case VisionGroupDataType_GuidanceDetect:
                    {
                        if (dataSize < sizeof(JYgXYyXqHVEIrYhz)) {
                            return false;
                        }
                        
                        JYgXYyXqHVEIrYhz *internalData = nullptr;
                        bool result = true;
                        
                        do {
                            internalData = (JYgXYyXqHVEIrYhz *)malloc(dataSize);
                            if (!readBlockBody(allBlockBuffer, allBlockLength, internalData, dataSize, needOffset)) {
                                result = false;
                                break;
                            }
                            
                            // can fill guidance detect.
                        } while (0);
                        
                        if (internalData) {
                            free(internalData);
                        }
                        
                        if (!result) {
                            return result;
                        }
                    }
                        break;
                    case VisionGroupDataType_WarningStatus:
                    {
                        if (dataSize < sizeof(pjEvVPrhPuHWwlgx)) {
                            return false;
                        }
                        
                        pjEvVPrhPuHWwlgx *internalData = nullptr;
                        bool result = true;
                        
                        do {
                            internalData = (pjEvVPrhPuHWwlgx *)malloc(dataSize);
                            if (!readBlockBody(allBlockBuffer, allBlockLength, internalData, dataSize, needOffset)) {
                                result = false;
                                break;
                            }
                        } while (0);
                        
                        if (internalData) {
                            free(internalData);
                        }
                        
                        if (!result) {
                            return result;
                        }
                    }
                        break;
                        
                    default:
                        return false;
                }
                
                return true;
            };
            
            bool onceReadSuccess = false;
            long offset = 0;
            
            while (readBlockOneByOne(buffer, length, output, &offset)) {
                onceReadSuccess = true;
                if (offset >= length) {
                    break;
                }
            }
            
            return true;
        }
            
        default:
            break;
    }
    
    return false;
}
