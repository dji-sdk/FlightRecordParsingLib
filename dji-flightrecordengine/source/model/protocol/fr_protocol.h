//
//  fr_protocol.h
//  FlightRecordEngine
//
//

#ifndef fr_protocol_h
#define fr_protocol_h

#include <stdint.h>
#include <stdbool.h>

#define MOMENTPICNAMELEN 30
#define MomentPicNum 4
#define DetailInfo_MD5_DIGEST_LENGTH 16
#define MAPLOCATIONNAMELEN 20
#define newDetailInfoReservedLen 19
#define Info_UUID_LENGTH 36
#define CurrentFREncryptMagicVersion 0
#define detailInfoEndCheckSum 12345
#define DJI_MSG_HCRC_INITCRC 0x77
#define DJISNLength 16

#pragma pack(1)

typedef struct{
    char locality[MAPLOCATIONNAMELEN*2];
    char administrativeArea[MAPLOCATIONNAMELEN*2];
}highVersionLocation;

typedef struct{
    uint64_t encryptMagicVersion;
    uint8_t reserved[80];
}DJIFlightRecordPrefixMagic;

typedef struct {
    uint8_t versions[4];
} VersionStructInfo;

typedef struct{
    uint8_t senderType;
    uint8_t subSenderType;
    VersionStructInfo firmwareVersion;
}singleVersionInfo;

typedef enum : uint8_t {
    DJIFlightRecordComponentType_None = 0,
    DJIFlightRecordComponentType_Camera = 1,
    DJIFlightRecordComponentType_FlightController = 2,
    DJIFlightRecordComponentType_RC = 3,
    DJIFlightRecordComponentType_Battery = 4,
    DJIFlightRecordComponentType_SSD = 5,
    DJIFlightRecordComponentType_Gimbal = 6,
} DJIFlightRecordComponentType;

typedef struct {
    DJIFlightRecordComponentType type;
    uint8_t seq;
    uint8_t dataLength;
    uint8_t componentSN[0];
} DJIFlightRecordComponentSN;

typedef enum {
    VisionGroupDataType_VisionDetectionRadarFront = 0,
    VisionGroupDataType_VisionDetectionRadarBack = 1,
    VisionGroupDataType_VisionDetectionRadarRight = 2,
    VisionGroupDataType_VisionDetectionRadarLeft = 3,
    VisionGroupDataType_VisionDetectionRadarTop = 4,
    VisionGroupDataType_VisionDetectionRadarDown = 5,
    VisionGroupDataType_VisionDetectionRadarReserve1 = 6,
    VisionGroupDataType_VisionDetectionRadarReserve2 = 7,

    VisionGroupDataType_MCAvoidStatus = 8, //size 2byte
    VisionGroupDataType_GuidanceDetect = 9,

    VisionGroupDataType_WarningStatus = 10,

    VisionGroupDataType_KindNum,

    VisionGroupDataType_End = 254
} FlightRecordVisionGroupDataType;

typedef struct
{
    uint16_t IuFKGSeqLbNNVUdH;
    uint8_t uGSyWlfwSJTWStcB;
} iDwTaliNfavePQhm;

typedef struct
{
    uint8_t XnODnCdVETKZCczz:4;
    uint8_t wQZNZcVOTljxufpH :4;
} EOscGCRXpfhuQSfb;

typedef struct
{
    union
    {
        struct
        {
            uint8_t VnEJRXrIabkYPTCj:1;
            uint8_t KllAkSvLWIaCoAxO:1;
            uint8_t fxXFtmTJfOAswBrR:1;
            uint8_t nctuCdhyrlcmNDzs:1;
            uint8_t HIUsLwmSXqcrBkcO:1;
            uint8_t sXBurewjSpxNggqa:1;
            uint8_t uGtLAWigilguYROi:1;
            uint8_t gRWVdyqpURKehiSB:1;
        } HKvtSapyhfcsbwVZ;
        uint8_t WUuXeyvwayYrvSWX;
    };
    EOscGCRXpfhuQSfb front_detect;
    EOscGCRXpfhuQSfb right_detect;
    EOscGCRXpfhuQSfb back_detect;
    EOscGCRXpfhuQSfb left_detect;
    uint8_t snwVqIClznacbXRh :1;
    uint8_t qnKBHAwVLMLULUrN :1;
    uint8_t sMJmnQXlcmpYCpWI  :1;
    uint8_t pMuhWJOFxIvNvxNE  :1;
    uint8_t UNYgyhRfeknvIxro:4;
    uint8_t AzbYvHwcEkoWpnGn;
} JYgXYyXqHVEIrYhz;

