//
//  fr_standardization_battery_filler.hpp
//  FlightRecordStandardization
//
//  Copyright © 2019 DJISDK. All rights reserved.
//

#ifndef fr_standardization_battery_filler_hpp
#define fr_standardization_battery_filler_hpp

#include <stdio.h>
#include "fr_standardization_frametime_model.hpp"
#include <FlightRecordProtocolEnum.h>

namespace DJIFR {
    namespace standardization {
        //MARK: - Public
    
        /// filler the battery state.
        /// @param output  the battery state.
        /// @param data_type  the data type.
        /// @param buffer  the original buffer.
        /// @param length  the length of the original buffer.
        /// @return YES, fill the rc hardware state success.
        bool Filler(std::map<int, std::shared_ptr<BatteryStateImp>>& output,
                    FlightRecordDataType data_type,
                    uint8_t *buffer,
                    uint64_t length);
    }
}

#endif /* fr_standardization_battery_filler_hpp */
