//
//  flight_record_feature_point_enum.h
//  FlightRecordEngine
//
//  Copyright © 2020 DJISDK. All rights reserved.
//

#ifndef flight_record_feature_point_enum_h
#define flight_record_feature_point_enum_h

#include <stdio.h>
#include <stdint.h>

namespace DJI {
    namespace FlightRecord {
        /// Function Points match RSA keys one by one.
        enum class FeaturePoint : uint16_t {
            /// Basic functions, general part
            /// It is currently version 13.1 in use.
            BaseFeature = 1,
            /// visual information
            /// It is currently version 13.1 in use.
            VisionFeature,
            /// Information related to Waypoint 1.0
            /// It is currently version 13.1 in use.
            WaypointFeature,
            /// Information on agricultural business
            /// It is currently version 13.1 in use.
            AgricultureFeature,
            /// Information on AirLink
            /// It is currently version 13.1 in use.
            AirLinkFeature,
            /// Post-Sales Engagement Key
            /// It is currently version 13.1 in use.
            AfterSalesFeature,
            /// DJI Fly
            /// It is currently version 13.1 in use.
            DJIFlyCustomFeature,
            /// Plaintext
            /// It is currently version 13.1 in use.
            PlaintextFeature,
            /// Flight Hub
            /// It is currently version 13.1 in use.
            FlightHubFeature,
        };
    }
}

#endif /* flight_record_feature_point_enum_h */