typedef struct
{
    uint8_t NwrAouTNkRnwEwRl :5;
    uint8_t OXcuQyrlPVXRDtah:3;
    iDwTaliNfavePQhm detect_distance[1];
    uint8_t WmegJUzNtcBxGdys;
} GSXuwjcwajRoXzYA;

typedef struct{
    union {
        uint64_t detailDataOffsetFromHead;
    };
    
    uint16_t detailInfoLength;
    uint8_t detailInfoFormatVersion;
    uint8_t XpQlMxyqxHsJtYDP;
}DJIFlightRecordDetailFilePrefixStruct;

typedef struct{
    unsigned char userAPICenterIDMD5[DetailInfo_MD5_DIGEST_LENGTH];

    float takeOffAltitude;

    uint8_t productType;

    int64_t qgNbXQTmJJHkjsAO;
    char aircraftName[32];
    uint8_t aircraftSN[16];
    uint8_t cameraSN[16];
    uint8_t rcSN[16];
    uint8_t batterySN[16];
    uint8_t appVersion[4];

    uint8_t LRnZZvSDJoiTwFzY;

    char reserved[newDetailInfoReservedLen];
}DJINewFlightRecordDetailDataInfoStruct;

typedef struct{
    union
    {
        highVersionLocation highVLocation;
    } locationName;

    uint8_t lOfEjLMyMNwSgxCj;
    uint8_t idXrIhPwYvVuUCsU;

    uint8_t HXqxzZFWmOnyUcZl;

    int32_t recordLineCount;
    int32_t detailInfoCheckSum;
    int64_t timeStamp;
    double longitude;
    double latitude;
    float totalDistance;
    int32_t totalTime;
    float maxHeight;
    float maxHorizontalSpeed;
    float maxVirticalSpeed;
    int32_t captureNum;
    int64_t videoTime;
    int32_t momentPicImageBufferLen[MomentPicNum];
    int32_t momentPicShrinkImageBufferLen[MomentPicNum];
    double momentPicLongitude[MomentPicNum];
    double momentPicLatitude[MomentPicNum];
    int64_t nlHMIOjQGfftyvQw;

    union
    {
        DJINewFlightRecordDetailDataInfoStruct newFRData;
    } ;
    
    char uuid[Info_UUID_LENGTH];
    
} DJIFlightRecordDetailDataEndStruct;


typedef struct
{
    uint8_t signal_percent:7;
    
    uint8_t is_up         :1;
    
    int8_t aerail_signal[2];
} dji_ofdm_radio_signal_push;

typedef struct
{
    
    double longitude;
    
    double latitude;
    
    int16_t barometer_height;
    
    int16_t speed_x;
    
    int16_t speed_y;
    
    int16_t speed_z;
    
    int16_t pitch;
    
    int16_t roll;
    
    int16_t yaw;
    
    uint8_t control_mode :7;
    
    uint8_t rc_outcontrol:1;
    uint8_t FcLIaBnHGrIdCPae;
    uint8_t alXJEnnqKohpOrIv      :1;
    
    uint8_t groundOrSky     :2;
    
    uint8_t isMotorUp       :1;
    uint8_t FyPwzqNxTELNHBFq:1;
    uint8_t BDnRRfEKLIFHPbYk     :3;
    uint8_t owwcYsTwwGyawhTh      :1;
    
    uint8_t batteryWarning    :2;
    uint8_t PPqGKRDqqvfWaPEN:1;
    uint8_t NTWSdyzVyGjeZytv :1;
    uint8_t vxLdBoDOQIKNvesn       :2;
    
    uint8_t isGPSValid        :1;
    
    uint8_t isCompassError :1;
    uint8_t HJFuZjYdhVqQYybR:1;
    
    uint8_t gpsSignalLevel :4;
    uint8_t BeqludSZijuZuhVJ    :2;
    uint8_t FuMAiwCgVLJzMQki          :1;
    uint8_t MDFMUARFxhpdJtmI       :1;
    uint8_t lRLOYosJLeInQfmo    :1;
    uint8_t dbBvkdKrlcmvZarp          :1;
    uint8_t sHDpcOoUTOCyuKeV        :1;
    uint8_t mOEVFFHhLfbwkMYj        :1;
    uint8_t zLsFXPLyQrHXFFUf:1;
    uint8_t SBVtcuthJBEgAhpq  :1;
    
    uint8_t gps_num;
    uint8_t kRkpOaMocJqXhYiC;
    uint8_t wJpEViPlInceBxUJ:7;
    uint8_t sfLKJziSEyBkGWYo:1;
    uint8_t NDZtBUirCTogtANe              :4;
    uint8_t aklFKRILmiQEdRGR:1;
    uint8_t GDxNbhaHjMNkkVZj         :1;
    uint8_t hOFRFXHicubKMlDx          :1;
    uint8_t ZWTfUyiWnoIXzHvU           :1;
    uint8_t EfrqbiuncIQowIcw;
    uint8_t QXBTzpVpVljFKBAc;
    uint16_t lastFlightTime;
    
    uint8_t startUpTimes;
    uint8_t itVJTUmVhBSRyFyP   :7;
    uint8_t qDnfgctEHRqWvwNB:1;
    uint8_t YeiIzOEFVCzhMWuf  :7;
    uint8_t mbPYYKtaKTRiSNrF:1;
    
    uint8_t versionC;
    
    uint8_t droneType;
    uint8_t sXVeYVkmfPPqVmfH;
    uint8_t apvMQrDukxndFPXS;
    uint8_t nXvqtfHDnlzNwKsq;
    uint8_t ZCmCGCIrRKmoBDwU;
} dji_fc_osd_push;

