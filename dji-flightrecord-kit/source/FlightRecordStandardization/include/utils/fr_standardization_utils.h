//
//  fr_standardization_utils.h
//  FlightRecordStandardization
//
//  Copyright © 2020 DJISDK. All rights reserved.
//

#ifndef fr_standardization_utils_h
#define fr_standardization_utils_h

#include "fr_standardization_flight_controller_interface.h"

namespace DJIFR {
    namespace standardization {
        /**
         * Returns the distance between two points on the Earth.
         * @param lat1 Latitude of the first point in degrees.
         * @param lon1 Longitude of the first point in degrees.
         * @param lat2 Latitude of the second point in degrees.
         * @param lon2 Longitude of the second point in degrees.
         * @return The distance between the two points in meters
         */
        double CoordinateDistance(double lat1, double lon1, double lat2, double lon2);
    
        /// Returns a Boolean value indicating whether the specified coordinate is valid.
        /// @param lat Latitude of the point in degrees.
        /// @param lon Longitude of the point in degrees.
        /// @param isGPSBeingUsed Whether the GPS is being used
        /// @param gpsLevel Aircraft's current GPS signal quality.
        /// @return true if the coordinate is valid or false if it is not.
        bool CoordinateIsValid(double lat, double lon, bool isGPSBeingUsed, GPSSignalLevel gpsLevel);
    }
}

#endif /* fr_standardization_utils_h */
