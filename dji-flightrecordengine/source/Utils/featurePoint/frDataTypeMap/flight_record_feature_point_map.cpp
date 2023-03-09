//
//  flight_record_feature_point_map.cpp
//  FlightRecordEngine
//
//  Copyright © 2020 DJISDK. All rights reserved.
//

#include "flight_record_feature_point_map.hpp"
#include <vector>

using namespace DJI::FlightRecord;

#ifndef WIN32
    __attribute__((visibility("hidden")))
#endif
std::map<FlightRecordDataType, FeaturePoint> DJI::FlightRecord::Version13_2FeaturePointMap() {
    std::map<FlightRecordDataType, FeaturePoint> map;
    
    auto base_feature_arr = std::vector<FlightRecordDataType>();
    base_feature_arr.push_back(OSDFlightRecordDataType);
    base_feature_arr.push_back(OSDHomeFlightRecordDataType);
    base_feature_arr.push_back(MCTripodStateFlightRecordDataType);
    base_feature_arr.push_back(RecoverInfoDataType);
    base_feature_arr.push_back(AppLocationDataType);
    base_feature_arr.push_back(FirmwareVersionType);
    base_feature_arr.push_back(ComponentSerialNumberDataType);
    for (auto iter = base_feature_arr.begin(); iter != base_feature_arr.end(); iter ++) {
        map[(*iter)] = FeaturePoint::BaseFeature;
    }
    
    auto gimbal_feature_arr = std::vector<FlightRecordDataType>();
    gimbal_feature_arr.push_back(GimbalFlightRecordDataType);
    for (auto iter = gimbal_feature_arr.begin(); iter != gimbal_feature_arr.end(); iter ++) {
        map[(*iter)] = FeaturePoint::GimbalFeature;
    }
    
    auto rc_feature_arr = std::vector<FlightRecordDataType>();
    rc_feature_arr.push_back(RCFlightRecordDataType);
    rc_feature_arr.push_back(RCPushGPSFlightRecordDataType);
    rc_feature_arr.push_back(AppSpecialControlJoyStickDataType);
    rc_feature_arr.push_back(AppVirtualStickDataType);
    for (auto iter = rc_feature_arr.begin(); iter != rc_feature_arr.end(); iter ++) {
        map[(*iter)] = FeaturePoint::RCFeature;
    }
    
    auto camera_feature_arr = std::vector<FlightRecordDataType>();
    camera_feature_arr.push_back(CameraInfoFlightRecordDataType);
    for (auto iter = camera_feature_arr.begin(); iter != camera_feature_arr.end(); iter ++) {
        map[(*iter)] = FeaturePoint::CameraFeature;
    }
    
    auto battery_feature_arr = std::vector<FlightRecordDataType>();
    battery_feature_arr.push_back(CenterBatteryFlightRecordDataType);
    battery_feature_arr.push_back(PushedBatteryFlightRecordDataType);
    battery_feature_arr.push_back(SmartBatteryGroupDataType);
    for (auto iter = battery_feature_arr.begin(); iter != battery_feature_arr.end(); iter ++) {
        map[(*iter)] = FeaturePoint::BatteryFeature;
    }
    
    auto vision_featuren_arr = std::vector<FlightRecordDataType>();
    vision_featuren_arr.push_back(VisionGroupDataType);
    vision_featuren_arr.push_back(VisionWaringStringDataType);
    for (auto iter = vision_featuren_arr.begin(); iter != vision_featuren_arr.end(); iter ++) {
        map[(*iter)] = FeaturePoint::VisionFeature;
    }
    
    auto waypoint_feature_arr = std::vector<FlightRecordDataType>();
    waypoint_feature_arr.push_back(NavigationModeGroupedDataType);
    waypoint_feature_arr.push_back(GSMissionStatusDataType);
    waypoint_feature_arr.push_back(GSMissionEventDataType);
    waypoint_feature_arr.push_back(WaypointUploadDataType);
    waypoint_feature_arr.push_back(WaypointMissionUploadDataType);
    waypoint_feature_arr.push_back(WaypointMissionDownloadDataType);
    waypoint_feature_arr.push_back(WaypointDownloadDataType);
    for (auto iter = waypoint_feature_arr.begin(); iter != waypoint_feature_arr.end(); iter ++) {
        map[(*iter)] = FeaturePoint::WaypointFeature;
    }
    
    auto argriculture_feature_arr = std::vector<FlightRecordDataType>();
    argriculture_feature_arr.push_back(AGOSDDataType);
    argriculture_feature_arr.push_back(AgricultureRadarPush);
    argriculture_feature_arr.push_back(AgricultureSpray);
    argriculture_feature_arr.push_back(RTKDifferenceDataType);
    argriculture_feature_arr.push_back(AgricultureFarmMissionInfo);
    argriculture_feature_arr.push_back(AgricultureFarmTaskTeamDataType);
    argriculture_feature_arr.push_back(AgricultureGroundStationPushData);
    argriculture_feature_arr.push_back(AgricultureDisplayField);
    for (auto iter = argriculture_feature_arr.begin(); iter != argriculture_feature_arr.end(); iter ++) {
        map[(*iter)] = FeaturePoint::AgricultureFeature;
    }
    
    auto airlink_feature_arr = std::vector<FlightRecordDataType>();
    airlink_feature_arr.push_back(AgricultureOFDMRadioSignalPush);
    for (auto iter = airlink_feature_arr.begin(); iter != airlink_feature_arr.end(); iter ++) {
        map[(*iter)] = FeaturePoint::AirLinkFeature;
    }
    
    auto after_sales_feature_arr = std::vector<FlightRecordDataType>();
    after_sales_feature_arr.push_back(RCDebugDataType);
    after_sales_feature_arr.push_back(OFDMDebugDataType);
    after_sales_feature_arr.push_back(MCParamDataType);
    after_sales_feature_arr.push_back(ADSBFlightDataDataType);
    after_sales_feature_arr.push_back(ADSBFlightOriginalDataType);
    for (auto iter = after_sales_feature_arr.begin(); iter != after_sales_feature_arr.end(); iter ++) {
        map[(*iter)] = FeaturePoint::AfterSalesFeature;
    }
    
    auto plaintext_feature_arr = std::vector<FlightRecordDataType>();
    plaintext_feature_arr.push_back(FlightRecordRecover);
    plaintext_feature_arr.push_back(KeyStorage);
    for (auto iter = plaintext_feature_arr.begin(); iter != plaintext_feature_arr.end(); iter ++) {
        map[(*iter)] = FeaturePoint::PlaintextFeature;
    }
    
    auto flight_hub_arr = std::vector<FlightRecordDataType>();
    flight_hub_arr.push_back(FlightHubInfoDataType);
    for (auto iter = flight_hub_arr.begin(); iter != flight_hub_arr.end(); iter ++) {
        map[(*iter)] = FeaturePoint::FlightHubFeature;
    }
    
    auto dji_fly_custom_feature_arr = std::vector<FlightRecordDataType>();
    dji_fly_custom_feature_arr.push_back(CustomFlightRecordDataType);
    dji_fly_custom_feature_arr.push_back(ShowTipsFlightRecordDataType);
    dji_fly_custom_feature_arr.push_back(ShowWarningFlightRecordDataType);
    dji_fly_custom_feature_arr.push_back(APPOperationDataType);
    dji_fly_custom_feature_arr.push_back(ShowSeriousWarningFlightRecordDataType);
    dji_fly_custom_feature_arr.push_back(AppLowFreqCustomDataType);
    dji_fly_custom_feature_arr.push_back(GOBusinessDataType);
    for (auto iter = dji_fly_custom_feature_arr.begin(); iter != dji_fly_custom_feature_arr.end(); iter ++) {
        map[(*iter)] = FeaturePoint::DJIFlyCustomFeature;
    }
    
    auto flysafe_feature_arr = std::vector<FlightRecordDataType>();
    flysafe_feature_arr.push_back(FlyForbidDBuuidDataType);
    flysafe_feature_arr.push_back(FlySafeLimitInfoDataType);
    flysafe_feature_arr.push_back(FlySafeUnlockLicenseUserActionInfoDataType);
    for (auto iter = flysafe_feature_arr.begin(); iter != flysafe_feature_arr.end(); iter ++) {
        map[(*iter)] = FeaturePoint::FlySafeFeature;
    }
    
    auto security_feature_arr = std::vector<FlightRecordDataType>();
    security_feature_arr.push_back(npzeXkozKlNHPjUQ);
    for (auto iter = security_feature_arr.begin(); iter != security_feature_arr.end(); iter ++) {
        map[(*iter)] = FeaturePoint::SecurityFeature;
    }
    
    return map;
}