typedef struct
{
    
    int16_t pitch;
    
    int16_t roll;
    
    int16_t yaw;
    
    uint8_t reserved2:5;
    
    uint8_t reset    :1;
    
    uint8_t work_mode:2;
    
    int8_t roll_adjust_rad;
    
    union
    {
        uint8_t EbpoVfmTdNuoakDp[2];
        int16_t yaw_angle_opposite_drone;
        struct
        {
            uint16_t RMvHaTeSlxxppcGO:2;
            uint16_t SkgawZblAgHXAkuK:2;
            uint16_t cqJMeRGaDKKRAwCj:12;
        };
    };
    
    uint8_t pitch_limited    :1;
    
    uint8_t row_limited      :1;
    
    uint8_t yaw_limited      :1;
    
    uint8_t autoCalibration  :1;
    
    uint8_t calibration_state:1;
    
    uint8_t install_direction:1;
    
    uint8_t gimbal_stuck     :1;
    
    uint8_t reserved         :1;
    
    uint8_t params_version:4;
    
    uint8_t hAtaEGQpIuTAFkMC       :1;
    
    uint8_t DIvYScGrQQKbwOuw  :1;
    
    uint8_t EcdDdDtDAFSpTNNY   :1;
    
    uint8_t hZjyCfMJxJUdzEtJ     :1;
    
    uint32_t XspGzJMvcaqlgbyV;
    
    int16_t PoZhRiWLCQXbtlMc;
    
    int8_t pitch_adjust_degree;
    
    int8_t yaw_trim_val;
    
    uint16_t JpmwBAxOFkkYfiAt;
    
    int16_t UCMPrfbMIXXgdbbw;
    
    float HRQDJsOHYmzHUdbp[4];
    
    float XjzTmVGMyLEqEcRE;
    
    uint8_t XjImTtRNMHCTUvTx;
} dji_gimbal_attitude_response;

typedef struct
{
    
    uint16_t current_voltage[6];
} dji_center_single_battery_voltage;

typedef struct
{
    
    uint8_t relative_volume;
    
    uint16_t current_voltage;
    
    uint16_t current_capacity;
    
    uint16_t full_capacity;
    
    uint8_t battery_life;
    
    uint16_t batery_circle_time;
    
    uint32_t hmrbnunZGCEvClsY;
    
    int16_t current;
    
    dji_center_single_battery_voltage single_batterys;
    
    uint16_t serial_number;
    uint16_t WDaTNYQHmbbqgJHb;
    
    uint16_t temperature;
    
    uint8_t connect_state;
    
    uint16_t sum_learn_count;
    
    uint16_t latest_learn_cycle;
    
    uint8_t battery_on_charge:1;
    
    uint8_t reverse          :7;
} dji_centerboard_push_battery_common_info_push;

