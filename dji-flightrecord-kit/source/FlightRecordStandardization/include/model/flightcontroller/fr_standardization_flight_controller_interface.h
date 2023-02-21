//
//  fr_standardization_flight_controller_interface.h
//  FlightRecordStandardization
//
//  Copyright © 2019 DJISDK. All rights reserved.
//

#ifndef fr_standardization_flight_controller_interface_h
#define fr_standardization_flight_controller_interface_h

#include <stdio.h>
#include <memory>
#include "fr_standardization_common_interface.h"

namespace DJIFR {
    namespace standardization {
    
        enum class FlightWindWarning {
            /// No wind warning.
            Level0 = 0,
            /// The wind speed is high. Fly with caution and ensure the aircraft remains within the line of sight.
            Level1 = 1,
            /// Strong Wind. Fly with caution and ensure the aircraft remains within line of  sight. It is more serious than `DJIFlightWindWarningLevel1`.
            Level2 = 2,
            Unknown,
        };
    
        enum class ConnectionFailSafeBehavior {
            Hover = 0,
            Landing = 1,
            GoHome = 2,
            Unknown,
        };
    
        enum class SmartRTHState {
            /// Smart RTH is not triggered yet in the current flight. The Smart RTH state will be reset to this value when the aircraft lands.
            Idle = 0,
            /// Smart RTH is triggered and the aircraft is counting down. If no response is received within 10 seconds or the user confirms the request, the aircraft will start to go home and the state will change to `DJIFlightControllerSmartRTHStateExecuted`. If user cancels the request, the state will change to `DJIFlightControllerSmartRTHStateCancelled`.
            CountingDown = 1,
            /// Smart RTH is already executed in the current flight. The state will not be reset until the aircraft lands.
            Executed = 2,
            /// Smart RTH request is cancelled by the user. The state will not be reset until the aircraft lands.
            Cancelled = 3,
            Unknown,
        };
    
        enum class VirtualStickVerticalControlMode {
            /// Sets the virtual stick vertical control values to be a vertical velocity.
            /// Positive and negative vertical velocity is for the aircraft ascending and
            /// descending respectively. Maximum vertical velocity is defined as 4 m/s. Minimum
            /// vertical velocity is defined as -4 m/s.
            Velocity = 0,
            /// Sets the virtual stick vertical control values to be an altitude. Maximum
            /// position is defined as 500 m. Minimum position is defined as 0 m.
            Position = 1,
            Unknown,
        };
    
        enum class VirtualStickRollPitchControlMode {
            /// Sets the roll and pitch values to be an angle relative to a level aircraft. In
            /// the body coordinate system, positive and negative pitch angle is for the
            /// aircraft rotating about the y-axis in the positive direction or negative
            /// direction, respectively. Positive and negative roll angle is the positive
            /// direction or negative direction rotation angle about the x-axis, respectively.
            /// However in the ground coordinate system, positive and negative pitch angle is
            /// the angle value for the aircraft moving south and north, respectively. Positive
            /// and negative roll angle is the angle when the aircraft is moving east and west,
            /// respectively. Maximum angle is defined as 30 degrees. Minimum angle is defined
            /// as -30 degrees.
            Angle = 0,
            /// Sets the roll and pitch values to be a velocity. In the body coordinate system,
            /// positive and negative pitch velocity is for the aircraft moving towards the
            /// positive direction or negative direction along the pitch axis and y-axis,
            /// respectively. Positive and negative roll velocity is when the aircraft is moving
            /// towards the positive direction or negative direction along the roll axis and
            /// x-axis, respectively. However, in the ground coordinate system, positive and
            /// negative pitch velocity is for the aircraft moving east and west, respectively.
            /// Positive and negative roll velocity is when the aircraft is moving north and
            /// south, respectively. Maximum velocity is defined as 15 meters/s. Minimum
            /// velocity is defined as -15 meters/s.
            Velocity = 1,
            Unknown,
        };
    
        enum class VirtualStickYawControlMode {
            /// Sets the yaw values to be an angle relative to the north. Positive and negative
            /// yaw angle is for the aircraft rotating clockwise and counterclockwise,
            /// respectively. Maximum yaw angle is defined as 180 degrees. Minimum yaw angle is
            /// defined as -180 degrees.
            Angle = 0,
            /// Sets the yaw values to be an angular velocity. Positive and negative angular
            /// velocity is for the aircraft rotating clockwise and counterclockwise,
            /// respectively. Maximum yaw angular velocity is defined as 100 degrees/s. Minimum
            /// yaw angular velocity is defined as -100 degrees/s.
            Velocity = 1,
            Unknown,
        };
    
        enum class VirtualStickFlightCoordinateSystem {
            /// Ground coordinate system.
            Ground = 0,
            /// Body coordinate system.
            Body = 1,
            Unknown,
        };
    