#ifndef WIN32
    __attribute__((visibility("hidden")))
#endif
std::map<FlightRecordDataType, FeaturePoint> DJI::FlightRecord::Version13_1FeaturePointMap() {
    std::map<FlightRecordDataType, FeaturePoint> map;
    
    auto base_feature_arr = std::vector<FlightRecordDataType>();
    base_feature_arr.push_back(OSDFlightRecordDataType);
    base_feature_arr.push_back(OSDHomeFlightRecordDataType);
    base_feature_arr.push_back(GimbalFlightRecordDataType);
    base_feature_arr.push_back(RCFlightRecordDataType);
    base_feature_arr.push_back(MCTripodStateFlightRecordDataType);
    base_feature_arr.push_back(CenterBatteryFlightRecordDataType);
    base_feature_arr.push_back(PushedBatteryFlightRecordDataType);
    base_feature_arr.push_back(RCPushGPSFlightRecordDataType);
    base_feature_arr.push_back(RecoverInfoDataType);
    base_feature_arr.push_back(AppLocationDataType);
    base_feature_arr.push_back(FirmwareVersionType);
    base_feature_arr.push_back(CameraInfoFlightRecordDataType);
    base_feature_arr.push_back(AppSpecialControlJoyStickDataType);
    base_feature_arr.push_back(AppVirtualStickDataType);
    base_feature_arr.push_back(ComponentSerialNumberDataType);
    for (auto iter = base_feature_arr.begin(); iter != base_feature_arr.end(); iter ++) {
        map[(*iter)] = FeaturePoint::BaseFeature;
    }
    
    auto vision_featuren_arr = std::vector<FlightRecordDataType>();
    vision_featuren_arr.push_back(VisionGroupDataType);
    vision_featuren_arr.push_back(VisionWaringStringDataType);
    for (auto iter = vision_featuren_arr.begin(); iter != vision_featuren_arr.end(); iter ++) {
        map[(*iter)] = FeaturePoint::VisionFeature;
    }
    
    auto waypoint_feature_arr = std::vector<FlightRecordDataType>();
    waypoint_feature_arr.push_back(NavigationModeGroupedDataType);
    waypoint_feature_arr.push_back(GSMissionStatusDataType);
    waypoint_feature_arr.push_back(GSMissionEventDataType);
    waypoint_feature_arr.push_back(WaypointUploadDataType);
    waypoint_feature_arr.push_back(WaypointMissionUploadDataType);
    waypoint_feature_arr.push_back(WaypointMissionDownloadDataType);
    waypoint_feature_arr.push_back(WaypointDownloadDataType);
    for (auto iter = waypoint_feature_arr.begin(); iter != waypoint_feature_arr.end(); iter ++) {
        map[(*iter)] = FeaturePoint::WaypointFeature;
    }
    
    auto argriculture_feature_arr = std::vector<FlightRecordDataType>();
    argriculture_feature_arr.push_back(AGOSDDataType);
    argriculture_feature_arr.push_back(AgricultureRadarPush);
    argriculture_feature_arr.push_back(AgricultureSpray);
    argriculture_feature_arr.push_back(RTKDifferenceDataType);
    argriculture_feature_arr.push_back(AgricultureFarmMissionInfo);
    argriculture_feature_arr.push_back(AgricultureFarmTaskTeamDataType);
    argriculture_feature_arr.push_back(AgricultureGroundStationPushData);
    argriculture_feature_arr.push_back(AgricultureDisplayField);
    for (auto iter = argriculture_feature_arr.begin(); iter != argriculture_feature_arr.end(); iter ++) {
        map[(*iter)] = FeaturePoint::AgricultureFeature;
    }
    
    auto airlink_feature_arr = std::vector<FlightRecordDataType>();
    airlink_feature_arr.push_back(AgricultureOFDMRadioSignalPush);
    for (auto iter = airlink_feature_arr.begin(); iter != airlink_feature_arr.end(); iter ++) {
        map[(*iter)] = FeaturePoint::AirLinkFeature;
    }
    
    auto after_sales_feature_arr = std::vector<FlightRecordDataType>();
    after_sales_feature_arr.push_back(RCDebugDataType);
    after_sales_feature_arr.push_back(OFDMDebugDataType);
    after_sales_feature_arr.push_back(MCParamDataType);
    after_sales_feature_arr.push_back(SmartBatteryGroupDataType);
    after_sales_feature_arr.push_back(ADSBFlightDataDataType);
    after_sales_feature_arr.push_back(ADSBFlightOriginalDataType);
    after_sales_feature_arr.push_back(FlyForbidDBuuidDataType);
    after_sales_feature_arr.push_back(FlySafeLimitInfoDataType);
    after_sales_feature_arr.push_back(FlySafeUnlockLicenseUserActionInfoDataType);
    after_sales_feature_arr.push_back(FlightHubInfoDataType);
    after_sales_feature_arr.push_back(npzeXkozKlNHPjUQ);
    for (auto iter = after_sales_feature_arr.begin(); iter != after_sales_feature_arr.end(); iter ++) {
        map[(*iter)] = FeaturePoint::AfterSalesFeature;
    }
    
    auto plaintext_feature_arr = std::vector<FlightRecordDataType>();
    plaintext_feature_arr.push_back(FlightRecordRecover);
    plaintext_feature_arr.push_back(KeyStorage);
    for (auto iter = plaintext_feature_arr.begin(); iter != plaintext_feature_arr.end(); iter ++) {
        map[(*iter)] = FeaturePoint::PlaintextFeature;
    }
    
    auto flight_hub_arr = std::vector<FlightRecordDataType>();
    flight_hub_arr.push_back(FlightHubInfoDataType);
    for (auto iter = flight_hub_arr.begin(); iter != flight_hub_arr.end(); iter ++) {
        map[(*iter)] = FeaturePoint::FlightHubFeature;
    }
    
    auto dji_fly_custom_feature_arr = std::vector<FlightRecordDataType>();
    dji_fly_custom_feature_arr.push_back(CustomFlightRecordDataType);
    dji_fly_custom_feature_arr.push_back(ShowTipsFlightRecordDataType);
    dji_fly_custom_feature_arr.push_back(ShowWarningFlightRecordDataType);
    dji_fly_custom_feature_arr.push_back(APPOperationDataType);
    dji_fly_custom_feature_arr.push_back(ShowSeriousWarningFlightRecordDataType);
    dji_fly_custom_feature_arr.push_back(AppLowFreqCustomDataType);
    dji_fly_custom_feature_arr.push_back(GOBusinessDataType);
    for (auto iter = dji_fly_custom_feature_arr.begin(); iter != dji_fly_custom_feature_arr.end(); iter ++) {
        map[(*iter)] = FeaturePoint::DJIFlyCustomFeature;
    }
    
    return map;
}
