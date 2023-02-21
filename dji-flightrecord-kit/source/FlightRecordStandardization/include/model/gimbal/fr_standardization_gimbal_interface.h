//
//  fr_standardization_gimbal_interface.h
//  FlightRecordStandardization
//
//  Copyright © 2019 DJISDK. All rights reserved.
//

#ifndef fr_standardization_gimbal_interface_h
#define fr_standardization_gimbal_interface_h

#include <stdio.h>
#include <memory>
#include "fr_standardization_common_interface.h"

namespace DJIFR {
    namespace standardization {
        enum class GimbalMode {
            /// The gimbal can move independently of the aircraft's yaw. In this mode, even if
            /// the aircraft yaw changes, the camera will continue pointing in the same world
            /// direction. This mode is only available for the Ronin-MX when the M600 or M600
            /// Pro landing gear is retracted.
            Free = 0,
            /// The gimbal's work mode is FPV mode. In this mode, the gimbal yaw will follow the
            /// aircraft's heading, and the gimbal roll will follow the RC's roll channel value.
            /// The pitch will be available to move.
            /// This mode is only available for the Ronin-MX when the M600 landing gear is retracted.
            FPV = 1,
            /// The gimbal's work mode is such that it will follow the yaw. In this mode, the
            /// gimbal yaw will be fixed, while pitch and roll will be available to move.
            YawFollow = 2,
        };
    
        //MARK: - GimbalState
    
        class GimbalState {
        public:
        
            /// Returns the component index. Index is zero based.
            virtual int index() const = 0;
            
            /// The current gimbal attitude in degrees. Roll, pitch and yaw are 0 if the gimbal
            /// is level with the aircraft and points in the forward direction of North Pole.
            virtual AttitudeSharedPtr attitude() const = 0;
            
            /// Returns the gimbal's roll fine-tuned value. The range for the fine-tuned value
            /// is [-10, 10] degrees. If the fine-tune value is negative, the gimbal will be fine.
            /// - tuned to the specified number of degrees in the counterclockwise direction.
            virtual float fineTunedRoll() const = 0;
            
            /// Returns the gimbal's pitch fine-tuned value. The range for the fine-tuned value
            /// is [-10, 10] degrees. If the fine-tune value is negative, the gimbal will be fine.
            /// - tuned to the specified number of degrees in the downward direction.
            virtual float fineTunedPitch() const = 0;
            
            /// Returns the gimbal's yaw fine-tuned value. The range for the fine-tuned value is
            /// [-10, 10] degrees. If the fine-tune value is negative, the gimbal will be fine.
            /// - tuned to the specified number of degrees in the port (left) direction.
            virtual float fineTunedYaw() const = 0;
            
            /// `YES` if the gimbal's roll value is at its limit.
            virtual bool isRollAtStop() const = 0;
            
            /// `YES` if the gimbal's yaw value is at its limit.
            virtual bool isYawAtStop() const = 0;
            
            /// `YES` if the gimbal's pitch value is at its limit.
            virtual bool isPitchAtStop() const = 0;
            
            /// This function will return the angle between gimbal and the drone heading.
            virtual double yawRelativeToAircraftHeading() const = 0;
            
            /// Returns the gimbal's current work mode.
            virtual GimbalMode mode() const = 0;
        };
    
        using GimbalStateSharedPtr = std::shared_ptr<GimbalState>;
    }
}

#endif /* fr_standardization_gimbal_interface_h */