        enum class GPSSignalLevel {
            /// The GPS has almost no signal, which is very bad.
            Level0 = 0,
            /// The GPS signal is very weak.
            Level1 = 1,
            /// The GPS signal is weak. At this level, the aircraft's go home functionality will still work.
            Level2 = 2,
            /// The GPS signal is good. At this level, the aircraft can hover in the air.
            Level3 = 3,
            /// The GPS signal is very good. At this level, the aircraft can record the home point.
            Level4 = 4,
            /// The GPS signal is very strong.
            Level5 = 5,
            Unknwon = 0xFF,
        };
    
        enum class FlightMode {
            /// Manual mode.
            Manual = 0,

            /// Attitude mode.
            Atti = 1,

            /// Attitude course lock mode.
            AttiCourseLock = 2,
           
            /// GPS Attitude mode.
            GPSAtti = 6,

            /// GPS course lock mode.
            GPSCourseLock = 7,

            /// GPS Home mode.
            GPSHomeLock = 8,

            /// GPS hotpoint mode.
            GPSHotPoint = 9,

            /// Assisted takeoff mode.
            AssistedTakeoff = 10,

            /// Auto takeoff mode.
            AutoTakeoff = 11,

            /// Auto landing mode.
            AutoLanding = 12,

            /// GPS waypoint mode.
            GPSWaypoint = 14,

            /// Go home mode.
            GoHome = 15,
        
            /// Joystick mode.
            Joystick = 17,
        
            /// Attitude limited mode.
            GPSAttiWristband = 18,
        
            /// Draw mode.
            Draw = 24,
        
            /// GPS follow me mode.
            GPSFollowMe = 25,
        
            /// ActiveTrack mode.
            ActiveTrack = 26,
        
            /// TapFly mode.
            TapFly = 27,
        
            /// Sport mode.
            GPSSport = 31,
        
            /// GPS Novice mode.
            GPSNovice = 32,
        
            /// Confirm landing mode.
            ConfirmLanding = 33,
        
            /// The aircraft should move following the terrain.
            TerrainFollow = 35,
        
            /// Tripod mode.
            Tripod = 38,
        
            /// Active track mode, corresponds to Spotlight active track mode.
            ActiveTrackSpotlight = 39,
        
            /// The motors are just started.
            MotorsJustStarted = 41,
        
            /// The main controller flight mode is unknown.
            Unknown = 0xFF,
        };
    
        //MARK: - VirtualStickFlightControlData
    
        class VirtualStickFlightControlData {
        public:
            
            /// Gets aircraft's velocity [m/s] along the y-axis or angle value [in degrees] for
            /// pitch. Use `DJIVirtualStickRollPitchControlMode` to set the velocity or angle
            /// mode. Note that the argument has different meanings in different coordinate
            /// systems. See the <i>Flight Controller User Guide</i> for more information.
            virtual float pitch() const = 0;
            
            /// Gets aircraft's velocity [m/s] along the x-axis or angle value [in degrees] for
            /// roll. Use `DJIVirtualStickRollPitchControlMode` to set the velocity or angle
            /// mode. Note that the argument has different meanings in different coordinate
            /// systems. See the <i>Flight Controller User Guide</i> for more information.
            virtual float roll() const = 0;
            
            /// Angular velocity [degrees/s] or angle [degrees] value for yaw. Use
            /// `DJIVirtualStickYawControlMode` to set angular velocity or angle mode.
            virtual float yaw() const = 0;
            
            /// Gets aircraft's velocity [m/s] or altitude [m] value for verticalControl. Use
            /// `DJIVirtualStickYawControlMode` to set velocity or altitude mode.
            virtual float verticalThrottle() const = 0;
            
            /// The vertical control mode for virtual stick. CAUTION: It will be reset to
            /// `DJIVirtualStickVerticalControlModeVelocity` when the flight controller is
            /// reconnected.
            virtual VirtualStickVerticalControlMode verticalControlMode() const = 0;
            
            /// The roll and pitch control mode for virtual stick. CAUTION: It will be reset to
            /// `DJIVirtualStickRollPitchControlModeAngle` when the flight controller is
            /// reconnected.
            virtual VirtualStickRollPitchControlMode rollPitchControlMode() const = 0;
            
            /// The yaw control mode for virtual stick. CAUTION: It will be reset to
            /// `DJIVirtualStickYawControlModeAngle` when the flight controller is reconnected.
            virtual VirtualStickYawControlMode yawControlMode() const = 0;
            
            /// The coordinate system for virtual stick. CAUTION: It will be reset to
            /// `DJIVirtualStickFlightCoordinateSystemGround` when the flight controller is
            /// reconnected.
            virtual VirtualStickFlightCoordinateSystem rollPitchCoordinateSystem() const = 0;
        };
    
        using VirtualStickFlightControlDataSharedPtr = std::shared_ptr<VirtualStickFlightControlData>;
    
