//
//  flight_record_utf8.hpp
//  FlightRecordEngine
//
//  Copyright © 2019 DJISDK. All rights reserved.
//

#ifndef flight_record_utf8_hpp
#define flight_record_utf8_hpp

#include <stdio.h>

namespace DJI {
    namespace FlightRecord {
        bool isValidUTF8(const char* str, size_t strLen);
    
        /// Content validity
        /// For example, the content is all 0000, but it is not necessarily valid content
        /// @param strlen the length of str
        bool isValidContent(const char* str, size_t strlen);
    }
}

#endif /* flight_record_utf8_hpp */
