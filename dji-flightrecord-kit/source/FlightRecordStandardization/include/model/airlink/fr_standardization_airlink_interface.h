//
//  fr_standardization_airlink_interface.h
//  FlightRecordStandardization
//
//  Copyright © 2020 DJISDK. All rights reserved.
//

#ifndef fr_standardization_airlink_interface_h
#define fr_standardization_airlink_interface_h

#include <stdio.h>
#include <vector>
#include <memory>

namespace DJIFR {
    namespace standardization {
        //MARK: - AirLinkState
        class AirLinkState {
        public:
            /// Updated signal quality in percent for the wireless downlink （from aircraft to
            /// remote  controller）. This link transfers all information from aircraft to remote
            /// controller,  which is predominantly video information. Signal quality is a
            /// function of signal  strength, interference and data rate. Signal quality will be
            /// more susceptible to weak  signal strengths or high interference when the data
            /// rate is high.
            /// The signal quality in percent with range [0, 100], where 100 is the best quality.
            virtual int32_t downlinkSignalQuality() const = 0;
            virtual bool has_downlinkSignalQuality() const = 0;
            
            /// Updated signal quality in percent for the wireless uplink （from remote
            /// controller to  aircraft）. This link transfers all information from the remote
            /// controller to the  aircraft, which is predominantly control information.
            /// The signal quality in percent with range [0, 100], where 100 is the best quality.
            virtual int32_t uplinkSignalQuality() const = 0;
            virtual bool has_uplinkSignalQuality() const = 0;
        };
    
        using AirLinkStateSharedPtr = std::shared_ptr<AirLinkState>;
    }
}

#endif /* fr_standardization_airlink_interface_h */
