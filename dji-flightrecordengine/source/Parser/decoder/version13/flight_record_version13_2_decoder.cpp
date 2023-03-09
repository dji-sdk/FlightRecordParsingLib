//
//  flight_record_version13_2_decoder.cpp
//  FlightRecordEngine
//
//

#include "flight_record_version13_2_decoder.hpp"

using namespace DJI::FlightRecord;

Version13V2Decoder::Version13V2Decoder():Version13Decoder() {
    support_decode_version_category_ = VersionCategory::Version13_2;
}

Version13V2Decoder::~Version13V2Decoder() {
    
}
