//
//  fr_standardization_mobile_rc_filler.cpp
//  FlightRecordStandardization
//
//  Copyright © 2019 DJISDK. All rights reserved.
//

#include "fr_standardization_mobile_rc_filler.hpp"
#include <model/protocol/fr_protocol.h>
#include "ZucGZjOtwWrgqCCe.h"
#include <Utils/encryption/FlightRecordCRC64.h>
#include <string.h>
#include <assert.h>

using namespace DJIFR::standardization;
using namespace DJI::FlightRecord;

//MARK: - AppSpecialControlJoyStickDataType

static bool FillJoyStickRecordData(const dji_special_control_joy_stick& joy_stick,
                                   std::shared_ptr<MobileRemoteControllerStateImp>& output) {
    output->set_leftStickVertical((joy_stick.channel2 - 1024) / 1024.0);
    output->set_leftStickHorizontal((joy_stick.channel3 - 1024) / 1024.0);
    output->set_rightStickVertical((joy_stick.channel1 - 1024) / 1024.0);
    output->set_rightStickHorizontal((joy_stick.channel0 - 1024) / 1024.0);
    
    return true;
}

//MARK: - Public

bool DJIFR::standardization::Filler(std::shared_ptr<MobileRemoteControllerStateImp>& output,
                                    FlightRecordDataType data_type,
                                    uint8_t *buffer,
                                    uint64_t length) {
    switch (data_type) {
        case AppSpecialControlJoyStickDataType:
        {
            if (length < sizeof(dji_special_control_joy_stick)) {
                return false;
            }
            
            if (length == sizeof(dji_special_control_joy_stick) + 1) {
                uint8_t crc8_res = crc8(buffer, sizeof(dji_special_control_joy_stick), DJI_MSG_HCRC_INITCRC);
                
                if (crc8_res != *(buffer + sizeof(dji_special_control_joy_stick))) {
                    assert(false && "crc verify can't pass");
                    return false;
                }
            }
            
            dji_special_control_joy_stick data_source = {0};
            memcpy(&data_source, buffer, sizeof(data_source));
            
            return FillJoyStickRecordData(data_source, output);
        }
            break;
            
        default:
            break;
    }
    
    return false;
}
