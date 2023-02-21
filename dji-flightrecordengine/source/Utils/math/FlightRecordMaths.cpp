//
//  FlightRecordMaths.cpp
//  FlightRecordEngine
//
//  Copyright © 2017 DJI. All rights reserved.
//

#include <stdio.h>
#include <Utils/math/FlightRecordMaths.h>
#define _USE_MATH_DEFINES
#include <cmath>
#include <math.h>

using namespace std;

double DJI::FlightRecord::Deg2rad(double deg) {
    return (deg * M_PI / 180);
}

//  This function converts radians to decimal degrees
double DJI::FlightRecord::Rad2deg(double rad) {
    return (rad * 180 / M_PI);
}

double DJI::FlightRecord::DistanceEarth(double lat1r, double lon1r, double lat2r, double lon2r) {
    double d_lon = abs(lon1r - lon2r);
    // Numerator
    double a = pow(cos(lat2r) * sin(d_lon), 2);
    double b = cos(lat1r) * sin(lat2r);
    double c = sin(lat1r) * cos(lat2r) * cos(d_lon);
    double d = pow(b - c, 2);
    double e = sqrt(a + d);
    // Denominator
    double f = sin(lat1r) * sin(lat2r);
    double g = cos(lat1r) * cos(lat2r) * cos(d_lon);
    double h = f + g;
    double d_sigma = atan2(e, h);
    return kEarthRadiusKm * d_sigma * 1000;
}
