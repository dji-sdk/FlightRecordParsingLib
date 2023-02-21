//
//  fr_standardization_remote_controller_interface.h
//  FlightRecordStandardization
//
//  Copyright © 2019 DJISDK. All rights reserved.
//

#ifndef fr_standardization_remote_controller_interface_h
#define fr_standardization_remote_controller_interface_h

#include <stdio.h>
#include <memory>
#include "fr_standardization_common_interface.h"

namespace DJIFR {
    namespace standardization {
        enum class RCFlightModelSwitch {
            /// Position One. For all products except Mavic Pro, this is the left most position
            /// of the flight mode switch on a remote controller from the perspective of the
            /// pilot. For example, on a Phantom 4 remote controller,  Position One is labeled
            /// "A". For Mavic Pro, Spark and Mavic Air, this is  the position that is furthest
            /// away from the pilot and labeled "Sport".
            One = 0,
            /// Position Two. For all products except Mavic Pro, this is the middle position of
            /// the flight mode switch on a remote controller from the perspective of the pilot.
            /// For example, on a Phantom 4 remote controller, Position Two is labeled "S". For
            /// Mavic Pro, Spark and Mavic Air, this is the position that is closest  to the
            /// pilot [the P position].
            Two = 1,
            /// Position Three. For all products except Mavic Pro, this is the right most
            /// position of the flight mode switch on a remote controller from the perspective
            /// of the pilot. For example, on a Phantom 4 remote controller, Position Two is
            /// labeled "P". Mavic Pro, Spark or Mavic Air does not have  a third position for
            /// the flight mode switch.
            Three = 2,
            Unknown = 3,
        };
    
        enum class RCAircraftMappingStyle {
            Style1 = 0,
            Style2 = 1,
            Style3 = 2,
            StyleCustom = 3,
            Unknown = 4,
        };
    
        //MARK: - Stick
    
        class Stick {
        public:
            
            /// Get the stick's horizontal position value, the value it's in the range of [-660, 660].
            virtual int32_t horizontalPosition() const = 0;
            
            /// Get the stick's vertical position value, the value it's in the range of [-660, 660].
            virtual int32_t verticalPosition() const = 0;
        };
    
        using StickSharedPtr = std::shared_ptr<Stick>;
    
        //MARK: - RCRightWheel
    
        class RCRightWheel {
        public:
            
            /// `YES` if right wheel present.
            virtual bool isPresent() const = 0;
            
            /// `YES` if wheel value has changed.
            virtual bool isTurned() const = 0;
            
            /// `YES` if wheel is being pressed.
            virtual bool isClicked() const = 0;
            
            /// Wheel value in the range of [-660, 660]. The value represents the difference in an operation.
            virtual int32_t value() const = 0;
        };
    
        using RCRightWheelSharedPtr = std::shared_ptr<RCRightWheel>;
    
        //MARK: - RCButton
    
        class RCButton {
        public:
            
            /// `YES` if the hardware button is present.
            virtual bool isPresent() const = 0;
            
            /// `YES` if button is pressed down.
            virtual bool isClicked() const = 0;
        };
    
        using RCButtonSharedPtr = std::shared_ptr<RCButton>;
    
        //MARK: - RCGPSData
        
        class RCGPSTime {
        public:
            /// Hour value of Remote Controller's GPS time.
            virtual uint8_t hour() const = 0;
            
            /// Minute value of Remote Controller's GPS time.
            virtual uint8_t minute() const = 0;
            
            /// Second value of Remote Controller's GPS time.
            virtual uint8_t second() const = 0;
            
            /// Year value of Remote Controller's GPS time.
            virtual uint16_t year() const = 0;
            
            /// Month value of Remote Controller's GPS time.
            virtual uint8_t month() const = 0;
            
            /// Day value of Remote Controller's GPS time.
            virtual uint8_t day() const = 0;
        };
    
        using RCGPSTimeSharedPtr = std::shared_ptr<RCGPSTime>;
    
        class RCGPSData {
        public:
            /// The Remote Controller's GPS time.
            virtual RCGPSTimeSharedPtr time() const = 0;
            
            /// The Remote Controller's location.
            virtual LocationCoordinate2DSharedPtr location() const = 0;
            
            /// The Remote Controller's speed in the East direction in meters/second. A negative
            /// speed means the Remote  Controller is moving in the West direction.
            virtual float eastSpeed() const = 0;
            
            /// The Remote Controller's speed in the North direction in meters/second. A
            /// negative speed means the Remote  Controller is moving in the South direction.
            virtual float northSpeed() const = 0;
            
            /// The number of GPS satellites the Remote Controller detects.
            virtual int satelliteCount() const = 0;
            
            /// The the margin of error, in meters, for the GPS location. Unit: meter.
            virtual float accuracy() const = 0;
            
            /// `YES` if the GPS data is valid. The data is not valid if there are too few
            /// satellites  or the signal strength is too low.
            virtual bool isValid() const = 0;
        };
    
        using RCGPSDataSharedPtr = std::shared_ptr<RCGPSData>;
    
        //MARK: - RCHardwareState
    
        class RCHardwareState {
        public:
            
            /// Get left stick.
            virtual StickSharedPtr leftStick() const = 0;
            
            /// Get right stick.
            virtual StickSharedPtr rightStick() const = 0;
            
            /// Gimbal Dial's [upper left wheel] value in the range of [-660,660],
            /// where 0 is untouched and positive is turned in the clockwise direction.
            virtual int32_t leftWheel() const = 0;
            
            /// Current state of the upper right wheel on the Remote Controller [Camera Settings Dial].
            virtual RCRightWheelSharedPtr rightWheel() const = 0;
            
            ///  Current position of the Flight Mode Switch on the Remote Controller.
            virtual RCFlightModelSwitch flightModeSwitch() const = 0;
            
            /// Current state of the Return To Home Button.
            virtual RCButtonSharedPtr goHomeButton() const = 0;
            
            /// Current state of the Video Recording Button.
            virtual RCButtonSharedPtr recordButton() const = 0;
            
            /// Current state of the Shutter Button.
            virtual RCButtonSharedPtr shutterButton() const = 0;
            
            /// Current state of the Playback Button.
            virtual RCButtonSharedPtr playbackButton() const = 0;
            
            /// Current state of the Pause Button.
            virtual RCButtonSharedPtr pauseButton() const = 0;
            
            /// The Remote Controller's control mode.
            virtual RCAircraftMappingStyle style() const = 0;
            
            /// The Remote Controller's GPS data.
            virtual RCGPSDataSharedPtr GPSData() const = 0;
        };
    
        using RCHardwareStateSharedPtr = std::shared_ptr<RCHardwareState>;
    }
}

#endif /* fr_standardization_remote_controller_interface_h */
