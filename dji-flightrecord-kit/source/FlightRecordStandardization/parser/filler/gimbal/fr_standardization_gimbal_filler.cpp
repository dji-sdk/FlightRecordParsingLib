//
//  fr_standardization_gimbal_filler.cpp
//  FlightRecordStandardization
//
//  Copyright © 2019 DJISDK. All rights reserved.
//

#include "fr_standardization_gimbal_filler.hpp"
#include <model/protocol/fr_protocol.h>
#include "ZucGZjOtwWrgqCCe.h"
#include <string.h>

using namespace DJIFR::standardization;
using namespace DJI::FlightRecord;

//MARK: - GimbalFlightRecordDataType

static bool FillGimbalAtti(const dji_gimbal_attitude_response &data_source,
                           std::shared_ptr<GimbalStateImp>& output) {
    auto attitude = std::make_shared<AttitudeImp>(data_source.pitch * 0.1f,
                                                  data_source.roll * 0.1f,
                                                  data_source.yaw * 0.1f);
    output->set_attitude(attitude);
    
    output->set_fineTunedRoll(data_source.roll_adjust_rad / 10.0);
    output->set_fineTunedYaw(data_source.yaw_trim_val / 10.0);
    output->set_fineTunedPitch(data_source.pitch_adjust_degree / 10.0);
    
    output->set_isRollAtStop(data_source.row_limited);
    output->set_isYawAtStop(data_source.yaw_limited);
    output->set_isPitchAtStop(data_source.pitch_limited);
    
    output->set_yawRelativeToAircraftHeading(data_source.yaw_angle_opposite_drone * 0.1f);
    
    output->set_mode((GimbalMode)data_source.work_mode);
    
    return true;
}

//MARK: - Public

bool DJIFR::standardization::Filler(std::shared_ptr<GimbalStateImp>& output,
                                    FlightRecordDataType data_type,
                                    uint8_t *buffer,
                                    uint64_t length) {
    switch (data_type) {
        case GimbalFlightRecordDataType:
        {
            dji_gimbal_attitude_response data_source = {0};
            uint64_t data_source_len = std::min(length, (uint64_t)sizeof(data_source));
            
            if (data_source_len <= 0) {
                return false;
            }
            
            memcpy(&data_source, buffer, data_source_len);
            
            return FillGimbalAtti(data_source, output);
        }
            break;
            
        default:
            break;
    }
    
    return true;
}
