//
//  fr_standardization_utils_private.h
//  FlightRecordStandardization
//
//  Copyright © 2020 DJISDK. All rights reserved.
//

#ifndef fr_standardization_utils_private_h
#define fr_standardization_utils_private_h

#include <stdio.h>
#include <memory>
#include <string>
#include "fr_standardization_summary_interface.h"
#include <FlightRecordProtocolEnum.h>

namespace DJIFR {
    namespace standardization {
    
        /// Check if the binary is a valid UTF-8, if not, return an empty string
        /// @param data data pointer
        /// @param max_data_len Maximum length of the data pointer
        std::string ConvertRawDataToUTF8(const char* data, size_t max_data_len);
    
        /// Convert the uint8_t array to a version string
        /// @param data uint8_t array
        /// @param count uint8_t array lengthuint8_t array length
        std::string ConvertUint8ToVersionStr(uint8_t *data, int count);
    
        Platform ConvertInternalPlatformToPublic(DJI::FlightRecord::Platform platform);
    }
}

#endif /* fr_standardization_utils_private_h */
