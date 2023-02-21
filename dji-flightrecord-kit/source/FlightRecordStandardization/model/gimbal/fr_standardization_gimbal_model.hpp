//
//  fr_standardization_gimbal_model.hpp
//  FlightRecordStandardization
//
//  Copyright © 2019 DJISDK. All rights reserved.
//

#ifndef fr_standardization_gimbal_model_hpp
#define fr_standardization_gimbal_model_hpp

#include <stdio.h>
#include "fr_standardization_common.hpp"
#include "fr_standardization_gimbal_interface.h"

namespace DJIFR {
    namespace standardization {
    
        //MARK: - GimbalStateImp
    
        class GimbalStateImp : public GimbalState {
        public:
            GimbalStateImp();
            virtual ~GimbalStateImp();
            
            std::shared_ptr<GimbalStateImp> clone();
            
            /// Returns the component index. Index is zero based.
            int index() const override;
            void set_index(int index);
            
            /// The current gimbal attitude in degrees. Roll, pitch and yaw are 0 if the gimbal
            /// is level with the aircraft and points in the forward direction of North Pole.
            AttitudeSharedPtr attitude() const override;
            void set_attitude(const AttitudeSharedPtr& atitude);
            
            /// Returns the gimbal's roll fine-tuned value. The range for the fine-tuned value
            /// is [-10, 10] degrees. If the fine-tune value is negative, the gimbal will be fine.
            /// - tuned to the specified number of degrees in the counterclockwise direction.
            float fineTunedRoll() const override;
            void set_fineTunedRoll(float fineTunedRoll);
            
            /// Returns the gimbal's pitch fine-tuned value. The range for the fine-tuned value
            /// is [-10, 10] degrees. If the fine-tune value is negative, the gimbal will be fine.
            /// - tuned to the specified number of degrees in the downward direction.
            float fineTunedPitch() const override;
            void set_fineTunedPitch(float fineTunedPitch);
            
            /// Returns the gimbal's yaw fine-tuned value. The range for the fine-tuned value is
            /// [-10, 10] degrees. If the fine-tune value is negative, the gimbal will be fine.
            /// - tuned to the specified number of degrees in the port (left) direction.
            float fineTunedYaw() const override;
            void set_fineTunedYaw(float fineTunedYaw);
            
            /// `YES` if the gimbal's roll value is at its limit.
            bool isRollAtStop() const override;
            void set_isRollAtStop(bool isRollAtStop);
            
            /// `YES` if the gimbal's yaw value is at its limit.
            bool isYawAtStop() const override;
            void set_isYawAtStop(bool isYawAtStop);
            
            /// `YES` if the gimbal's pitch value is at its limit.
            bool isPitchAtStop() const override;
            void set_isPitchAtStop(bool isPitchAtStop);
            
            /// This function will return the angle between gimbal and the drone heading.
            double yawRelativeToAircraftHeading() const override;
            void set_yawRelativeToAircraftHeading(double yawRelativeToAircraftHeading);
            
            /// Returns the gimbal's current work mode.
            GimbalMode mode() const override;
            void set_mode(GimbalMode mode);
            
        private:
            int index_ = 0;
            
            AttitudeSharedPtr atitude_;
            
            float fineTunedRoll_;
            
            float fineTunedPitch_;
            
            float fineTunedYaw_;
            
            bool isRollAtStop_;
            
            bool isYawAtStop_;
            
            bool isPitchAtStop_;
            
            double yawRelativeToAircraftHeading_;
            
            GimbalMode mode_;
        };
    }
}

#endif /* fr_standardization_gimbal_model_hpp */
