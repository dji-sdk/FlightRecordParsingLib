//
//  fr_standardization_vision_model.hpp
//  FlightRecordKitCpp
//
//

#ifndef fr_standardization_vision_model_hpp
#define fr_standardization_vision_model_hpp

#include <stdio.h>
#include "fr_standardization_vision_interface.h"

namespace DJIFR {
    namespace standardization {
    
        class ObstacleDetectionSectorImp : public ObstacleDetectionSector {
        public:
            ObstacleDetectionSectorImp();
            ~ObstacleDetectionSectorImp();
            
            std::shared_ptr<ObstacleDetectionSectorImp> clone();
            
            /// The detected obstacle distance to the aircraft in meters.
            double obstacleDistanceInMeters() const override;
            void set_obstacleDistanceInMeters(double obstacleDistanceInMeters);
            
            /// The warning level based on distance.
            ObstacleDetectionSectorWarning warningLevel() const override;
            void set_warningLevel(ObstacleDetectionSectorWarning warningLevel);
            
        private:
            double obstacleDistanceInMeters_ = 0;
            
            ObstacleDetectionSectorWarning warningLevel_ = ObstacleDetectionSectorWarning::Invalid;
        };
    
        class VisionDetectionStateImp : public VisionDetectionState {
        public:
            VisionDetectionStateImp();
            ~VisionDetectionStateImp();
            
            std::shared_ptr<VisionDetectionStateImp> clone();
            
            /// The vision sensor's position on the aircraft. For Phantom 4 Pro, there are 4
            /// vision sensors on the aircraft.  The sensors on the nose and tail are dual-
            /// camera sensors. The sensors on the left and right are infrared  time-of-flight
            /// (TOF) sensors.
            VisionSensorPosition position() const override;
            void set_position(VisionSensorPosition position);
            
            /// `true` if the vision sensor is working.
            bool isSensorBeingUsed() const override;
            void set_isSensorBeingUsed(bool isSensorBeingUsed);
            
            /// Distance warning level between the obstacle and the aircraft. This is a
            /// combination of warning levels from each sector.
            VisionSystemWarning systemWarning() const override;
            void set_systemWarning(VisionSystemWarning systemWarning);
            
            /// The distance to the closest detected obstacle, in meters. It is only used when
            /// the sensor is an infrared TOF  sensor. The valid range is [0.3, 5.0]. Phantom 4
            /// Pro has two infrared sensors on its left and right. Both sensors have a
            /// 70-degree horizontal field of view (FOV) and 20-degree vertical FOV. The value
            /// is always 0.0 if the sensor is a dual-camera sensor or the sensor is not working
            /// properly.
            double obstacleDistanceInMeters() const override;
            void set_obstacleDistanceInMeters(double obstacleDistanceInMeters);
            
            /// The vision system can see in front of the aircraft with a 70 degree horizontal
            /// field of view (FOV) and 55-degree  vertical FOV for the Phantom 4. The
            /// horizontal FOV is split into four equal sectors and this array contains the
            /// distance and warning information for each sector. For Phantom 4, the horizontal
            /// FOV is separated into 4 sectors.
            std::vector<ObstacleDetectionSectorSharedPtr> detectionSectors() const override;
            std::vector<std::shared_ptr<ObstacleDetectionSectorImp>> &detectionSectors();
            
        private:
            VisionSensorPosition position_ = VisionSensorPosition::Unknown;
            
            bool isSensorBeingUsed_ = false;
            
            VisionSystemWarning systemWarning_ = VisionSystemWarning::Unknown;
            
            double obstacleDistanceInMeters_ = 0;
            
            std::vector<std::shared_ptr<ObstacleDetectionSectorImp>> detectionSectors_;
        };
    
        class VisionControlStateImp : public VisionControlState {
        public:
            VisionControlStateImp();
            ~VisionControlStateImp();
            
            std::shared_ptr<VisionControlStateImp> clone();
            
            /// `true` if the aircraft will not ascend further because of an obstacle detected within 1m above it.
            bool isAscentLimitedByObstacle() const override;
            void set_isAscentLimitedByObstacle(bool isAscentLimitedByObstacle);
            
            /// `true` if the aircraft is avoiding collision from an obstacle moving towards the aircraft.
            bool isAvoidingActiveObstacleCollision() const override;
            void set_isAvoidingActiveObstacleCollision(bool isAvoidingActiveObstacleCollision);
            
            /// `true` if the aircraft is braking automatically to avoid collision.
            bool isBraking() const override;
            void set_isBraking(bool isBraking);
            
            /// `true` if the aircraft is landing precisely.
            bool isPerformingPrecisionLanding() const override;
            void set_isPerformingPrecisionLanding(bool isPerformingPrecisionLanding);
            
        private:
            bool isAscentLimitedByObstacle_ = false;
            
            bool isAvoidingActiveObstacleCollision_ = false;
            
            bool isBraking_ = false;
            
            bool isPerformingPrecisionLanding_ = false;
        };
    
        class VisionStateImp : public VisionState {
        public:
            VisionStateImp();
            ~VisionStateImp();
            
            std::shared_ptr<VisionStateImp> clone();
            
            //MARK: - Property Set & Get
            
            /// collision avoidance. When enabled, the aircraft will stop and try to go around detected obstacles.
            bool collisionAvoidanceEnabled() const override;
            void set_collisionAvoidanceEnabled(bool collisionAvoidanceEnabled);
            
            /// This class gives the aircraft's state, which is controlled by the intelligent flight assistant.
            VisionControlStateSharedPtr controlState() const override;
            std::shared_ptr<VisionControlStateImp> controlStateImp();
            void set_controlState(const std::shared_ptr<VisionControlStateImp>& controlState);
            
            /// The vision detection state.
            std::map<VisionSensorPosition, VisionDetectionStateSharedPtr> detectionStateMap() const override;
            std::map<VisionSensorPosition, std::shared_ptr<VisionDetectionStateImp>>& detectionStateMap();
            
        private:
            bool collisionAvoidanceEnabled_ = false;
            
            std::shared_ptr<VisionControlStateImp> controlState_ = nullptr;
            
            std::map<VisionSensorPosition, std::shared_ptr<VisionDetectionStateImp>> detectionStateMap_;
        };
    }
}

#endif /* fr_standardization_vision_model_hpp */
