//
//  fr_standardization_common_interface.h
//  FlightRecordStandardization
//
//  Copyright © 2019 DJISDK. All rights reserved.
//

#ifndef fr_standardization_common_interface_h
#define fr_standardization_common_interface_h

#include <stdio.h>
#include <memory>

namespace DJIFR {
    namespace standardization {
    
        enum class ObstacleDirection : int {
            None = 0,
            Front = 1,
            Back = 2,
            Up = 3,
            Left = 4,
            Right = 5,
        };
    
        //MARK: - LocationCoordinate2D
        class LocationCoordinate2D {
        public:
            
            /// The latitude in degrees.
            virtual double latitude() const = 0;
            
            /// The longitude in degrees.
            virtual double longitude() const = 0;
        };
    
        using LocationCoordinate2DSharedPtr = std::shared_ptr<LocationCoordinate2D>;
    
        //MARK: - Velocity
        
        class Velocity {
        public:
            /// Current speed of the aircraft in the x direction, in meters per second,
            /// using the N-E-D (North-East-Down)  coordinate system.
            virtual float velocityX() const = 0;
            
            /// Current speed of the aircraft in the y direction, in meters per second,
            /// using the N-E-D (North-East-Down)  coordinate system.
            virtual float velocityY() const = 0;
            
            /// Current speed of the aircraft in the z direction, in meters per second,
            /// using the N-E-D (North-East-Down)  coordinate system.
            virtual float velocityZ() const = 0;
        };
    
        using VelocitySharedPtr = std::shared_ptr<Velocity>;
    
        //MARK: - Attitude
    
        class Attitude {
        public:
            
            /// Aircraft's pitch attitude value.
            virtual double pitch() const = 0;
            
            /// Aircraft's roll attitude value.
            virtual double roll() const = 0;
            
            /// Aircraft's yaw attitude value.
            virtual double yaw() const = 0;
        };
    
        using AttitudeSharedPtr = std::shared_ptr<Attitude>;
    
        //MARK: - Buffer
        
        class Buffer {
        public:
            Buffer(void *pointer, size_t length);
            Buffer(size_t length);
            virtual ~Buffer();
            
            std::shared_ptr<void> data_;
            
            size_t length_;
        };
    
        using BufferSharedPtr = std::shared_ptr<Buffer>;
    
        //MARK: - DecryptKeychain
    
        class DecryptKeychain {
        public:
            DecryptKeychain(const Buffer& private_key, const Buffer& lparam);
            virtual ~DecryptKeychain();
            
            Buffer private_key_;
            
            Buffer lparam_;
        };
    
        using DecryptKeychainSharedPtr = std::shared_ptr<DecryptKeychain>;
    }
}

#endif /* fr_standardization_common_interface_h */