typedef struct
{
    
    uint16_t remain_fly_time;
    
    uint16_t need_gohome_time;
    
    uint16_t need_land_time;
    
    uint16_t gohome_electricity;
    
    uint16_t land_electricity;
    
    float safe_fly_radius;
    
    float electricity_consume_speed;
    uint32_t smart_battery_state;
    
    uint8_t need_gohome;
    
    uint8_t cancel_count;
    
    uint16_t battery_voltage;
    
    uint8_t power_percent;
    
    uint8_t battery_warning_value    :7;
    
    uint8_t is_battery_warning_enable:1;
    
    uint8_t serious_battery_warning_value :7;
    
    uint8_t serious_battery_warning_enable:1;
    // 保留
    uint8_t rsvd;
} dji_fc_electricity_push;

typedef struct
{
    
    
    int16_t yaw;
    
    
    int16_t pitch;
    
    
    int16_t distance;
} dji_oa_obstacle_info;

typedef enum
{
    DJI_CAMERA_SDCARD_STATUS_NORMAL = 0,
    DJI_CAMERA_SDCARD_STATUS_NO_CARD = 1,
    DJI_CAMERA_SDCARD_STATUS_INVALID_CARD = 2,
    DJI_CAMERA_SDCARD_STATUS_W_POROTECTED = 3,
    DJI_CAMERA_SDCARD_STATUS_UNFORMATTED = 4,
    DJI_CAMERA_SDCARD_STATUS_FORMATING = 5,
    DJI_CAMERA_SDCARD_STATUS_ILLEGAL_FILE_SYS = 6,
    DJI_CAMERA_SDCARD_STATUS_CARD_BUSY = 7,
    DJI_CAMERA_SDCARD_STATUS_CARD_FULL = 8,
    DJI_CAMERA_SDCARD_STATUS_CARD_SPEED_LOW = 9,
    DJI_CAMERA_SDCARD_STATUS_UNKOWN_ERROR = 10,
    DJI_CAMERA_SDCARD_STATUS_INDEX_MAX = 11,
    DJI_CAMERA_SDCARD_STATUS_INITIALIZE = 12,
    DJI_CAMERA_SDCARD_STATUS_SUGGEST_FORMAT = 13,
    DJI_CAMERA_SDCARD_STATUS_FILE_REPAIRING = 14,
} DJI_CAMERA_SDCARD_STATUS;

typedef struct{
    
    bool isConnect:1;
    bool isUSBConnect:1;

    bool timerSyncState:1;

    uint8_t captureState:3;
    uint8_t isVideoRecording:2;
    /******1字节********/

    bool LtQGsyAykBKmcckl:1;

    bool hasSDCard:1;
    uint8_t SDCardState:4;

    bool isUpgrading:1;
    uint8_t upgradeError:2;

    bool isHeat:1;
    bool isCaptureDisable:1;
    bool isDDRStoring:1;
    bool contiCapture:1;
    bool hdmiOutputStatus:1;
    uint8_t encryptStatus:2;

    bool fileSynState:1;
    bool rcBtnForbidState:1;
    bool getFocusState:1;
    bool panoTimelapseGimbalState:1;
    bool isEnableTrackingMode:1;
    uint16_t reserved:3;
    /************4字节************/
    uint8_t workMode;
    
    uint32_t sdCardTotalCapacity;
    uint32_t sdCardRemainCapacity;
    uint32_t remainPhotoNum;
    uint32_t remainVideoTimer;
    

    uint16_t recordTime;
    uint8_t cameraType;
    uint8_t shBCSgxGiMpCbUbL;


    
    uint8_t uOaTEmOtfIENVbdC;
}DJIFlightRecordCameraStatusInfoCollectStruct;

enum class AircraftPosition {
    Unknown = 0,
    On_the_ground = 1,
    In_the_air = 2,
};

