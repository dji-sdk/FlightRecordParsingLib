//
//  fr_standardization_rc_hardware_filler.hpp
//  FlightRecordStandardization
//
//  Copyright © 2019 DJISDK. All rights reserved.
//

#ifndef fr_standardization_rc_hardware_filler_hpp
#define fr_standardization_rc_hardware_filler_hpp

#include <stdio.h>
#include "fr_standardization_frametime_model.hpp"
#include <FlightRecordProtocolEnum.h>
#include <model/protocol/dji_product_type.h>

namespace DJIFR {
    namespace standardization {
        //MARK: - Public
    
        /// filler the rc hardware state.
        /// @param rc_hardware_state  the rc hardware state
        /// @param product_type the product type.
        /// @param data_type  the data type.
        /// @param buffer  the original buffer.
        /// @param length  the length of the original buffer.
        /// @return YES, fill the rc hardware state success.
        bool Filler(std::shared_ptr<RCHardwareStateImp>& rc_hardware_state,
                    DJI::FlightRecord::ProductType product_type,
                    FlightRecordDataType data_type,
                    uint8_t *buffer,
                    uint64_t length);
    }
}

#endif /* fr_standardization_rc_hardware_filler_hpp */
