//
//  fr_standardization_mobile_device_filler.cpp
//  FlightRecordStandardization
//
//  Copyright © 2020 DJISDK. All rights reserved.
//

#include "fr_standardization_mobile_device_filler.hpp"
#include <model/protocol/fr_protocol.h>
#include <string.h>
#include <model/protocol/fr_protocol.h>
#include "fr_standardization_common.hpp"

using namespace DJIFR::standardization;
using namespace DJI::FlightRecord;

static bool FillAppLocationDataType(const DJIFlightRecordAppLocation& data_source,
                                    std::shared_ptr<MobileDeviceStateImp>& output) {
    auto mobile_location = std::make_shared<LocationCoordinate2DImp>(data_source.latitude, data_source.longitude);
    output->set_coordinate(mobile_location);
    
    output->set_horizontalAccuracy(data_source.horizontalAccuracy);
    
    return true;
}

//MARK: - Public

bool DJIFR::standardization::Filler(std::shared_ptr<MobileDeviceStateImp>& output,
                                    FlightRecordDataType data_type,
                                    uint8_t *buffer,
                                    uint64_t length) {
    switch (data_type) {
        case AppLocationDataType:
        {
            DJIFlightRecordAppLocation data_source = {0};
            uint64_t data_length = std::min(length, (uint64_t)sizeof(data_source));
            if (data_length <= 0) {
                return false;
            }
            
            memcpy(&data_source, buffer, data_length);
            return FillAppLocationDataType(data_source, output);
        }
            break;

        default:
            break;
    }

    return false;
}