typedef struct
{
    
    double longitude;
    
    double latitude;
    
    float altitude;
    
    uint16_t recordCount         :1;
    
    uint16_t goHomeMethod        :1;
    
    uint16_t goHomeHead          :1;
    
    uint16_t dynaimcHomePointOpen:1;
    
    uint16_t isNearDistanceLimit :1;
    
    uint16_t isNearHeightLimit   :1;
    
    uint16_t isMultipleModeOpen  :1;
    
    uint16_t reserve             :1;
    
    uint16_t compassState        :2;
    
    uint16_t isCompassAdjust     :1;
    
    uint16_t isBeginnerMode      :1;
    
    uint16_t isIOCOpen           :1;
    
    uint16_t IOCMode             :3;
    
    uint16_t goHomeHeight;
    
    int16_t iocCourseLockAngle;
    
    uint8_t flightRecordSDState;
    
    uint8_t recordSDCapacityPercent;
    
    uint16_t recordSDLeftTime;
    
    uint16_t currentFlightRecordIndex;
    uint16_t mhvdESfaSDiMndbu:14;
    uint16_t gale_warning          :1;
    uint8_t GjmyaynoWTyPzGDJ:5;
    uint16_t gale_serious_warning  :1;
    uint16_t AwsOZXIcKBVyaLPj:11;
    uint8_t QPvwHjSkqiwSvHfF             :5;
    
    uint8_t is_limit_height_releative_height:1;
    uint8_t reserved3                       :2;
    
    float limit_height_meter;
    uint32_t TFzBXePYCyJbWMKO;
    uint8_t RxgloInufinFIzEo;
    uint32_t ZCbdnDoUggjcheTQ;
    uint16_t ttxLrCMFyNsVgTPF;
    uint8_t acaNtzPAIHMgMQjs[16];
    
    uint8_t OWDPPdjKzTQhurwU;
} dji_fc_fc_osd_lowfreq_push;

typedef struct
{
    uint16_t pcaFdLtqshmtOQJx          :1;
    uint16_t gSxEGGJhfFYvpnpn              :1;
    uint16_t WXaFjBiEftixmXIg   :1;
    uint16_t awDwZRRmWAGTHVWe      :1;
    uint16_t xKAzqnosDpSSJWpG           :1;
    
    uint16_t avoid_ground_force_landing_flag:1;
    uint16_t qsXYqFyBLSYKVBRj         :1;
    uint16_t RJEHTqKFBxvxPQBn        :1;
    uint16_t bfSeJHAuVMEsHAkT       :1;
    uint16_t ApTLPSZfobpImHbN            :1;
    uint16_t OXvfYzYQZXBRGlJR         :1;
    uint16_t OAxCsPDRLiLERJos       :1;
    uint16_t rePruwwodJtpzMyQ   :1;
    uint16_t GNqlLYGTcNLUwUHY           :1;
    uint16_t vLRfeAHVcTtuxZLI     :1;
    uint16_t aRHnAKcdmSpWDhES                        :1;
} TMEcHTnPNccJUFVk;

typedef struct{
    
    uint8_t failSafeProtection;
    /**
     *  typedef NS_ENUM(uint8_t, DJIFlightFailSafeActionType) {
     DJIFlightFailSafeActionTypeHover = 0,
     DJIFlightFailSafeActionTypeLanding,
     DJIFlightFailSafeActionTypeGoHome
     };
     */

    
    
    uint8_t mcParam_CONFIG_MVO_CFG_MVO_FUNC_EN_0:1;
    
    uint8_t mcParam_CONFIG_AVOID_OBSTACLE_LIMIT_CFG_AVOID_OBSTACLE_ENABLE_0:1;
    
    uint8_t mcParam_CONFIG_AVOID_OBSTACLE_LIMIT_CFG_USER_AVOID_ENABLE_0:1;
    uint8_t reserved:5;
}DJIFlightRecordCollectMCParamStruct;

typedef struct{
    uint8_t menu:1;
    uint8_t playback:1;
    uint8_t record:1;
    uint8_t reserved:5;
    
    uint16_t channel0:11 ;
    uint16_t channel1:11 ;
    uint16_t channel2:11 ;
    uint16_t channel3:11 ;
    uint16_t channel4:11 ;
    uint16_t channel5:11 ;
    uint16_t channel6:11 ;
    uint8_t ioc_key:2;
    uint8_t rs_key:1;
    
    
    uint8_t button:1;
    uint8_t data:5;
    uint8_t symbol:1;
    uint8_t change:1;
    
    
    uint8_t shutter:1;
    uint8_t focus:1;
    uint8_t mode_sw:2;
    uint8_t transform_sw:2;
    uint8_t gohome:2;
} dji_special_control_joy_stick;

