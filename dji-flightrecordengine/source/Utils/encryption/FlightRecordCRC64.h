//
//  crc64.h
//  testEncryptFR
//

#ifndef FlightRecordCRC64_h
#define FlightRecordCRC64_h

#include <stdio.h>

namespace DJI {
    namespace FlightRecord {
        uint64_t crc64(uint64_t crc, const unsigned char *s, uint64_t l);
        uint8_t crc8(const uint8_t *pData, uint32_t Len, uint8_t initCrc);
    }
}
#endif /* FlightRecordCRC64_h */
