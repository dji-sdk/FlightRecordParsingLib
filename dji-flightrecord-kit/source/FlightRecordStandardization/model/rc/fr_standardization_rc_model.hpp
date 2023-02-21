//
//  fr_standardization_rc_model.hpp
//  FlightRecordStandardization
//
//  Copyright © 2019 DJISDK. All rights reserved.
//

#ifndef fr_standardization_rc_model_hpp
#define fr_standardization_rc_model_hpp

#include "fr_standardization_remote_controller_interface.h"
#include "fr_standardization_common.hpp"

namespace DJIFR {
    namespace standardization {
    
        //MARK: - StickImp
    
        class StickImp : public Stick {
        public:
            StickImp();
            virtual ~StickImp();
            
            /// Get the stick's horizontal position value, the value it's in the range of [-660, 660].
            int32_t horizontalPosition() const override;
            void set_horizontalPosition(int32_t horizontalPosition);
            
            /// Get the stick's vertical position value, the value it's in the range of [-660, 660].
            int32_t verticalPosition() const override;
            void set_verticalPosition(int32_t verticalPosition);
            
        private:
            int32_t horizontalPosition_;
            
            int32_t verticalPosition_;
        };
    
        //MARK: - RCRightWheelImp
    
        class RCRightWheelImp : public RCRightWheel {
        public:
            RCRightWheelImp();
            virtual ~RCRightWheelImp();
            
            /// `YES` if right wheel present.
            bool isPresent() const override;
            void set_isPresent(bool isPresent);
            
            /// `YES` if wheel value has changed.
            bool isTurned() const override;
            void set_isTurned(bool isTurned);
            
            /// `YES` if wheel is being pressed.
            bool isClicked() const override;
            void set_isClicked(bool isClicked);
            
            /// Wheel value in the range of [-660, 660]. The value represents the difference in an operation.
            int32_t value() const override;
            void set_value(int32_t value);
            
        private:
            bool isPresent_;
            
            bool isTurned_;
            
            bool isClicked_;
            
            int32_t value_;
        };
    
        //MARK: - RCButtonImp
    
        class RCButtonImp : public RCButton {
        public:
            RCButtonImp();
            virtual ~RCButtonImp();
            
            /// `YES` if the hardware button is present.
            bool isPresent() const override;
            void set_isPresent(bool isPresent);
            
            /// `YES` if button is pressed down.
            bool isClicked() const override;
            void set_isClicked(bool isClicked);
            
        private:
            bool isPresent_;
            
            bool isClicked_;
        };
    
        //MARK: - RCGPSData
        class RCGPSTimeImp : public RCGPSTime {
        public:
            RCGPSTimeImp();
            ~RCGPSTimeImp();
            
            /// Hour value of Remote Controller's GPS time.
            uint8_t hour() const override;
            void set_hour(uint8_t hour);
            
            /// Minute value of Remote Controller's GPS time.
            uint8_t minute() const override;
            void set_minute(uint8_t minute);
            
            /// Second value of Remote Controller's GPS time.
            uint8_t second() const override;
            void set_second(uint8_t second);
            
            /// Year value of Remote Controller's GPS time.
            uint16_t year() const override;
            void set_year(uint16_t year);
            
            /// Month value of Remote Controller's GPS time.
            uint8_t month() const override;
            void set_month(uint8_t month);
            
            /// Day value of Remote Controller's GPS time.
            uint8_t day() const override;
            void set_day(uint8_t day);
            
        private:
            uint8_t hour_ = 0;
            
            uint8_t minute_ = 0;
            
            uint8_t second_ = 0;
            
            uint16_t year_ = 0;
            
            uint8_t month_ = 0;
            
            uint8_t day_ = 0;
        };
    
        class RCGPSDataImp : public RCGPSData {
        public:
            RCGPSDataImp();
            ~RCGPSDataImp();
            
            /// The Remote Controller's GPS time.
            RCGPSTimeSharedPtr time() const override;
            void set_time(const std::shared_ptr<RCGPSTimeImp>& time);
            
            /// The Remote Controller's location.
            LocationCoordinate2DSharedPtr location() const override;
            void set_location(const std::shared_ptr<LocationCoordinate2DImp>& location);
            
