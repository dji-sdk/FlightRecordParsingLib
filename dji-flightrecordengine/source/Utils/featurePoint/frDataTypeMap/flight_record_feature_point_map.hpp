//
//  flight_record_feature_point_map.hpp
//  FlightRecordEngine
//
//  Copyright © 2020 DJISDK. All rights reserved.
//

#ifndef flight_record_feature_point_map_hpp
#define flight_record_feature_point_map_hpp

#include <stdio.h>
#include <Utils/featurePoint/flight_record_feature_point_enum.h>
#include <map>
#include <FlightRecordProtocolEnum.h>

namespace DJI {
    namespace FlightRecord {
    
        /// This is the Map relation corresponding to Version 13.1, the new version, which needs to rebuild the Map relation
        std::map<FlightRecordDataType, FeaturePoint> Version13_1FeaturePointMap();
    
        /// This is the Map relationship corresponding to Version 13.2, new version, need to re-construct the Map relationship.
        std::map<FlightRecordDataType, FeaturePoint> Version13_2FeaturePointMap();
    }
}

#endif /* flight_record_feature_point_map_hpp */
