//
//  FlightRecordMaths.h
//  FlightRecordEngine
//
//  Copyright © 2017 DJI. All rights reserved.
//

#ifndef FlightRecordMaths_h
#define FlightRecordMaths_h

namespace DJI {
    namespace FlightRecord {
        const double kEarthRadiusKm = 6371.0;
        double Deg2rad(double deg);
        double Rad2deg(double rad);

        /**
         * Returns the distance between two points on the Earth.
         * @param lat1r Latitude of the first point in radian
         * @param lon1r Longitude of the first point in radian
         * @param lat2r Latitude of the second point in radian
         * @param lon2r Longitude of the second point in radian
         * @return The distance between the two points in meters
         */
        double DistanceEarth(double lat1r, double lon1r, double lat2r, double lon2r);
    }
}

#endif /* FlightRecordMaths_h */