            /// The Remote Controller's speed in the East direction in meters/second. A negative
            /// speed means the Remote  Controller is moving in the West direction.
            float eastSpeed() const override;
            void set_eastSpeed(float speed);
            
            /// The Remote Controller's speed in the North direction in meters/second. A
            /// negative speed means the Remote  Controller is moving in the South direction.
            float northSpeed() const override;
            void set_northSpeed(float northSpeed);
            
            /// The number of GPS satellites the Remote Controller detects.
            int satelliteCount() const override;
            void set_satelliteCount(int satelliteCount);
            
            /// The the margin of error, in meters, for the GPS location. Unit: meter.
            float accuracy() const override;
            void set_accuracy(float accuracy);
            
            /// `YES` if the GPS data is valid. The data is not valid if there are too few
            /// satellites  or the signal strength is too low.
            bool isValid() const override;
            void set_isValid(bool isValid);
            
        private:
            std::shared_ptr<RCGPSTimeImp> time_ = nullptr;
            
            std::shared_ptr<LocationCoordinate2DImp> location_ = nullptr;
            
            float eastSpeed_ = 0;
            
            float northSpeed_ = 0;
            
            int satelliteCount_ = 0;
            
            float accuracy_ = 0;
            
            bool isValid_ = false;
        };
    
        //MARK: - RCHardwareStateImp
    
        class RCHardwareStateImp : public RCHardwareState {
        public:
            RCHardwareStateImp();
            virtual ~RCHardwareStateImp();
            
            std::shared_ptr<RCHardwareStateImp> clone();
            
            /// Get left stick.
            StickSharedPtr leftStick() const override;
            void set_leftStick(const StickSharedPtr& leftStick);
            
            /// Get right stick.
            StickSharedPtr rightStick() const override;
            void set_rightStick(const StickSharedPtr& rightStick);
            
            /// Gimbal Dial's [upper left wheel] value in the range of [-660,660],
            /// where 0 is untouched and positive is turned in the clockwise direction.
            int32_t leftWheel() const override;
            void set_leftWheel(int32_t leftWheel);
            
            /// Current state of the upper right wheel on the Remote Controller [Camera Settings Dial].
            RCRightWheelSharedPtr rightWheel() const override;
            void set_rightWheel(const RCRightWheelSharedPtr& rightWheel);
            
            ///  Current position of the Flight Mode Switch on the Remote Controller.
            RCFlightModelSwitch flightModeSwitch() const override;
            void set_flightModeSwitch(RCFlightModelSwitch flightModeSwitch);
            
            /// Current state of the Return To Home Button.
            RCButtonSharedPtr goHomeButton() const override;
            void set_goHomeButton(const RCButtonSharedPtr& goHomeButton);
            
            /// Current state of the Video Recording Button.
            RCButtonSharedPtr recordButton() const override;
            void set_recordButton(const RCButtonSharedPtr& recordButton);
            
            /// Current state of the Shutter Button.
            RCButtonSharedPtr shutterButton() const override;
            void set_shutterButton(const RCButtonSharedPtr& shutterButton);
            
            /// Current state of the Playback Button.
            RCButtonSharedPtr playbackButton() const override;
            void set_playbackButton(const RCButtonSharedPtr& playbackButton);
            
            /// Current state of the Pause Button.
            RCButtonSharedPtr pauseButton() const override;
            void set_pauseButton(const RCButtonSharedPtr& pauseButton);
            
            /// The Remote Controller's control mode.
            RCAircraftMappingStyle style() const override;
            void set_style(RCAircraftMappingStyle style);
            
            RCGPSDataSharedPtr GPSData() const override;
            void set_GPSData(const RCGPSDataSharedPtr& GPSData);
            
        private:
            StickSharedPtr leftStick_;
            
            StickSharedPtr rightStick_;
            
            int32_t leftWheel_;
            
            RCRightWheelSharedPtr rightWheel_;
            
            RCFlightModelSwitch flightModeSwitch_;
            
            RCButtonSharedPtr goHomeButton_;
            
            RCButtonSharedPtr recordButton_;
            
            RCButtonSharedPtr shutterButton_;
            
            RCButtonSharedPtr playbackButton_;
            
            RCButtonSharedPtr pauseButton_;
            
            RCAircraftMappingStyle style_;
            
            RCGPSDataSharedPtr GPSData_;
        };
    }
}

#endif /* fr_standardization_rc_model_hpp */