typedef struct
{
    
    uint16_t ch_a;
    
    uint16_t ch_e;
    
    uint16_t ch_t;
    
    uint16_t ch_r;
    
    uint16_t GYRO;
    
    uint8_t wheel_btn_down:1;
    
    uint8_t wheel_offset  :5;
    
    uint8_t wheel_polarity:1;
    
    uint8_t wheel_change  :1;
    
    uint8_t transform_btn_reserve:3;
    
    uint8_t return_btn           :1;
    
    uint8_t mode_switch          :2;
    
    uint8_t transform_switch     :2;
    
    uint8_t reserved                 :1;
    
    uint8_t custom_function_btn4_down:1;
    
    uint8_t custom_function_btn3_down:1;
    
    uint8_t custom_function_btn2_down:1;
    
    uint8_t custom_function_btn1_down:1;
    
    uint8_t playback_btn_down        :1;
    
    uint8_t shutter_btn_down         :1;
    
    uint8_t focus_btn_down           :1;
    
    uint8_t bandwidth;
    
    uint8_t gimbal_control_enable;
    union
    {
        
        uint16_t right_wheel_channel;
        struct
        {
            
            uint16_t custom_function_button3_down:1;
            
            uint16_t custom_function_button4_down:1;
            uint16_t rc_pro_reserved1            :14;
            uint16_t rc_pro_reserved2;
            
            uint16_t right_gear;
            
            uint16_t left_lever;
            
            uint16_t right_lever;
        };
    };
} dji_rc_channel_params_push;

typedef struct{
    int8_t camereShoot;
    int8_t videoShoot;
    float Hspeed;
    float Mileage;
    uint64_t updateTimeStamp;
}DJIFlightRecordCustomInfoStruct;

typedef struct{
    uint8_t productType;
    uint8_t appVersion[4];
    uint8_t aircraftSN[DJISNLength];
    char aircraftName[32];
    int64_t qgNbXQTmJJHkjsAO;
    uint8_t cameraSN[DJISNLength];
    uint8_t rcSN[DJISNLength];
    uint8_t batterySN[DJISNLength];

    uint8_t gimbalType;

}DJIFlightRecordRecoverInfoStruct;

typedef struct{
    double latitude;
    double longitude;
    float horizontalAccuracy;
}DJIFlightRecordAppLocation;

typedef struct
{
    uint16_t detect_distance_CM;
    uint8_t warning_level;
} dji_front_detection_item;
typedef struct
{
    uint8_t detection_count :5;
    uint8_t sensor_direction:3;
    dji_front_detection_item detect_distance[1];
    uint8_t WmegJUzNtcBxGdys;
} dji_vision_push_front_detetion_push;

typedef enum : uint8_t {
    SmartbatteryGroupDataType_Reserved = 0,
    SmartbatteryGroupDataType_StaticInfo = 1,
    SmartbatteryGroupDataType_DynamicInfo = 2,
    SmartbatteryGroupDataType_SingleVoltage = 3,
} FlightRecordSmartbatteryGroupDataType;

typedef struct
{
    uint8_t index;
    uint32_t designed_capacity;
    uint16_t loop_times;
    uint32_t full_voltage;
    uint16_t aeWHGGhmoNrBdLNA;
    uint16_t serial_number;
    uint8_t dOWAZxrkcBkZGIyM[10];
    uint8_t xNBTSosAPjdLetSY[5];
    uint8_t version_number[8];
    uint8_t battery_life;
    uint8_t battery_type;
} dji_smart_battery_get_static_info_ios;

typedef struct
{
    uint8_t index;
    int32_t current_voltage;
    int32_t current_current;
    uint32_t full_capacity;
    uint32_t remained_capacity;
    int16_t temperature;
    uint8_t cell_count;
    uint8_t capacity_percent;
    uint64_t bettery_state;
    uint8_t ruliSrUOVpYUtTVj;
    uint8_t UFDpPVigIERuubKI;
    uint8_t UPrFxwqwZYtntcGg;
    int16_t WTdsLHJXppbkCbWt;
} dji_battery_dynamic_info;

typedef struct
{
    uint8_t index;
    uint8_t cell_count;
    uint16_t cell_voltage[0];
} dji_cell_voltage_info;

typedef struct
{
    uint8_t distance_level:4;
    uint8_t warning_level :4;
} dji_guidance_detection_warning_info;