        //MARK: - FlightControllerState
    
        class FlightControllerState {
        public:
            
            /// The attitude of the aircraft, where the pitch, roll, and yaw values will be in
            /// the range of [-180, 180] degrees. If its pitch, roll, and yaw values are 0, the
            /// aircraft will  be hovering level with a True North heading.
            virtual AttitudeSharedPtr attitude() const = 0;
            
            /// Current speed of the aircraft
            virtual VelocitySharedPtr velocity() const = 0;
            
            /// Home location of the aircraft as a coordinate.
            virtual LocationCoordinate2DSharedPtr homeLocationCoordinate() const = 0;
            
            /// Relative altitude of the aircraft home location relative to sea level, in meters.
            virtual float takeoffLocationAltitude() const = 0;
            
            /// The current location of the aircraft as a coordinate. `nil` if the location is invalid.
            virtual LocationCoordinate2DSharedPtr aircraftLocation() const = 0;
            
            /// Relative altitude of the aircraft relative to take off location, measured by
            /// the barometer, in meters.
            virtual float altitude() const = 0;
            
            /// Flight controller flight mode.
            virtual FlightMode flightMode() const = 0;
            
            /// Whether the GPS is being used
            virtual bool isGPSBeingUsed() const = 0;
            
            /// Aircraft's current GPS signal quality.
            virtual GPSSignalLevel gpsLevel() const = 0;
            
            /// GPS satellite count.
            virtual int32_t satelliteCount() const = 0;
            
            /// The estimated remaining time, in seconds, it will take the aircraft to go home
            /// with a 10% battery buffer remaining. This time includes landing the aircraft. If
            /// the aircraft is using the simulator, this value will be 0.
            virtual int32_t remainingFlightTime() const = 0;
            
            /// The battery percentage, in the range of [0,100], needed for the aircraft to move
            /// downward from its current position and land.
            virtual int32_t batteryPercentageNeededToLandFromCurrentHeight() const = 0;
            
            /// The estimated battery percentage, in the range of [0,100], needed for the
            /// aircraft to go home and have 10% battery remaining. This includes landing of the aircraft.
            virtual int32_t batteryPercentageNeededToGoHome() const = 0;
            
            /// The Smart Return-To-Home (RTH) state for the current flight.
            virtual SmartRTHState smartRTHState() const = 0;
            
            /// Sets the FailSafe action for when the connection between remote controller and aircraft is lost.
            virtual ConnectionFailSafeBehavior behavior() const = 0;
            
            /// The virtual stick commands
            virtual VirtualStickFlightControlDataSharedPtr virtualControlData() const = 0;
            
            ///  `YES` if the signal is lost between remote controller and aircraft, and FailSafe is enabled.
            virtual bool isFailsafeEnabled() const = 0;
            
            /// `YES` if motors are on.
            virtual bool areMotorsOn() const = 0;
            
            /// `YES` if the home point has been set.
            virtual bool isHomeLocationSet() const = 0;
            
            /// `YES` if the clearance between the aircraft and the ground is less than 0.3m,
            /// and  confirmation from the user is needed to continue the landing. When the
            /// confirmation is needed, `confirmLandingWithCompletion` in `DJIFlightController`
            /// can be used to continue landing. It is
            /// supported by flight controller firmware 3.2.0.0 or above.
            virtual bool isLandingConfirmationNeeded() const = 0;
            
            /// `YES` if the aircraft has reached its flight height limit.
            virtual bool hasReachedMaxFlightHeight() const = 0;
            
            /// `YES` if the aircraft has reached its flight radius limit.
            virtual bool hasReachedMaxFlightRadius() const = 0;
            
            /// Warning related to high winds.
            virtual FlightWindWarning windWarning() const = 0;
            
            /// The count of flights within the battery life cycle. Cleared when power-on.
            virtual int32_t countOfFlights() const = 0;
            
            /// The current index of the flight log on the aircraft. It is useful to find the
            /// corresponding flight log.
            virtual int32_t flightLogIndex() const = 0;
            
            /// `YES` if aircraft is flying.
            virtual bool isFlying() const = 0;
            
            /// The accumulated flight time, in seconds, since the aircraft's motors were turned on.
            virtual double flightTimeInSeconds() const = 0;
            
            /// Cumulative flight distance of the aircraft in meters
            virtual double cumulativeFlightDistance() const = 0;
            
            /// The countdown [in seconds] for the Smart Return-To-Home [RTH]. Once the
            /// countdown reaches 0, the aircraft will  execute an automatic go-home procedure.
            /// It is only valid when  `smartRTHState`  is
            /// `DJIFlightControllerSmartRTHStateCountingDown`.
            virtual int32_t smartRTHCountdown() const = 0;
        };
    
        using FlightControllerStateSharedPtr = std::shared_ptr<FlightControllerState>;
    }
}

#endif /* fr_standardization_flight_controller_interface_h */
