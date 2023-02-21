//
//  fr_standardization_utils.cpp
//  FlightRecordStandardization
//
//  Copyright © 2020 DJISDK. All rights reserved.
//

#include <stdio.h>
#include "fr_standardization_utils.h"
#include <Utils/math/FlightRecordMaths.h>
#include <math.h>
#include "fr_standardization_utils_private.h"
#include <Utils/string/flight_record_utf8.hpp>
#include <string.h>

using namespace DJI::FlightRecord;
using namespace DJIFR::standardization;

#define NoGPSLON 0.00000001
#define NoGPSLAT 0.00000001

static bool gpsDefined(double latitude, double longitude)
{
    if (fabs(longitude) < NoGPSLON || fabs(latitude) < NoGPSLAT) {
        return false;
    }
    else if (fabs(latitude) > 95
        || fabs(longitude) > 185)
    {
        return false;
    }
    else
    {
        return true;
    }
}

//MARK: - Public

double DJIFR::standardization::CoordinateDistance(double lat1, double lon1, double lat2, double lon2) {
    double lat1d = Deg2rad(lat1);
    double lon1d = Deg2rad(lon1);
    double lat2d = Deg2rad(lat2);
    double lon2d = Deg2rad(lon2);
    
    return DistanceEarth(lat1d, lon1d, lat2d, lon2d);
}

bool DJIFR::standardization::CoordinateIsValid(double lat, double lon, bool isGPSBeingUsed, GPSSignalLevel gpsLevel) {
    if (gpsLevel < GPSSignalLevel::Level3 || !isGPSBeingUsed) {
        return false;
    }
    
    return gpsDefined(lat, lon);
}

//MARK: - fr_standardization_utils_private

std::string DJIFR::standardization::ConvertRawDataToUTF8(const char* data, size_t max_data_len) {
    size_t utf8_pointer_len = std::min(strlen(data), max_data_len);
    if (isValidUTF8(data, utf8_pointer_len)) {
        return std::string(data, utf8_pointer_len);
    }
    
    return "";
}

std::string DJIFR::standardization::ConvertUint8ToVersionStr(uint8_t *data, int count) {
    if (count <= 0) {
        return "";
    }
    
    std::string version;
    for (int i = 0; i < count; i ++) {
        version += std::to_string(data[i]);
        
        if (i != count - 1) {
            version += ".";
        }
    }
    
    return version;
}

DJIFR::standardization::Platform DJIFR::standardization::ConvertInternalPlatformToPublic(DJI::FlightRecord::Platform platform) {
    switch (platform) {
        case DJI::FlightRecord::Platform::iOS:
            return DJIFR::standardization::Platform::iOS;
        case DJI::FlightRecord::Platform::Android:
            return DJIFR::standardization::Platform::Android;
        case DJI::FlightRecord::Platform::Window:
            return DJIFR::standardization::Platform::Window;
        case DJI::FlightRecord::Platform::Mac:
            return DJIFR::standardization::Platform::Mac;
            
        default:
            break;
    }
    
    return DJIFR::standardization::Platform::Unknown;
}
