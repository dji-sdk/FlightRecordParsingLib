//
//  fr_standardization_airlink_model.hpp
//  FlightRecordStandardization
//
//  Copyright © 2020 DJISDK. All rights reserved.
//

#ifndef fr_standardization_airlink_model_hpp
#define fr_standardization_airlink_model_hpp

#include <stdio.h>
#include "fr_standardization_airlink_interface.h"
#include <model/protocol/dji_product_type.h>

namespace DJIFR {
    namespace standardization {
        //MARK: - AirLinkStateImp
        class AirLinkStateImp : public AirLinkState {
        public:
            AirLinkStateImp();
            virtual ~AirLinkStateImp();
            
            std::shared_ptr<AirLinkStateImp> clone();
            
            /// Updated signal quality in percent for the wireless downlink （from aircraft to
            /// remote  controller）. This link transfers all information from aircraft to remote
            /// controller,  which is predominantly video information. Signal quality is a
            /// function of signal  strength, interference and data rate. Signal quality will be
            /// more susceptible to weak  signal strengths or high interference when the data
            /// rate is high.
            /// The signal quality in percent with range [0, 100], where 100 is the best quality.
            int32_t downlinkSignalQuality() const override;
            void set_downlinkSignalQuality(int32_t downlinkSignalQuality);
            
            bool has_downlinkSignalQuality() const override;
            void set_has_downlinkSignalQuality(bool has_downlinkSignalQuality);
            
            /// Updated signal quality in percent for the wireless uplink （from remote
            /// controller to  aircraft）. This link transfers all information from the remote
            /// controller to the  aircraft, which is predominantly control information.
            /// The signal quality in percent with range [0, 100], where 100 is the best quality.
            int32_t uplinkSignalQuality() const override;
            void set_uplinkSignalQuality(int32_t uplinkSignalQuality);
            
            bool has_uplinkSignalQuality() const override;
            void set_has_uplinkSignalQuality(bool has_uplinkSignalQuality);
            
            //MARK: - Private Property
            
            DJI::FlightRecord::DroneType drone_type() const;
            void set_drone_type(DJI::FlightRecord::DroneType drone_type);
            
        private:
            int32_t downlinkSignalQuality_ = 0;
            
            int32_t uplinkSignalQuality_ = 0;
            
            bool has_downlinkSignalQuality_ = false;
            
            bool has_uplinkSignalQuality_ = false;
            
            DJI::FlightRecord::DroneType drone_type_ = DJI::FlightRecord::DroneType::Unknown;
        };
    }
}

#endif /* fr_standardization_airlink_model_hpp */
