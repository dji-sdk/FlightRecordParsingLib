//
//  fr_standardization_airlink_filler.hpp
//  FlightRecordStandardization
//
//  Copyright © 2020 DJISDK. All rights reserved.
//

#ifndef fr_standardization_airlink_filler_hpp
#define fr_standardization_airlink_filler_hpp

#include <stdio.h>
#include "fr_standardization_airlink_model.hpp"
#include <FlightRecordProtocolEnum.h>

namespace DJIFR {
    namespace standardization {
        //MARK: - Public
        
        /// filler the airlink state.
        /// @param output  the battery state.
        /// @param data_type  the data type.
        /// @param buffer  the original buffer.
        /// @param length  the length of the original buffer.
        /// @return YES, fill the rc hardware state success.
        bool Filler(std::shared_ptr<AirLinkStateImp>& output,
                    FlightRecordDataType data_type,
                    uint8_t *buffer,
                    uint64_t length);
    }
}

#endif /* fr_standardization_airlink_filler_hpp */
