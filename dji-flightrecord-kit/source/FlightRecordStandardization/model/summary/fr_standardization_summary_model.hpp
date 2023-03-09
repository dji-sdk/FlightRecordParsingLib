//
//  fr_standardization_summary_model.hpp
//  FlightRecordStandardization
//
//  Copyright © 2019 DJISDK. All rights reserved.
//

#ifndef fr_standardization_summary_model_hpp
#define fr_standardization_summary_model_hpp

#include <stdio.h>
#include "fr_standardization_common.hpp"
#include <memory>
#include <string>
#include <map>
#include <vector>
#include "fr_standardization_summary_interface.h"

namespace DJIFR {
    namespace standardization {
        
        //MARK: - ComponentInformationImp
    
        class ComponentInformationImp : public ComponentInformation {
        public:
            ComponentInformationImp();
            virtual ~ComponentInformationImp();
            
            int32_t index() const override;
            void set_index(int32_t index);
            
            std::vector<int32_t> firmwareVersion() const override;
            void set_firmwareVersion(std::vector<int32_t> firmwareVersion);
            
            std::string serialNumber() const override;
            void set_serialNumber(const std::string& serialNumber);
            
        private:
            int32_t index_ = 0;
            
            std::vector<int32_t> firmwareVersion_;
            
            std::string serialNumber_;
        };

        //MARK: - SummaryInformationImp
    
        class SummaryInformationImp : public SummaryInformation {
        public:
            SummaryInformationImp();
            virtual ~SummaryInformationImp();
            
            Platform platform() const override;
            void set_platform(Platform platform);
            
            std::vector<int32_t> appVersion() const override;
            void set_appVersion(const std::vector<int32_t>& appVersion);
            
            std::map<int32_t, ComponentInformationSharedPtr> batteriesInformation() const override;
            std::map<int32_t, std::shared_ptr<ComponentInformationImp>>* batteriesInformationImp();
            
            std::map<int32_t, ComponentInformationSharedPtr> camerasInformation() const override;
            std::map<int32_t, std::shared_ptr<ComponentInformationImp>>* camerasInformationImp();
            
            std::map<int32_t, ComponentInformationSharedPtr> gimbalsInformation() const override;
            std::map<int32_t, std::shared_ptr<ComponentInformationImp>>* gimbalsInformationImp();
            
            ComponentInformationSharedPtr remoteControllerInformation() const override;
            std::shared_ptr<ComponentInformationImp> remoteControllerInformationImp();
            void set_remoteControllerInformation(const std::shared_ptr<ComponentInformationImp>& remoteControllerInformation);
            
            ComponentInformationSharedPtr flightControllerInformation() const override;
            std::shared_ptr<ComponentInformationImp> flightControllerInformationImp();
            void set_flightControllerInformation(const std::shared_ptr<ComponentInformationImp>& flightControllerInformation);
            
            std::string aircraftName() const override;
            void set_aircraftName(const std::string& aircraftName);
            
            /// The time starts to fly. Unit: Second.
            double startTime() const override;
            void set_startTime(double startTime);
            
            /// The coordinate to start fly
            LocationCoordinate2DSharedPtr startCoordinate() const override;
            void set_startCoordinate(const LocationCoordinate2DSharedPtr& startCoordinate);
            
            /// The distance of the start and the end. Unit: Meter
            float totalDistance() const override;
            void set_totalDistance(float totalDistance);
            
            /// Time interval from the start of flight to the end of flight. Unit: Second.
            double totalTime() const override;
            void set_totalTime(double totalTime);
            
            /// FrameTimeState sampling rate. The default is a sampling rate of 10HZ,
            /// that is, FrameTimeState shows the aircraft state in 0.1 seconds
            int samplingRate() const override;
            void set_samplingRate(int samplingRate);
            
            /// Highest flight distance in meters. Relative altitude of the aircraft relative to take off location.
            float maxHeight() const override;
            void set_maxHeight(float maxHeight);
            
            /// Maximum horizontal speed, in meters per second.
            float maxHorizontalSpeed() const override;
            void set_maxHorizontalSpeed(float maxHorizontalSpeed);
            
            /// Maximum vertical speed, in meters per second.
            float maxVirticalSpeed() const override;
            void set_maxVirticalSpeed(float maxVirticalSpeed);
            
            /// Only one sortie marked
            std::string uuid() const override;
            void set_uuid(const std::string& uuid);
            
            /// Only one sortie marked
            DJI::FlightRecord::ProductType product_type() const override;
            void set_product_type(DJI::FlightRecord::ProductType product_type);
            
        private:
            Platform platform_ = Platform::Unknown;
            
            std::vector<int32_t> appVersion_;
            
            std::map<int32_t, std::shared_ptr<ComponentInformationImp>> batteriesInformation_;
            
            std::map<int32_t, std::shared_ptr<ComponentInformationImp>> camerasInformation_;
            
            std::map<int32_t, std::shared_ptr<ComponentInformationImp>> gimbalsInformation_;
            
            std::shared_ptr<ComponentInformationImp> remoteControllerInformation_ = nullptr;
            
            std::shared_ptr<ComponentInformationImp> flightControllerInformation_ = nullptr;
            
            std::string aircraftName_;
            
            double startTime_ = 0;
            
            LocationCoordinate2DSharedPtr startCoordinate_ = nullptr;
            
            float totalDistance_ = 0;
            
            double totalTime_ = 0;
            
            int samplingRate_ = 0;
            
            /// Highest flight distance in meters. Relative altitude of the aircraft relative to take off location.
            float maxHeight_;
            
            /// Maximum horizontal speed, in meters per second.
            float maxHorizontalSpeed_;
            
            /// Maximum vertical speed, in meters per second.
            float maxVirticalSpeed_;
            
            /// Only one sortie marked
            std::string uuid_;
            
            /// Product Type
            DJI::FlightRecord::ProductType product_type_ = DJI::FlightRecord::ProductType::None;
        };
    }
}

#endif /* fr_standardization_summary_model_hpp */
