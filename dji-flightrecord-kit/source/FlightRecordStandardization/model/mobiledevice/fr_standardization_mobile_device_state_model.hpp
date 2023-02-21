//
//  fr_standardization_mobile_device_state_model.hpp
//  FlightRecordStandardization
//
//  Copyright © 2020 DJISDK. All rights reserved.
//

#ifndef fr_standardization_mobile_device_state_model_hpp
#define fr_standardization_mobile_device_state_model_hpp

#include <stdio.h>
#include "fr_standardization_mobile_device_interface.h"
#include "fr_standardization_common.hpp"

namespace DJIFR {
    namespace standardization {
        class MobileDeviceStateImp : public MobileDeviceState {
        public:
            MobileDeviceStateImp();
            virtual ~MobileDeviceStateImp();
            
            std::shared_ptr<MobileDeviceStateImp> clone();
            
            /// The current location of the mobile as a coordinate. `nil` if the location is invalid.
            LocationCoordinate2DSharedPtr coordinate() const override;
            void set_coordinate(const LocationCoordinate2DSharedPtr& coordinate);
            
            /// The radius of uncertainty for the location, measured in meters.
            /// Returns the horizontal accuracy of the location. Negative if the lateral location is invalid.
            double horizontalAccuracy() const override;
            void set_horizontalAccuracy(double horizontalAccuracy);
            
        private:
            LocationCoordinate2DSharedPtr coordinate_ = nullptr;
            
            double horizontalAccuracy_ = -1;
        };
    }
}

#endif /* fr_standardization_mobile_device_state_model_hpp */
