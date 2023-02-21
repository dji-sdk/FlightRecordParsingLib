//
//  fr_standardization_vision_filter.hpp
//  FlightRecordStandardization
//
//

#ifndef fr_standardization_vision_filter_hpp
#define fr_standardization_vision_filter_hpp

#include <stdio.h>
#include "fr_standardization_vision_model.hpp"
#include <FlightRecordProtocolEnum.h>

namespace DJIFR {
    namespace standardization {
        
        //MARK: - Public
        
        /// filler the vistion state.
        /// @param output  the vistion state.
        /// @param data_type  the data type.
        /// @param buffer  the original buffer.
        /// @param length  the length of the original buffer.
        /// @return YES, fill the rc hardware state success.
        bool Filler(std::shared_ptr<VisionStateImp>& output,
                    FlightRecordDataType data_type,
                    uint8_t *buffer,
                    uint64_t length);
    
    }
}

#endif /* fr_standardization_vision_filter_hpp */
