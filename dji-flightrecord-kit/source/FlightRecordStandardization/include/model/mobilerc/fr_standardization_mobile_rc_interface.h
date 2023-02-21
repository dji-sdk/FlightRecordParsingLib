//
//  fr_standardization_mobile_rc_interface.h
//  FlightRecordStandardization
//
//  Copyright © 2019 DJISDK. All rights reserved.
//

#ifndef fr_standardization_mobile_rc_interface_h
#define fr_standardization_mobile_rc_interface_h

#include <stdio.h>
#include <memory>

namespace DJIFR {
    namespace standardization {
        class MobileRemoteControllerState {
        public:
            
            /// Simulates the vertical movement of the left stick, which changes the aircraft's
            /// thrust causing it to raise or  lower in elevation. The valid range is [-1, 1].
            virtual float leftStickVertical() const = 0;
            
            /// Simulates the horizontal movement of the left stick, which changes the yaw of
            /// the aircraft causing it to rotate  horizontally. The valid range is [-1, 1].
            virtual float leftStickHorizontal() const = 0;
            
            /// Simulates the vertical movement of the right stick, which changes the the
            /// aircraft's pitch causing it to fly  forward or backward. The valid range is [-1, 1].
            virtual float rightStickVertical() const = 0;
            
            /// Simulates the horizontal movement of the right stick, which changes the the
            /// aircraft's roll causing it to fly  left or right. The valid range is  [-1, 1].
            virtual float rightStickHorizontal() const = 0;
        };
    
        using MobileRemoteControllerStateSharedPtr = std::shared_ptr<MobileRemoteControllerState>;
    }
}

#endif /* fr_standardization_mobile_rc_interface_h */
