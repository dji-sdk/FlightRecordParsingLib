//
//  fr_server_standardization_frametime_interface.h
//  FlightRecordStandardization
//
//  Copyright © 2020 DJISDK. All rights reserved.
//

#ifndef fr_server_standardization_frametime_interface_h
#define fr_server_standardization_frametime_interface_h

#include "fr_standardization_frametime_interface.h"
#include "fr_standardization_go_business_interface.h"

namespace DJIFR {
    namespace standardization {
        class ServerFrameTimeState : public FrameTimeState {
        public:
            
            /// Return an instance of the aircraft's go business data
            virtual GOBusinessDataSharedPtr goBusinessData() const = 0;
        };
    
        using ServerFrameTimeStateSharedPtr = std::shared_ptr<ServerFrameTimeState>;
    }
}

#endif /* fr_server_standardization_frametime_interface_h */
