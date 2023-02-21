//
//  fr_standardization_mobile_device_interface.h
//  FlightRecordStandardization
//
//  Copyright © 2020 DJISDK. All rights reserved.
//

#ifndef fr_standardization_mobile_device_interface_h
#define fr_standardization_mobile_device_interface_h

#include <stdio.h>
#include <memory>
#include "fr_standardization_common_interface.h"

namespace DJIFR {
    namespace standardization {
        class MobileDeviceState {
        public:
            /// The current location of the mobile as a coordinate. `nil` if the location is invalid.
            virtual LocationCoordinate2DSharedPtr coordinate() const = 0;
            
            /// The radius of uncertainty for the location, measured in meters.
            /// Returns the horizontal accuracy of the location. Negative if the lateral location is invalid.
            virtual double horizontalAccuracy() const = 0;
        };
    
        using MobileDeviceStateSharedPtr = std::shared_ptr<MobileDeviceState>;
    }
}

#endif /* fr_standardization_mobile_device_interface_h */