typedef struct
{
    union
    {
        struct
        {
            uint8_t brake_flag                 :1;
            uint8_t vision_work_flag           :1;
            uint8_t ass_enable_flag            :1;
            uint8_t AXhYUFwgoJnueLeh    :1;
            uint8_t front_detect_available_flag:1;
            uint8_t right_detect_available_flag:1;
            uint8_t back_detect_available_flag :1;
            uint8_t left_detect_available_flag :1;
        } visionFlag;
        uint8_t oa_flag;
    };
    dji_guidance_detection_warning_info front_detect;
    dji_guidance_detection_warning_info right_detect;
    dji_guidance_detection_warning_info back_detect;
    dji_guidance_detection_warning_info left_detect;
    uint8_t front_allow :1;
    uint8_t right_allow :1;
    uint8_t back_allow  :1;
    uint8_t left_allow  :1;
    uint8_t reserv_allow:4;
    uint8_t WmegJUzNtcBxGdys;
} dji_vision_push_guidance_detetion_push;

typedef struct
{
    uint16_t avoid_obstacle_enable          :1;
    uint16_t user_avoid_enable              :1;
    uint16_t avoid_obstacle_work_flag_old   :1;
    uint16_t emergency_brake_work_flag      :1;
    uint16_t go_home_avoid_enable           :1;
    uint16_t avoid_ground_force_landing_flag:1;
    uint16_t radius_limit_work_flag         :1;
    uint16_t airport_limit_work_flag        :1;
    uint16_t avoid_obstacle_work_flag       :1;
    uint16_t horiz_near_boundary            :1;
    uint16_t is_avoid_overshoot_act         :1;
    uint16_t vert_low_limit_work_flag       :1;
    uint16_t vert_airport_limit_work_flag   :1;
    uint16_t roof_limit_work_flag           :1;
    uint16_t hit_ground_limit_work_flag     :1;
    uint16_t reserve                        :1;
} dji_fc_avoid_status_push;

typedef struct {
    uint8_t is_tracking:1;
    uint8_t is_tapfly:1;
    uint8_t is_homing:1;
    uint8_t is_landing:1;
    uint8_t is_face_detect:1;
    uint8_t is_moving_object_detect:1;
    uint8_t is_gps_assistant:1;
    uint8_t is_watching:1;
} AircraftVisionStatus;

typedef struct {
    uint32_t available:1;
    uint32_t cannot_by_pass:1;
    uint32_t descending:1;
    uint32_t braeking:1;
    
    uint32_t up_by_passing:1;
    uint32_t down_by_passing:1;
    uint32_t left_by_passing:1;
    uint32_t right_by_passing:1;
}DJITomatoVisionTrackingActiveAvoidStstusInfo;

typedef struct
{
    //4byte
    uint8_t trackingExitCode:4;
    uint8_t tracking_gps_assistent_flag_aircraft_unavailable:1;
    uint8_t tracking_gps_assistent_flag_user_unavailable:1;
    uint8_t tracking_gps_assistent_flag_gps_miss_match:1;
    uint8_t is_quick_movie:1;
    
    //5byte
    DJITomatoVisionTrackingActiveAvoidStstusInfo tracking_avoid;
    
    //6byte
    uint8_t mFnFMSeIPDgKytAd:1;
    uint8_t obstacle_can_not_fly:1;
    uint8_t breaking_not_fly:1;
    uint8_t up_fly_by:1;
    uint8_t left_fly_by:1;
    uint8_t right_fly_by:1;
    uint8_t stick_input:1;
    uint8_t dir_not_valid:1;
    
    uint8_t user_pitch_stick_backward:1;
    uint8_t lower_limit_mode:1;
    uint8_t GDsXYpIYWGlZKFjR:1;
    uint8_t is_tap_to_go_on:1;
    uint8_t reserved4:4;
} DJITomatoVisionTrackingStatus;

typedef enum: uint8_t
{
    DJITomatoVisionLandingStageNone,
    DJITomatoVisionLandingStageTurnYaw,
    DJITomatoVisionLandingStageLanding,
} DJITomatoVisionLandingStage;

typedef enum: uint8_t
{
    gGOuRJRHsQxvuIog = 0,
    DJITomatoVisionGoHomeStageTurnYaw,
    DJITomatoVisionGoHomeStageGoingHome,
    DJITomatoVisionGoHomeStageHovering,
    DJITomatoVisionGoHomeStageReCalculate
} DJITomatoVisionGoHomeStage;

typedef struct
{
    uint16_t gpsAbnormal:1;
    uint16_t frontVisionAbnormal:1;
    DJITomatoVisionGoHomeStage gohomeStage:3;
    uint8_t aeWHGGhmoNrBdLNA:1;
    uint8_t goingHome:1;
    uint8_t reserved1:1;
    //
    uint8_t reserved;
}DJITomatoVisionSmartGoHomeState;

