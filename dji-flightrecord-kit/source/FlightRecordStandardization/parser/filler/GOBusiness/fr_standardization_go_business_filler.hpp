//
//  fr_standardization_go_business_filler.hpp
//  FlightRecordStandardization
//
//  Copyright © 2020 DJISDK. All rights reserved.
//

#ifndef fr_standardization_go_business_filler_hpp
#define fr_standardization_go_business_filler_hpp

#include <stdio.h>
#include "fr_standardization_go_business_model.hpp"
#include <FlightRecordProtocolEnum.h>

namespace DJIFR {
    namespace standardization {
        //MARK: - Public
        
        /// filler the go business state.
        /// @param output  the go business state.
        /// @param data_type  the data type.
        /// @param buffer  the original buffer.
        /// @param length  the length of the original buffer.
        /// @return YES, fill the rc hardware state success.
        bool Filler(std::shared_ptr<GOBusinessDataImp>& output,
                    FlightRecordDataType data_type,
                    uint8_t *buffer,
                    uint64_t length);
    }
}

#endif /* fr_standardization_go_business_filler_hpp */
