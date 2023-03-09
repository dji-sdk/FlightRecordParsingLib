//
//  fr_standardization_rc_hardware_filler.cpp
//  FlightRecordStandardization
//
//  Copyright © 2019 DJISDK. All rights reserved.
//

#include "fr_standardization_rc_hardware_filler.hpp"
#include <model/protocol/fr_protocol.h>
#include "ZucGZjOtwWrgqCCe.h"
#include <string.h>

using namespace DJIFR::standardization;
using namespace DJI::FlightRecord;

//MARK: - RCPushGPSFlightRecordDataType

static bool FillRCGPSData(const dji_rc_gps_info_push& data_source,
                          std::shared_ptr<RCHardwareStateImp>& output) {
    auto time = std::make_shared<RCGPSTimeImp>();
    time->set_hour(data_source.time.hour);
    time->set_minute(data_source.time.minute);
    time->set_second(data_source.time.second);
    time->set_year(data_source.time.year);
    time->set_month(data_source.time.month);
    time->set_day(data_source.time.day);
    
    auto GPSData = std::make_shared<RCGPSDataImp>();
    GPSData->set_time(time);
    GPSData->set_location(std::make_shared<LocationCoordinate2DImp>(data_source.latitude, data_source.longitude));
    GPSData->set_eastSpeed(data_source.v_x);
    GPSData->set_northSpeed(data_source.v_y);
    GPSData->set_satelliteCount(data_source.gps_num);
    GPSData->set_accuracy(data_source.accuracy);
    GPSData->set_isValid(data_source.valid_data);
    
    output->set_GPSData(GPSData);
    
    return true;
}

//MARK: - RCFlightRecordDataType

static bool FillerRCFlightRecordData(const dji_rc_channel_params_push& data_source,
                                     std::shared_ptr<RCHardwareStateImp>& output,
                                     ProductType product_type) {
    auto left_stick = std::make_shared<StickImp>();
    left_stick->set_horizontalPosition(data_source.ch_r - 1024);
    left_stick->set_verticalPosition(data_source.ch_t - 1024);
    output->set_leftStick(left_stick);
    
    auto right_stick = std::make_shared<StickImp>();
    right_stick->set_horizontalPosition(data_source.ch_a - 1024);
    right_stick->set_verticalPosition(data_source.ch_e - 1024);
    output->set_rightStick(right_stick);
    
    output->set_leftWheel(data_source.GYRO - 1024);
    
    auto right_wheel = std::make_shared<RCRightWheelImp>();
    right_wheel->set_isPresent(product_type != ProductType::jwtAbyahuARrhuhr && product_type != ProductType::Spark);
    right_wheel->set_isClicked(data_source.wheel_btn_down);
    right_wheel->set_isTurned(data_source.wheel_change);
    bool isSupportNewRightWheel = (product_type == ProductType::Matrice300RTK);
    bool isMavic2SerialRC = (product_type == ProductType::Mavic2 || product_type == ProductType::Mavic2Enterprise);
    if (isSupportNewRightWheel || isMavic2SerialRC) {
        right_wheel->set_value(data_source.right_wheel_channel - 1024);
    } else {
        int sign = data_source.wheel_polarity ? 1 : -1;
        right_wheel->set_value(sign * data_source.wheel_offset);
    }
    output->set_rightWheel(right_wheel);
    
    // flight mode switch
    RCFlightModelSwitch mode_switch = (RCFlightModelSwitch)data_source.mode_switch;
    if (product_type == ProductType::MavicPro) {
        switch (mode_switch) {
            case RCFlightModelSwitch::One:
                mode_switch = RCFlightModelSwitch::Two;
                break;
            case RCFlightModelSwitch::Two:
                mode_switch = RCFlightModelSwitch::Three;
                break;
            case RCFlightModelSwitch::Three:
                mode_switch = RCFlightModelSwitch::One;
                break;
                
            default:
                break;
        }
    }
    output->set_flightModeSwitch(mode_switch);
    
    std::shared_ptr<RCButtonImp> go_home_btn = nullptr;
    std::shared_ptr<RCButtonImp> record_btn = nullptr;
    std::shared_ptr<RCButtonImp> shutter_btn = nullptr;
    std::shared_ptr<RCButtonImp> playback_btn = nullptr;
    std::shared_ptr<RCButtonImp> pause_btn = nullptr;
    if (product_type != ProductType::jwtAbyahuARrhuhr) {
        go_home_btn = std::make_shared<RCButtonImp>();
        go_home_btn->set_isPresent(true);
        go_home_btn->set_isClicked(data_source.return_btn);
        
        record_btn = std::make_shared<RCButtonImp>();
        record_btn->set_isPresent(true);
        record_btn->set_isClicked(data_source.focus_btn_down);
        
        shutter_btn = std::make_shared<RCButtonImp>();
        shutter_btn->set_isPresent(!(product_type == ProductType::Spark || product_type == ProductType::MavicAir));
        shutter_btn->set_isClicked(data_source.shutter_btn_down);
        
        switch (product_type) {
            // play back
            case ProductType::Phantom3Standard:
            case ProductType::jwtAbyahuARrhuhr:
            case ProductType::kshQeTGrEeTmtpoe:
            case ProductType::Phantom3SE:
            case ProductType::ZUYdiVOVXfGCLDcI:
            case ProductType::CdogAypKribEXKfS:
            case ProductType::Phantom34K:
            {
                playback_btn = std::make_shared<RCButtonImp>();
                playback_btn->set_isPresent(true);
                playback_btn->set_isClicked(data_source.playback_btn_down);
            }
                break;
            // pause button
            case ProductType::Phantom4Pro:
            case ProductType::Phantom4Advanced:
            case ProductType::Phantom4ProV2:
            case ProductType::Phantom4:
            case ProductType::qvMmdCGxrtrJWvxx:
            case ProductType::Inspire2:
            case ProductType::Phantom4RTK:
            {
                pause_btn = std::make_shared<RCButtonImp>();
                pause_btn->set_isPresent(true);
                pause_btn->set_isClicked(data_source.playback_btn_down);
            }
                break;
                
            default:
                break;
        }
        
        output->set_goHomeButton(go_home_btn);
        output->set_recordButton(record_btn);
        output->set_shutterButton(shutter_btn);
        output->set_playbackButton(playback_btn);
        output->set_pauseButton(pause_btn);
    }
    
    return true;
}

//MARK: - Public

bool DJIFR::standardization::Filler(std::shared_ptr<RCHardwareStateImp>& rc_hardware_state,
                                    ProductType product_type,
                                    FlightRecordDataType data_type,
                                    uint8_t *buffer,
                                    uint64_t length) {
    switch (data_type) {
        case RCFlightRecordDataType:
        {
            dji_rc_channel_params_push data_source = {0};
            uint64_t data_source_len = std::min(length, (uint64_t)sizeof(data_source));
            
            if (data_source_len <= 0) {
                return false;
            }
            
            memcpy(&data_source, buffer, data_source_len);
            
            return FillerRCFlightRecordData(data_source, rc_hardware_state, product_type);
        }
        case RCPushGPSFlightRecordDataType:
        {
            dji_rc_gps_info_push data_source = {0};
            uint64_t data_source_len = std::min(length, (uint64_t)sizeof(data_source));
            
            if (data_source_len <= 0) {
                return false;
            }
            
            memcpy(&data_source, buffer, data_source_len);
            
            return FillRCGPSData(data_source, rc_hardware_state);
        }
            break;
            
        default:
            break;
    }
    
    return false;
}
