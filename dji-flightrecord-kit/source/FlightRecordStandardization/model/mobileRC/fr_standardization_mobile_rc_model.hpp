//
//  fr_standardization_mobile_rc_model.hpp
//  FlightRecordStandardization
//
//  Copyright © 2019 DJISDK. All rights reserved.
//

#ifndef fr_standardization_mobile_rc_model_hpp
#define fr_standardization_mobile_rc_model_hpp

#include "fr_standardization_mobile_rc_interface.h"

namespace DJIFR {
    namespace standardization {
        class MobileRemoteControllerStateImp : public MobileRemoteControllerState {
        public:
            MobileRemoteControllerStateImp();
            virtual ~MobileRemoteControllerStateImp();
            
            /// Simulates the vertical movement of the left stick, which changes the aircraft's
            /// thrust causing it to raise or  lower in elevation. The valid range is [-1, 1].
            float leftStickVertical() const override;
            void set_leftStickVertical(float leftStickVertical);
            
            /// Simulates the horizontal movement of the left stick, which changes the yaw of
            /// the aircraft causing it to rotate  horizontally. The valid range is [-1, 1].
            float leftStickHorizontal() const override;
            void set_leftStickHorizontal(float leftStickHorizontal);
            
            /// Simulates the vertical movement of the right stick, which changes the the
            /// aircraft's pitch causing it to fly  forward or backward. The valid range is [-1, 1].
            float rightStickVertical() const override;
            void set_rightStickVertical(float rightStickVertical);
            
            /// Simulates the horizontal movement of the right stick, which changes the the
            /// aircraft's roll causing it to fly  left or right. The valid range is  [-1, 1].
            float rightStickHorizontal() const override;
            void set_rightStickHorizontal(float rightStickHorizontal);
            
        private:
            float leftStickVertical_;
            
            float leftStickHorizontal_;
            
            float rightStickVertical_;
            
            float rightStickHorizontal_;
        };
    }
}

#endif /* fr_standardization_mobile_rc_model_hpp */
