//
//  FlightRecordInfoModel.h
//  FlightRecordEngine
//
//  Copyright © 2019 DJISDK. All rights reserved.
//

#ifndef FlightRecordInfoModel_h
#define FlightRecordInfoModel_h

#include <model/FlightRecordCommonModel.h>

namespace DJI {
    namespace FlightRecord {
        enum class FlightRecordInfoVersion : uint8_t {
            // Version 1, using DJIFlightRecordDetailDataEndStruct
            Version1 = 0,
        };
    
        #pragma pack(1)
    
        typedef struct {
            FlightRecordInfoVersion version;
            FlightRecordCommonData info_data;
            FlightRecordCommonData info_signature_data;
        } FlightRecordInfoPlaintext;
    
        #pragma pack()
    }
}

#endif /* FlightRecordInfoModel_h */
