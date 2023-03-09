//
//  FlightRecordProtocolEnum.h
//  FlightRecordWriter
//
//  Copyright © 2017 DJI. All rights reserved.
//

#ifndef FlightRecordProtocolEnum_h
#define FlightRecordProtocolEnum_h

#include <stdint.h>
#include <stdbool.h>

typedef enum {
    LineEndFlightRecordDataType=-1,
    
    OSDFlightRecordDataType = 1,
    OSDHomeFlightRecordDataType = 2,
    GimbalFlightRecordDataType = 3,
    RCFlightRecordDataType = 4,
    CustomFlightRecordDataType = 5,
    MCTripodStateFlightRecordDataType = 6,
    CenterBatteryFlightRecordDataType = 7,
    PushedBatteryFlightRecordDataType = 8,
    ShowTipsFlightRecordDataType = 9,
    ShowWarningFlightRecordDataType = 10,
    RCPushGPSFlightRecordDataType=11,
    RCDebugDataType = 12,
    RecoverInfoDataType = 13,
    AppLocationDataType = 14,
    FirmwareVersionType = 15,
    OFDMDebugDataType = 16,
    
    VisionGroupDataType = 17,
    VisionWaringStringDataType = 18,
    MCParamDataType = 19,
    APPOperationDataType = 20,
    
    AGOSDDataType = 21,
    
    SmartBatteryGroupDataType = 22,
    
    ShowSeriousWarningFlightRecordDataType = 24,
    
    CameraInfoFlightRecordDataType = 25,
    
    ADSBFlightDataDataType = 26,
    ADSBFlightOriginalDataType = 27,
    
    FlyForbidDBuuidDataType = 28,
    AppSpecialControlJoyStickDataType = 29,
    
    AppLowFreqCustomDataType = 30,
    
    NavigationModeGroupedDataType = 31,
    GSMissionStatusDataType = 32,
    AppVirtualStickDataType = 33,
    GSMissionEventDataType = 34,
    WaypointMissionUploadDataType = 35,
    WaypointUploadDataType = 36,
    WaypointMissionDownloadDataType = 38,
    WaypointDownloadDataType = 39,
    
    ComponentSerialNumberDataType = 40,
    
    AgricultureDisplayField = 41,
    
    AgricultureMg1sAvoidanceRadarPush_Recover = 42,
    AgricultureRadarPush = 43,
    AgricultureSpray = 44,
    RTKDifferenceDataType = 45,
    AgricultureFarmMissionInfo = 46,
    AgricultureFarmTaskTeamDataType = 47,
    AgricultureGroundStationPushData = 48,
    AgricultureOFDMRadioSignalPush = 49,
    FlightRecordRecover = 50,
    
    FlySafeLimitInfoDataType = 51,
    FlySafeUnlockLicenseUserActionInfoDataType = 52,
    FlightHubInfoDataType = 53,
    
    GOBusinessDataType = 54,
    
    npzeXkozKlNHPjUQ = 55,
    KeyStorage = 56,
    
    FlightRecordTypeKindNum,
    
} FlightRecordDataType;

namespace DJI {
    namespace FlightRecord {
        enum class VersionCategory : uint16_t {
            None = 0,
            Version13_1 = 3,
            Version13_2 = 4,
        };
    
        enum class Department : uint8_t {
            Unknown = 0,
            SDK = 1,
            DJIGO = 2,
            DJIFly = 3,
            AgriculturalMachinery = 4,
            Terra = 5,
            DJIPilot = 7,
            GSPro = 8,
        };
    
        typedef struct {
            VersionCategory version;
            Department department;
        } VersionExtension;
    
        enum class Platform : uint8_t {
            Unknown = 0,
            iOS = 1,
            Android = 2,
            Window = 10,
            Mac = 11,
            Linux = 12,
        };
    }
}

#endif /* FlightRecordProtocolEnum_h */