typedef enum : uint8_t
{
    DJITomatoVisionLandingTypeNone,
    DJITomatoVisionLandingTypePreciseLanding,
    DJITomatoVisionLandingTypeNormalLanding,
} DJITomatoVisionLandingType;

typedef struct
{
    uint8_t obstacle:1;
    DJITomatoVisionLandingStage landingStage:2;
    uint8_t landingCorrecting:1;
    uint8_t landingExecuting:1;
    DJITomatoVisionLandingType landingType:2;
    uint8_t reserved1:1;
    //
    uint8_t reserved;
}DJITomatoVisionPreciseLandingState;

typedef struct
{
    DJITomatoVisionSmartGoHomeState gohomeState;
    DJITomatoVisionPreciseLandingState landingState;
} DJITomatoVisionSmartGoHomeStatus;

typedef struct {
    uint8_t something_wrong_with_tracking:1;
    uint8_t something_wrong_with_pointing:1;
    uint8_t vkbJCJKQGbBnpBeN:1;
    uint8_t imu_data_lost:1;
    uint8_t gimbal_data_lost:1;
    uint8_t rc_data_lost:1;
    uint8_t jambIbhEyIrNuKyM:1;
    uint8_t reserved:1;
    
    //1 byte
    uint8_t MlSoGIuYgQYYToHt:1;
    uint8_t zqUmkrYmCLficmZW:1;
    uint8_t jhDMGHdrcYMcZZun:1;
    uint8_t csKoYViBlBwbhyoZ:1;
    uint8_t drone_not_take_off:1;
    uint8_t user_stoped:1;
    uint8_t is_tripod_mode:1;
    uint8_t fc_limited:1;
    
    //2 byte
    uint8_t buwrufZwBLfoCoHj:1;
    uint8_t disconnect_with_app:1;
    uint8_t cannot_control_mc:1;
    uint8_t enter_limit_zoon:1;
    uint8_t cZYSyWvfbxZKIaMw:1;
    uint8_t fly_limit_zone:1;
    uint8_t spzWJFtACyJPIBup:1;
    uint8_t is_drawing_fly:1;
    
    //3byte
    AircraftVisionStatus aircraftVisionStatus;
    
    union
    {
        DJITomatoVisionTrackingStatus trackingStatus;
        DJITomatoVisionSmartGoHomeStatus smartGoHomeStatus;
    } missionStatus;
    
    // 8 bytes
    uint32_t WbOuFzQdFMwWdEvD;
    
    //12 byte
    uint8_t reserved3:6;
    uint8_t ext_reach_distence_limit:1;
    uint8_t ext_reach_high_limit:1;
    
} DJITomatoVisionCommonWarningStatusData;

typedef struct
{
    uint8_t hour;
    uint8_t minute;
    uint8_t second;
    uint16_t year;
    uint8_t month;
    uint8_t day;
} dji_rc_time;

typedef struct
{
    dji_rc_time time;
    int32_t latitude;
    int32_t longitude;
    int32_t v_x;
    int32_t v_y;
    uint8_t gps_num;
    float accuracy;
    uint16_t valid_data;
} dji_rc_gps_info_push;

typedef enum
{
    DJI_CAMERA_WORKING_MODE_CAPTURE = 0,
    DJI_CAMERA_WORKING_MODE_RECORDING = 1,
    DJI_CAMERA_WORKING_MODE_PLAYBACK = 2,
    DJI_CAMERA_WORKING_MODE_TRANSCODE = 3, 
    DJI_CAMERA_WORKING_MODE_TUNING = 4,
    DJI_CAMERA_WORKING_MODE_POWER_SAVE = 5,
    DJI_CAMERA_WORKING_MODE_DOWNLOAD = 6,
    DJI_CAMERA_WORKING_MODE_XCODE_PLAYBACK = 7,
    DJI_CAMERA_WORKING_MODE_BROADCAST = 8,
} DJI_CAMERA_WORKING_MODE;

typedef enum
{
    DJI_CAMERA_TYPE_Insipre1 = 0, // Inpire 1
    DJI_CAMERA_TYPE_Insipre1Pro = 1, // Inpire 1 pro
    DJI_CAMERA_TYPE_Phantom4 = 6, // Phantom 4
} DJI_CAMERA_TYPE;

#pragma pack()

#endif /* fr_protocol_h */
