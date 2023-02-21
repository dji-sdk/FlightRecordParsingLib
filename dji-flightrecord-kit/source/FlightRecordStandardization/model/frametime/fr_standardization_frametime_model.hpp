//
//  fr_standardization_frametime_model.hpp
//  FlightRecordStandardization
//
//  Copyright © 2019 DJISDK. All rights reserved.
//

#ifndef fr_standardization_frametime_model_hpp
#define fr_standardization_frametime_model_hpp

#include <stdio.h>
#include "fr_standardization_rc_model.hpp"
#include "fr_standardization_mobile_rc_model.hpp"
#include "fr_standardization_gimbal_model.hpp"
#include "fr_standardization_flightcontroller_model.hpp"
#include "fr_standardization_camera_state.hpp"
#include "fr_standardization_battery_state.hpp"
#include "fr_standardization_airlink_model.hpp"
#include "fr_standardization_go_business_model.hpp"
#include "fr_server_standardization_frametime_interface.h"
#include "fr_standardization_mobile_device_state_model.hpp"
#include "fr_standardization_vision_model.hpp"

namespace DJIFR {
    namespace standardization {
        /// Frame time records what happed within 0.1 seconds.
        class FrameTimeStateImp : public ServerFrameTimeState {
        public:
            FrameTimeStateImp();
            virtual ~FrameTimeStateImp();
            
            std::shared_ptr<FrameTimeStateImp> clone();
            
            /// Returns an instance of the aircraft's remote controller hardware state.
            RCHardwareStateSharedPtr rcHardwareState() const override;
            std::shared_ptr<RCHardwareStateImp> rcHardwareStateImp();
            void set_rcHardwareState(const std::shared_ptr<RCHardwareStateImp>& rcHardwareState);
            
            /// A simulated remote controller on the mobile device.
            MobileRemoteControllerStateSharedPtr mobileRemoteController() const override;
            std::shared_ptr<MobileRemoteControllerStateImp> mobileRemoteControllerImp();
            void set_mobileRemoteController(const std::shared_ptr<MobileRemoteControllerStateImp>& mobileRemoteController);
            
            /// Returns an instance of the aircraft's gimbal state.
            GimbalStateSharedPtr gimbalState() const override;
            std::shared_ptr<GimbalStateImp> gimbalStateImp();
            void set_gimbalState(const std::shared_ptr<GimbalStateImp>& gimbalState);
            
            /// Returns an array of the aircraft's gimbal state.
            std::map<int, GimbalStateSharedPtr> gimbalsState() const override;
            std::map<int, std::shared_ptr<GimbalStateImp>> &gimbalsState();
            
            /// Returns an instance of the aircraft's flight controller state.
            FlightControllerStateSharedPtr flightControllerState() const override;
            std::shared_ptr<FlightControllerStateImp> flightControllerStateImp();
            void set_flightControllerState(const std::shared_ptr<FlightControllerStateImp>& flightControllerState);
            
            /// Returns an instance of the aircraft's camera state.
            CameraStateSharedPtr cameraState() const override;
            std::shared_ptr<CameraStateImp> cameraStateImp();
            void set_cameraState(const std::shared_ptr<CameraStateImp>& cameraState);
            
            /// Returns an array of the aircraft's camera state.
            std::map<int, CameraStateSharedPtr> camerasState() const override;
            std::map<int, std::shared_ptr<CameraStateImp>> &camerasState();
            
            /// Returns an instance of the aircraft's battery state.
            BatteryStateSharedPtr batteryState() const override;
            std::shared_ptr<BatteryStateImp> batteryStateImp();
            void set_batteryState(const std::shared_ptr<BatteryStateImp>& batteryState);
            
            /// Returns an array of the aircraft's battery state.
            std::map<int, BatteryStateSharedPtr> batteriesState() const override;
            std::map<int, std::shared_ptr<BatteryStateImp>> &batteriesState();
            
            /// Returns an instance of the aircraft's airlink state.
            AirLinkStateSharedPtr airlinkState() const override;
            std::shared_ptr<AirLinkStateImp> airlinkStateImp();
            void set_airlinkState(const std::shared_ptr<AirLinkStateImp>& airlinkState);
            
            /// Return an instance of the aircraft's go business data
            GOBusinessDataSharedPtr goBusinessData() const override;
            std::shared_ptr<GOBusinessDataImp> goBusinessDataImp();
            void set_goBusinessData(const std::shared_ptr<GOBusinessDataImp>& goBusiness);
            
            /// Returns an instance of the mobile device state.
            MobileDeviceStateSharedPtr mobileDeviceState() const override;
            std::shared_ptr<MobileDeviceStateImp> mobileDeviceStateImp();
            void set_mobileDeviceState(const std::shared_ptr<MobileDeviceStateImp>& mobileDeviceState);
            
            VisionStateSharedPtr visionState() const override;
            std::shared_ptr<VisionStateImp> visionStateImp();
            void set_visionState(const std::shared_ptr<VisionStateImp>& visionState);
            
        private:
            
            std::shared_ptr<RCHardwareStateImp> rcHardwareState_ = nullptr;
            
            std::shared_ptr<MobileRemoteControllerStateImp> mobileRemoteController_ = nullptr;
            
            std::map<int, std::shared_ptr<GimbalStateImp>> gimbalsState_;
            
            std::shared_ptr<FlightControllerStateImp> flightControllerState_ = nullptr;
            
            std::map<int, std::shared_ptr<CameraStateImp>> camerasState_;
            
            std::map<int, std::shared_ptr<BatteryStateImp>> batteriesState_;
            
            std::shared_ptr<AirLinkStateImp> airlinkState_ = nullptr;
            
            std::shared_ptr<GOBusinessDataImp> goBusiness_ = nullptr;
            
            std::shared_ptr<MobileDeviceStateImp> mobileDeviceState_ = nullptr;
            
            std::shared_ptr<VisionStateImp> visionState_ = nullptr;
        };
    }
}

#endif /* fr_standardization_frametime_model_hpp */
