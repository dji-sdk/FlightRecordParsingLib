//
//  FlightRecordCommonModel.h
//  FlightRecordEngine
//
//  Copyright © 2019 DJISDK. All rights reserved.
//

#ifndef FlightRecordCommonModel_h
#define FlightRecordCommonModel_h

#include <stdint.h>
#include <stdbool.h>
#include <FlightRecordProtocolEnum.h>

namespace DJI {
    namespace FlightRecord {
        enum class FlightRecordAuxiliaryDataType : uint8_t {
            Info = 0,
            VersionExtension,
        };
    
#pragma pack(1)
    
        typedef struct {
            uint16_t data_length;
            uint8_t data[0];
        } FlightRecordCommonData;
    
        typedef struct {
            FlightRecordAuxiliaryDataType type;
            FlightRecordCommonData auxiliary_data;
        } FlightRecordAuxiliaryStruct;
    
#pragma pack()
    }
}

#endif /* FlightRecordCommonModel_h */
