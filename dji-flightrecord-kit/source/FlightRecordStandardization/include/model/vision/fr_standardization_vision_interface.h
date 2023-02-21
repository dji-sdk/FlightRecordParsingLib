//
//  fr_standardization_vision_interface.h
//  FlightRecordConversionServiceExecutable
//
//

#ifndef fr_standardization_vision_interface_h
#define fr_standardization_vision_interface_h

#include <stdio.h>
#include <vector>
#include <memory>
#include <string>
#include <map>

namespace DJIFR {
    namespace standardization {
    
        /// Distance warning returned by each sector of the front vision system. Warning
        /// Level 6 is the most serious level. For different aircraft, the same warning
        /// level will refer to different distances. Spark only supports the follow warning
        /// levels:
        ///    - `Invalid`
        ///    - `Level1`
        ///    - `Level2`
        ///    - `Level3`
        ///    - `Unknown`
        enum class ObstacleDetectionSectorWarning : int {
            /// The warning level is invalid. The sector cannot determine depth of the scene in front of it.
            Invalid = 0,
            /// Safe distance.
            Safe = 1,
            /// Warning disance.
            Warning = 2,
            /// Danger
            Danger = 3,
        };
    
        /// Position of the sensor on the aircraft.
        enum class VisionSensorPosition {
            /// The sensor is on the front or nose of the aircraft.
            Nose = 0,
            /// The sensor is on the back or tail of the aircraft.
            Tail = 1,
            /// The sensor is on the right or starboard side of the aircraft.
            Right = 2,
            /// The sensor is on the left or port side of the aircraft.
            Left = 3,
            /// Unknown.
            Unknown = 4,
        };
    
        enum class VisionSystemWarning {
            /// The warning is invalid. The front vision system cannot determine depth of the scene in front of it.
            Invalid = 0,
            /// The distance between the obstacle detected by the vision system and the aircraft is safe (over 2 meters).
            Safe = 1,
            /// The distance between the obstacle detected by the vision system and the aircraft
            /// is dangerous (less than 2 meters).
            Dangerous = 2,
            /// The distance warning is unknown. This warning is returned when an exception occurs.
            Unknown = 0xFF,
        };
    
        class ObstacleDetectionSector {
        public:
            /// The detected obstacle distance to the aircraft in meters.
            virtual double obstacleDistanceInMeters() const = 0;
            
            /// The warning level based on distance.
            virtual ObstacleDetectionSectorWarning warningLevel() const = 0;
        };
    
        using ObstacleDetectionSectorSharedPtr = std::shared_ptr<ObstacleDetectionSector>;
    
        /// This class gives state information about the product's vision sensors used for
        /// obstacle detection. The two types of sensors used are dual camera sensors
        /// operating in the visible spectrum (dual-camera sensor) and infrared time of
        /// flight (TOF) sensors. Note, Inspire 2's upwards-facing infrared TOF sensor is
        /// not returned in this state. It is accessed through `DJIVisionControlState`.
        class VisionDetectionState {
        public:
            /// The vision sensor's position on the aircraft. For Phantom 4 Pro, there are 4
            /// vision sensors on the aircraft.  The sensors on the nose and tail are dual-
            /// camera sensors. The sensors on the left and right are infrared  time-of-flight
            /// (TOF) sensors.
            virtual VisionSensorPosition position() const = 0;
            
            /// `true` if the vision sensor is working.
            virtual bool isSensorBeingUsed() const = 0;
            
            /// Distance warning level between the obstacle and the aircraft. This is a
            /// combination of warning levels from each sector.
            virtual VisionSystemWarning systemWarning() const = 0;
            
            /// The distance to the closest detected obstacle, in meters. It is only used when
            /// the sensor is an infrared TOF  sensor. The valid range is [0.3, 5.0]. Phantom 4
            /// Pro has two infrared sensors on its left and right. Both sensors have a
            /// 70-degree horizontal field of view (FOV) and 20-degree vertical FOV. The value
            /// is always 0.0 if the sensor is a dual-camera sensor or the sensor is not working
            /// properly.
            virtual double obstacleDistanceInMeters() const = 0;
            
            /// The vision system can see in front of the aircraft with a 70 degree horizontal
            /// field of view (FOV) and 55-degree  vertical FOV for the Phantom 4. The
            /// horizontal FOV is split into four equal sectors and this array contains the
            /// distance and warning information for each sector. For Phantom 4, the horizontal
            /// FOV is separated into 4 sectors.
            virtual std::vector<ObstacleDetectionSectorSharedPtr> detectionSectors() const = 0;
        };
    
        using VisionDetectionStateSharedPtr = std::shared_ptr<VisionDetectionState>;
    
        /// This class gives the aircraft's state, which is controlled by the intelligent flight assistant.
        class VisionControlState {
        public:
            /// `true` if the aircraft will not ascend further because of an obstacle detected within 1m above it.
            virtual bool isAscentLimitedByObstacle() const = 0;
            
            /// `true` if the aircraft is avoiding collision from an obstacle moving towards the aircraft.
            virtual bool isAvoidingActiveObstacleCollision() const = 0;
            
            /// `true` if the aircraft is braking automatically to avoid collision.
            virtual bool isBraking() const = 0;
            
            /// `true` if the aircraft is landing precisely.
            virtual bool isPerformingPrecisionLanding() const = 0;
        };
    
        using VisionControlStateSharedPtr = std::shared_ptr<VisionControlState>;
    
        class VisionState {
        public:
            //MARK: - Property Set & Get
            
            /// collision avoidance. When enabled, the aircraft will stop and try to go around detected obstacles.
            virtual bool collisionAvoidanceEnabled() const = 0;
            
            /// This class gives the aircraft's state, which is controlled by the intelligent flight assistant.
            virtual VisionControlStateSharedPtr controlState() const = 0;
            
            /// The vision detection state.
            virtual std::map<VisionSensorPosition, VisionDetectionStateSharedPtr> detectionStateMap() const = 0;
        };
    
        using VisionStateSharedPtr = std::shared_ptr<VisionState>;
    }
}

#endif /* fr_standardization_vision_interface_h */
