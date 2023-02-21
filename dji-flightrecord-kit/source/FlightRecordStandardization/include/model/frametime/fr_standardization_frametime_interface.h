//
//  fr_standardization_frametime_interface.h
//  FlightRecordStandardization
//
//  Copyright © 2019 DJISDK. All rights reserved.
//

#ifndef fr_standardization_frametime_interface_h
#define fr_standardization_frametime_interface_h

#include "fr_standardization_battery_interface.h"
#include "fr_standardization_camera_interface.h"
#include "fr_standardization_flight_controller_interface.h"
#include "fr_standardization_gimbal_interface.h"
#include "fr_standardization_mobile_rc_interface.h"
#include "fr_standardization_remote_controller_interface.h"
#include "fr_standardization_airlink_interface.h"
#include "fr_standardization_mobile_device_interface.h"
#include "fr_standardization_vision_interface.h"
#include <map>

namespace DJIFR {
    namespace standardization {
        /// Frame time records what happed within 0.1 seconds.
        class FrameTimeState {
        public:
            
            /// Returns an instance of the aircraft's remote controller hardware state.
            virtual RCHardwareStateSharedPtr rcHardwareState() const = 0;
            
            /// A simulated remote controller on the mobile device.
            virtual MobileRemoteControllerStateSharedPtr mobileRemoteController() const = 0;
            
            /// Returns an instance of the aircraft's gimbal state.
            virtual GimbalStateSharedPtr gimbalState() const = 0;
            
            /// Returns an array of the aircraft's gimbal state.
            virtual std::map<int, GimbalStateSharedPtr> gimbalsState() const = 0;
            
            /// Returns an instance of the aircraft's flight controller state.
            virtual FlightControllerStateSharedPtr flightControllerState() const = 0;
            
            /// Returns an instance of the aircraft's camera state.
            virtual CameraStateSharedPtr cameraState() const = 0;
            
            /// Returns an array of the aircraft's camera state.
            virtual std::map<int, CameraStateSharedPtr> camerasState() const = 0;
            
            /// Returns an instance of the aircraft's battery state.
            virtual BatteryStateSharedPtr batteryState() const = 0;
            
            /// Returns an array of the aircraft's battery state.
            virtual std::map<int, BatteryStateSharedPtr> batteriesState() const = 0;
            
            /// Returns an instance of the aircraft's airlink state.
            virtual AirLinkStateSharedPtr airlinkState() const = 0;
            
            /// Returns an instance of the mobile device state.
            virtual MobileDeviceStateSharedPtr mobileDeviceState() const = 0;
            
            /// Returns an instance of the vision state.
            virtual VisionStateSharedPtr visionState() const = 0;
        };
    
        using FrameTimeStateSharedPtr = std::shared_ptr<FrameTimeState>;
    }
}

#endif /* fr_standardization_frametime_interface_h */
