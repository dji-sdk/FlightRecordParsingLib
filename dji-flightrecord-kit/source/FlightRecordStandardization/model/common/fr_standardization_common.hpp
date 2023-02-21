//
//  fr_standardization_common.hpp
//  FlightRecordStandardization
//
//  Copyright © 2019 DJISDK. All rights reserved.
//

#ifndef fr_standardization_common_hpp
#define fr_standardization_common_hpp

#include <stdio.h>
#include <memory>
#include "fr_standardization_common_interface.h"

namespace DJIFR {
    namespace standardization {
    
        //MARK: - LocationCoordinate2DImp
        class LocationCoordinate2DImp : public LocationCoordinate2D {
        public:
            LocationCoordinate2DImp(double latitude, double longitude);
            virtual ~LocationCoordinate2DImp();
            
            /// The latitude in degrees.
            double latitude() const override;
            
            /// The longitude in degrees.
            double longitude() const override;
            
        private:
            double latitude_;
            
            double longitude_;
        };
    
        //MARK: - VelocityImp
    
        class VelocityImp : public Velocity {
        public:
            VelocityImp(float velocityX, float velocityY, float velocityZ);
            virtual ~VelocityImp();
            
            /// Current speed of the aircraft in the x direction, in meters per second,
            /// using the N-E-D (North-East-Down)  coordinate system.
            float velocityX() const override;
            
            /// Current speed of the aircraft in the y direction, in meters per second,
            /// using the N-E-D (North-East-Down)  coordinate system.
            float velocityY() const override;
            
            /// Current speed of the aircraft in the z direction, in meters per second,
            /// using the N-E-D (North-East-Down)  coordinate system.
            float velocityZ() const override;
            
        private:
            float velocityX_;
            
            float velocityY_;
            
            float velocityZ_;
        };
    
        //MARK: - AttitudeImp
    
        class AttitudeImp : public Attitude {
        public:
            AttitudeImp(double pitch, double roll, double yaw);
            virtual ~AttitudeImp();
            
            /// Aircraft's pitch attitude value.
            double pitch() const override;
            
            /// Aircraft's roll attitude value.
            double roll() const override;
            
            /// Aircraft's yaw attitude value.
            double yaw() const override;
            
        private:
            double pitch_;
            
            double roll_;
            
            double yaw_;
        };
    }
}

#endif /* fr_standardization_common_hpp */
