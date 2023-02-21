//
//  FlightRecordKeychainModel.h
//  FlightRecordEngine
//
//  Copyright © 2019 DJISDK. All rights reserved.
//

#ifndef FlightRecordKeychainModel_h
#define FlightRecordKeychainModel_h

#include <model/FlightRecordCommonModel.h>
#include <Utils/featurePoint/flight_record_feature_point_enum.h>

namespace DJI {
    namespace FlightRecord {
#pragma pack(1)
        typedef struct {
            FeaturePoint featurePoint;
            FlightRecordCommonData aes_key_ciphertext;
        } FlightRecordKeyChainInDetail;
#pragma pack()
    }
}

#endif /* FlightRecordKeychainModel_h */
