//
//  flight_record_version13_2_decoder.hpp
//  FlightRecordEngine
//
//

#ifndef flight_record_version13_2_decoder_hpp
#define flight_record_version13_2_decoder_hpp

#include <stdio.h>
#include <Parser/decoder/version13/flight_record_version13_decoder.hpp>

namespace DJI {
    namespace FlightRecord {
        /// Decoded version 13.2 flight logs
        class Version13V2Decoder : public Version13Decoder {
        public:
            Version13V2Decoder();
            ~Version13V2Decoder();
        };
    }
}

#endif /* flight_record_version13_2_decoder_hpp */
