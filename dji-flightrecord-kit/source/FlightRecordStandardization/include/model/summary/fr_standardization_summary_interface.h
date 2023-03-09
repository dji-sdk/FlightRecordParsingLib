//
//  fr_standardization_summary_interface.h
//  FlightRecordStandardization
//
//  Copyright © 2019 DJISDK. All rights reserved.
//

#ifndef fr_standardization_summary_interface_h
#define fr_standardization_summary_interface_h

#include <stdio.h>
#include <memory>
#include "fr_standardization_common_interface.h"
#include <map>
#include <vector>
#include <model/protocol/dji_product_type.h>

namespace DJIFR {
    namespace standardization {
        enum class Platform {
            /// Unknown
            Unknown = 0,
            iOS = 1,
            Android = 2,
            Window = 10,
            Mac = 11,
            Linux = 12,
        };
    
        //MARK: - ComponentInformation
    
        class ComponentInformation {
        public:
            
            virtual int32_t index() const = 0;
            
            virtual std::vector<int32_t> firmwareVersion() const = 0;
            
            virtual std::string serialNumber() const = 0;
        };
    
        using ComponentInformationSharedPtr = std::shared_ptr<ComponentInformation>;
    
        //MARK: - SummaryInformation
    
        class SummaryInformation {
        public:
            
            virtual Platform platform() const = 0;
            
            virtual std::vector<int32_t> appVersion() const = 0;
            
            virtual std::map<int32_t, ComponentInformationSharedPtr> batteriesInformation() const = 0;
            
            virtual std::map<int32_t, ComponentInformationSharedPtr> camerasInformation() const = 0;
            
            virtual std::map<int32_t, ComponentInformationSharedPtr> gimbalsInformation() const = 0;
            
            virtual ComponentInformationSharedPtr remoteControllerInformation() const = 0;
            
            virtual ComponentInformationSharedPtr flightControllerInformation() const = 0;
            
            virtual std::string aircraftName() const = 0;
            
            /// The time starts to fly. Unit: Second.
            virtual double startTime() const = 0;
            
            /// The coordinate to start fly
            virtual LocationCoordinate2DSharedPtr startCoordinate() const = 0;
            
            /// The distance of the start and the end. Unit: Meter
            virtual float totalDistance() const = 0;
            
            /// Time interval from the start of flight to the end of flight. Unit: Second.
            virtual double totalTime() const = 0;
            
            /// FrameTimeState sampling rate. The default is a sampling rate of 10HZ,
            /// that is, FrameTimeState shows the aircraft state in 0.1 seconds
            virtual int samplingRate() const = 0;
            
            /// Highest flight distance in meters. Relative altitude of the aircraft relative to take off location.
            virtual float maxHeight() const = 0;
            
            /// Maximum horizontal speed, in meters per second.
            virtual float maxHorizontalSpeed() const = 0;
            
            /// Maximum vertical speed, in meters per second.
            virtual float maxVirticalSpeed() const = 0;
            
            /// Only one sortie marked
            virtual std::string uuid() const = 0;
            
            /// Product Type
            virtual DJI::FlightRecord::ProductType product_type() const = 0;
        };
    
        using SummaryInformationSharedPtr = std::shared_ptr<SummaryInformation>;
    }
}

#endif /* fr_standardization_summary_interface_h */
