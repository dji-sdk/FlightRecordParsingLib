//
//  DJIFRProtoParser.cpp
//  FlightRecordStandardizationCpp
//
//  Copyright © 2019 DJISDK. All rights reserved.
//

#include "DJIFRProtoParser.hpp"
#include "fr_standardization_server_creater.h"

using namespace DJIFRProto::Standard;

//MARK: - Common Converter

static RCGPSTime ConvertToRCGPSTime(DJIFR::standardization::RCGPSTimeSharedPtr rc_gps_time_cpp) {
    RCGPSTime rc_gps_time;
    rc_gps_time.set_hour(rc_gps_time_cpp->hour());
    rc_gps_time.set_minute(rc_gps_time_cpp->minute());
    rc_gps_time.set_second(rc_gps_time_cpp->second());
    rc_gps_time.set_year(rc_gps_time_cpp->year());
    rc_gps_time.set_month(rc_gps_time_cpp->month());
    rc_gps_time.set_day(rc_gps_time_cpp->day());
    
    return rc_gps_time;
}

static ComponentInformation ConvertToComponentInformation(DJIFR::standardization::ComponentInformationSharedPtr component_information_cpp) {
    ComponentInformation component_information;
    component_information.set_index(component_information_cpp->index());
    auto firmware_version = component_information_cpp->firmwareVersion();
    for (auto iter = firmware_version.begin(); iter != firmware_version.end(); iter ++) {
        component_information.add_firmwareversion((*iter));
    }
    component_information.set_serialnumber(component_information_cpp->serialNumber());
    
    return component_information;
}

static LocationCoordinate2D ConvertToLocationCoordinate(DJIFR::standardization::LocationCoordinate2DSharedPtr location_cpp) {
    LocationCoordinate2D location;
    location.set_latitude(location_cpp->latitude());
    location.set_longitude(location_cpp->longitude());
    
    return location;
}

static Stick ConvertToStick(DJIFR::standardization::StickSharedPtr stick_cpp) {
    Stick stick;
    stick.set_verticalposition(stick_cpp->verticalPosition());
    stick.set_horizontalposition(stick_cpp->horizontalPosition());
    
    return stick;
}

static RCRightWheel ConvertToRCRightWheel(DJIFR::standardization::RCRightWheelSharedPtr right_wheel_cpp) {
    RCRightWheel right_wheel;
    right_wheel.set_ispresent(right_wheel_cpp->isPresent());
    right_wheel.set_isturned(right_wheel_cpp->isTurned());
    right_wheel.set_isclicked(right_wheel_cpp->isClicked());
    right_wheel.set_value(right_wheel_cpp->value());
    
    return right_wheel;
}

static RCButton ConvertToRCButton(DJIFR::standardization::RCButtonSharedPtr rc_button_cpp) {
    RCButton button;
    button.set_ispresent(rc_button_cpp->isPresent());
    button.set_isclicked(rc_button_cpp->isClicked());
    
    return button;
}

static Attitude ConvertToAttitude(DJIFR::standardization::AttitudeSharedPtr attitude_cpp) {
    Attitude attitude;
    attitude.set_pitch(attitude_cpp->pitch());
    attitude.set_roll(attitude_cpp->roll());
    attitude.set_yaw(attitude_cpp->yaw());
    
    return attitude;
}

static Velocity ConvertToVelocity(DJIFR::standardization::VelocitySharedPtr velocity_cpp) {
    Velocity velocity;
    velocity.set_velocityx(velocity_cpp->velocityX());
    velocity.set_velocityy(velocity_cpp->velocityY());
    velocity.set_velocityz(velocity_cpp->velocityZ());
    
    return velocity;
}

static VirtualStickFlightControlData ConvertToVirtualStickFlightControlData(DJIFR::standardization::VirtualStickFlightControlDataSharedPtr virtual_stick_flight_control_data_cpp) {
    VirtualStickFlightControlData virtual_stick_flight_control_data;
    virtual_stick_flight_control_data.set_pitch(virtual_stick_flight_control_data_cpp->pitch());
    virtual_stick_flight_control_data.set_roll(virtual_stick_flight_control_data_cpp->roll());
    virtual_stick_flight_control_data.set_yaw(virtual_stick_flight_control_data_cpp->yaw());
    virtual_stick_flight_control_data.set_verticalthrottle(virtual_stick_flight_control_data_cpp->verticalThrottle());
    virtual_stick_flight_control_data.set_verticalcontrolmode((VirtualStickVerticalControl_Mode)virtual_stick_flight_control_data_cpp->verticalControlMode());
    virtual_stick_flight_control_data.set_rollpitchcontrolmode((VirtualStickRollPitchControl_Mode)virtual_stick_flight_control_data_cpp->rollPitchControlMode());
    virtual_stick_flight_control_data.set_yawcontrolmode((VirtualStickYawControl_Mode)virtual_stick_flight_control_data_cpp->yawControlMode());
    virtual_stick_flight_control_data.set_rollpitchcoordinatesystem((VirtualStickFlightCoordinate_System)virtual_stick_flight_control_data_cpp->rollPitchCoordinateSystem());
    
    return virtual_stick_flight_control_data;
}

//MARK: - Image Converter

static void ConvertToImageData(ImageData *image_data_proto, DJIFR::standardization::ImageDataSharedPtr imageData_cpp) {
    if (imageData_cpp->coordinate()) {
        (*image_data_proto->mutable_coordinate()) = ConvertToLocationCoordinate(imageData_cpp->coordinate());
    }
    
    auto previewImage_cpp = imageData_cpp->previewImage();
    if (previewImage_cpp) {
        image_data_proto->set_previewimage(previewImage_cpp->data_.get(), previewImage_cpp->length_);
    }
    
    auto thumbnail_cpp = imageData_cpp->thumbnail();
    if (thumbnail_cpp) {
        image_data_proto->set_thumbnail(thumbnail_cpp->data_.get(), thumbnail_cpp->length_);
    }
}

//MARK: - RC State

static RCGPSData ConvertToRCGPSData(DJIFR::standardization::RCGPSDataSharedPtr data_cpp) {
    RCGPSData rc_gps;
    if (data_cpp->time()) {
        (*rc_gps.mutable_time()) = ConvertToRCGPSTime(data_cpp->time());
    }
    if (data_cpp->location()) {
        (*rc_gps.mutable_location()) = ConvertToLocationCoordinate(data_cpp->location());
    }
    rc_gps.set_eastspeed(data_cpp->eastSpeed());
    rc_gps.set_northspeed(data_cpp->northSpeed());
    rc_gps.set_satellitecount(data_cpp->satelliteCount());
    rc_gps.set_accuracy(data_cpp->accuracy());
    rc_gps.set_isvalid(data_cpp->isValid());
    return rc_gps;
}

//MARK: - Vision

static VisionControlState ConvertToVisionControlState(DJIFR::standardization::VisionControlStateSharedPtr vision_control_cpp) {
    VisionControlState vision;
    vision.set_isascentlimitedbyobstacle(vision_control_cpp->isAvoidingActiveObstacleCollision());
    vision.set_isavoidingactiveobstaclecollision(vision_control_cpp->isAvoidingActiveObstacleCollision());
    vision.set_isbraking(vision_control_cpp->isBraking());
    vision.set_isperformingprecisionlanding(vision_control_cpp->isPerformingPrecisionLanding());
    
    return vision;
}

static VisionDetectionState ConvertToVisionDetectionState(DJIFR::standardization::VisionDetectionStateSharedPtr detection_cpp) {
    VisionDetectionState vision;
    vision.set_position((DJIFRProto::Standard::Vision_VisionSensorPosition)detection_cpp->position());
    vision.set_issensorbeingused(detection_cpp->isSensorBeingUsed());
    vision.set_systemwarning((DJIFRProto::Standard::Vision_VisionSystemWarning)detection_cpp->systemWarning());
    vision.set_obstacledistanceinmeters(detection_cpp->obstacleDistanceInMeters());
    auto detectionSectors_cpp = detection_cpp->detectionSectors();
    for (auto iter = detectionSectors_cpp.begin(); iter != detectionSectors_cpp.end(); iter ++) {
        auto detectionSector = vision.add_detectionsectors();
        auto detectionSector_cpp = (*iter);
        detectionSector->set_obstacledistanceinmeters(detectionSector_cpp->obstacleDistanceInMeters());
        detectionSector->set_warninglevel((DJIFRProto::Standard::Vision_ObstacleDetectionSectorWarning)detectionSector_cpp->warningLevel());
    }
    return vision;
}

//MARK: - FrameTimeState Converter

static VisionState ConvertToVisionState(DJIFR::standardization::VisionStateSharedPtr vision_cpp) {
    VisionState vision;
    vision.set_collisionavoidanceenabled(vision_cpp->collisionAvoidanceEnabled());
    if (vision_cpp->controlState()) {
        (*vision.mutable_controlstate()) = ConvertToVisionControlState(vision_cpp->controlState());
    }
    auto detectionStateMap_cpp = vision_cpp->detectionStateMap();
    auto detectionStateMap = vision.mutable_detectionstatemap();
    for (auto iter = detectionStateMap_cpp.begin(); iter != detectionStateMap_cpp.end(); iter ++) {
        int32_t position = (int32_t)(*iter).first;
        (*detectionStateMap)[position] = ConvertToVisionDetectionState((*iter).second);
    }
    return vision;
}

static RCHardwareState ConvertToRCHardwareState(DJIFR::standardization::RCHardwareStateSharedPtr rc_hardware_cpp) {
    RCHardwareState rc_hardware;
    
    if (rc_hardware_cpp->leftStick()) {
        (*rc_hardware.mutable_leftstick()) = ConvertToStick(rc_hardware_cpp->leftStick());
    }
    if (rc_hardware_cpp->rightStick()) {
        (*rc_hardware.mutable_rightstick()) = ConvertToStick(rc_hardware_cpp->rightStick());
    }
    if (rc_hardware_cpp->leftWheel()) {
        rc_hardware.set_leftwheel(rc_hardware_cpp->leftWheel());
    }
    if (rc_hardware_cpp->rightWheel()) {
        (*rc_hardware.mutable_rightwheel()) = ConvertToRCRightWheel(rc_hardware_cpp->rightWheel());
    }
    rc_hardware.set_flightmodeswitch((RCFlightModel_Switch)rc_hardware_cpp->flightModeSwitch());
    if (rc_hardware_cpp->goHomeButton()) {
        (*rc_hardware.mutable_gohomebutton()) = ConvertToRCButton(rc_hardware_cpp->goHomeButton());
    }
    if (rc_hardware_cpp->recordButton()) {
        (*rc_hardware.mutable_recordbutton()) = ConvertToRCButton(rc_hardware_cpp->recordButton());
    }
    if (rc_hardware_cpp->shutterButton()) {
        (*rc_hardware.mutable_shutterbutton()) = ConvertToRCButton(rc_hardware_cpp->shutterButton());
    }
    if (rc_hardware_cpp->playbackButton()) {
        (*rc_hardware.mutable_playbackbutton()) = ConvertToRCButton(rc_hardware_cpp->playbackButton());
    }
    if (rc_hardware_cpp->pauseButton()) {
        (*rc_hardware.mutable_pausebutton()) = ConvertToRCButton(rc_hardware_cpp->pauseButton());
    }
    rc_hardware.set_style((RCAircraftMapping_Style)rc_hardware_cpp->style());
    if (rc_hardware_cpp->GPSData()) {
        (*rc_hardware.mutable_gpsdata()) = ConvertToRCGPSData(rc_hardware_cpp->GPSData());
    }
    
    return rc_hardware;
}

static MobileRemoteControllerState ConvertToMobileRemoteControllerState(DJIFR::standardization::MobileRemoteControllerStateSharedPtr mobileRemoteController) {
    MobileRemoteControllerState mobileRCState;
    mobileRCState.set_leftstickvertical(mobileRemoteController->leftStickVertical());
    mobileRCState.set_leftstickhorizontal(mobileRemoteController->leftStickHorizontal());
    mobileRCState.set_rightstickvertical(mobileRemoteController->rightStickVertical());
    mobileRCState.set_rightstickhorizontal(mobileRemoteController->rightStickHorizontal());
    
    return mobileRCState;
}

static GimbalState ConvertToGimbalState(DJIFR::standardization::GimbalStateSharedPtr gimbalState_cpp) {
    GimbalState gimbalState;
    if (gimbalState_cpp->attitude()) {
        (*gimbalState.mutable_atitude()) = ConvertToAttitude(gimbalState_cpp->attitude());
    }
    gimbalState.set_index(gimbalState_cpp->index());
    gimbalState.set_finetunedroll(gimbalState_cpp->fineTunedRoll());
    gimbalState.set_finetunedpitch(gimbalState_cpp->fineTunedPitch());
    gimbalState.set_finetunedyaw(gimbalState_cpp->fineTunedYaw());
    gimbalState.set_isrollatstop(gimbalState_cpp->isRollAtStop());
    gimbalState.set_isyawatstop(gimbalState_cpp->isYawAtStop());
    gimbalState.set_ispitchatstop(gimbalState_cpp->isPitchAtStop());
    gimbalState.set_yawrelativetoaircraftheading(gimbalState_cpp->yawRelativeToAircraftHeading());
    gimbalState.set_mode((GimbalMode)gimbalState_cpp->mode());
    
    return gimbalState;
}

static FlightControllerState ConvertToFlightControllerState(DJIFR::standardization::FlightControllerStateSharedPtr flightController_cpp) {
    FlightControllerState flightControllerState;
    
    if (flightController_cpp->attitude()) {
        (*flightControllerState.mutable_attitude()) = ConvertToAttitude(flightController_cpp->attitude());
    }
    if (flightController_cpp->velocity()) {
        (*flightControllerState.mutable_velocity()) = ConvertToVelocity(flightController_cpp->velocity());
    }
    if (flightController_cpp->homeLocationCoordinate()) {
        (*flightControllerState.mutable_homelocationcoordinate()) = ConvertToLocationCoordinate(flightController_cpp->homeLocationCoordinate());
    }
    if (flightController_cpp->takeoffLocationAltitude()) {
        flightControllerState.set_takeofflocationaltitude(flightController_cpp->takeoffLocationAltitude());
    }
    if (flightController_cpp->aircraftLocation()) {
        (*flightControllerState.mutable_aircraftlocation()) = ConvertToLocationCoordinate(flightController_cpp->aircraftLocation());
    }
    flightControllerState.set_altitude(flightController_cpp->altitude());
    flightControllerState.set_flightmode((FlightMode)flightController_cpp->flightMode());
    flightControllerState.set_gpssignallevel((GPSSignal_Level)flightController_cpp->gpsLevel());
    flightControllerState.set_satellitecount(flightController_cpp->satelliteCount());
    flightControllerState.set_remainingflighttime(flightController_cpp->remainingFlightTime());
    flightControllerState.set_batterypercentageneededtolandfromcurrentheight(flightController_cpp->batteryPercentageNeededToLandFromCurrentHeight());
    flightControllerState.set_batterypercentageneededtogohome(flightController_cpp->batteryPercentageNeededToGoHome());
    flightControllerState.set_smartrthstate((SmartRTH_State)flightController_cpp->smartRTHState());
    flightControllerState.set_behavior((Connection_FailSafeBehavior)flightController_cpp->behavior());
    if (flightController_cpp->virtualControlData()) {
        (*flightControllerState.mutable_virtualcontroldata()) = ConvertToVirtualStickFlightControlData(flightController_cpp->virtualControlData());
    }
    flightControllerState.set_isfailsafeenabled(flightController_cpp->isFailsafeEnabled());
    flightControllerState.set_aremotorson(flightController_cpp->areMotorsOn());
    flightControllerState.set_ishomelocationset(flightController_cpp->isHomeLocationSet());
    flightControllerState.set_islandingconfirmationneeded(flightController_cpp->isLandingConfirmationNeeded());
    flightControllerState.set_hasreachedmaxflightheight(flightController_cpp->hasReachedMaxFlightHeight());
    flightControllerState.set_hasreachedmaxflightradius(flightController_cpp->hasReachedMaxFlightRadius());
    flightControllerState.set_windwarning((FlightWind_Warning)flightController_cpp->windWarning());
    flightControllerState.set_countofflights(flightController_cpp->countOfFlights());
    flightControllerState.set_flightlogindex(flightController_cpp->flightLogIndex());
    flightControllerState.set_isflying(flightController_cpp->isFlying());
    flightControllerState.set_smartrthcountdown(flightController_cpp->smartRTHCountdown());
    flightControllerState.set_isgpsbeingused(flightController_cpp->isGPSBeingUsed());
    flightControllerState.set_flighttimeinseconds(flightController_cpp->flightTimeInSeconds());
    flightControllerState.set_cumulativeflightdistance(flightController_cpp->cumulativeFlightDistance());
    
    return flightControllerState;
}

static CameraState ConvertToCameraState(DJIFR::standardization::CameraStateSharedPtr camera_state_cpp) {
    CameraState camera_state;
    
    camera_state.set_index(camera_state_cpp->index());
    camera_state.set_isrecording(camera_state_cpp->isRecording());
    camera_state.set_isshootingsinglephoto(camera_state_cpp->isShootingSinglePhoto());
    camera_state.set_isinserted(camera_state_cpp->isInserted());
    camera_state.set_isinitializing(camera_state_cpp->isInitializing());
    camera_state.set_haserror(camera_state_cpp->hasError());
    camera_state.set_isverified(camera_state_cpp->isVerified());
    camera_state.set_isfull(camera_state_cpp->isFull());
    camera_state.set_isformatted(camera_state_cpp->isFormatted());
    camera_state.set_isformatting(camera_state_cpp->isFormatting());
    camera_state.set_isinvalidformat(camera_state_cpp->isInvalidFormat());
    camera_state.set_isreadonly(camera_state_cpp->isReadOnly());
    camera_state.set_totalspaceinmb(camera_state_cpp->totalSpaceInMB());
    camera_state.set_remainingspaceinmb(camera_state_cpp->remainingSpaceInMB());
    camera_state.set_availablecapturecount(camera_state_cpp->availableCaptureCount());
    camera_state.set_availablerecordingtimeinseconds(camera_state_cpp->availableRecordingTimeInSeconds());
    camera_state.set_mode((CameraState_CameraMode)camera_state_cpp->mode());
    
    return camera_state;
}

static BatteryState ConvertToBatteryState(DJIFR::standardization::BatteryStateSharedPtr battery_state_cpp) {
    BatteryState battery_state;
    
    battery_state.set_index(battery_state_cpp->index());
    battery_state.set_voltage(battery_state_cpp->voltage());
    battery_state.set_current(battery_state_cpp->current());
    battery_state.set_temperature(battery_state_cpp->temperature());
    
    auto cellVoltages_cpp = battery_state_cpp->cellVoltages();
    if (cellVoltages_cpp.size() > 0) {
        auto cellVoltages = battery_state.mutable_cellvoltages();
        for (auto iter = cellVoltages_cpp.begin(); iter != cellVoltages_cpp.end(); iter ++) {
            cellVoltages->Add((*iter));
        }
    }
    
    battery_state.set_chargeremaininginpercent(battery_state_cpp->chargeRemainingInPercent());
    battery_state.set_lowbatterywarningthreshold(battery_state_cpp->lowBatteryWarningThreshold());
    battery_state.set_seriouslowbatterywarningthreshold(battery_state_cpp->seriousLowBatteryWarningThreshold());
    battery_state.set_lifetimeremaining(battery_state_cpp->lifetimeRemaining());
    battery_state.set_designcapacity(battery_state_cpp->designCapacity());
    battery_state.set_numberofdischarges(battery_state_cpp->numberOfDischarges());
    battery_state.set_isinsinglebatterymode(battery_state_cpp->isInSingleBatteryMode());
    battery_state.set_fullchargecapacity(battery_state_cpp->fullChargeCapacity());
    battery_state.set_chargeremaining(battery_state_cpp->chargeRemaining());
    
    return battery_state;
}

static void ConvertToGOBusiness(DJIFR::standardization::GOBusinessDataSharedPtr go_business_cpp, GOBusinessData *go_business_proto) {
    if (!go_business_proto || !go_business_cpp) {
        return;
    }
    
    go_business_proto->set_version(go_business_cpp->version());
    go_business_proto->set_tips(go_business_cpp->tips());
    go_business_proto->set_warning(go_business_cpp->warning());
    go_business_proto->set_seriouswarning(go_business_cpp->seriousWarning());
    auto go_business_buffer = go_business_cpp->goBusinessData();
    if (go_business_buffer) {
        go_business_proto->set_gobusinessdata(go_business_buffer->data_.get(), go_business_buffer->length_);
    }
}

static void ConvertToMobileDeviceState(DJIFR::standardization::MobileDeviceStateSharedPtr mobile_device_state_cpp, MobileDeviceState *mobile_device_state_proto) {
    if (!mobile_device_state_cpp || !mobile_device_state_proto) {
        return;
    }
    
    if (mobile_device_state_cpp->coordinate()) {
        (*mobile_device_state_proto->mutable_coordinate()) = ConvertToLocationCoordinate(mobile_device_state_cpp->coordinate());
    }
    
    mobile_device_state_proto->set_horizontalaccuracy(mobile_device_state_cpp->horizontalAccuracy());
}

static void ConvertToAirLinkState(DJIFR::standardization::AirLinkStateSharedPtr air_link_state_cpp, AirLinkState *air_link_proto) {
    if (!air_link_proto || air_link_state_cpp) {
        return;
    }
    
    air_link_proto->set_downlinksignalquality(air_link_state_cpp->downlinkSignalQuality());
    air_link_proto->set_hasdownlinksignalquality(air_link_state_cpp->has_downlinkSignalQuality());
    air_link_proto->set_uplinksignalquality(air_link_state_cpp->uplinkSignalQuality());
    air_link_proto->set_hasuplinksignalquality(air_link_state_cpp->has_uplinkSignalQuality());
}

static void ConvertToFrameTimeState(DJIFR::standardization::ServerFrameTimeStateSharedPtr frame_time_cpp, FrameTimeState *output) {
    
    auto rc_hardware_cpp = frame_time_cpp->rcHardwareState();
    if (rc_hardware_cpp) {
        (*output->mutable_rchardwarestate()) = ConvertToRCHardwareState(rc_hardware_cpp);
    }
    
    auto mobileRCState = frame_time_cpp->mobileRemoteController();
    if (mobileRCState) {
        (*output->mutable_mobileremotecontroller()) = ConvertToMobileRemoteControllerState(mobileRCState);
    }
    
    auto gimbalState = frame_time_cpp->gimbalState();
    if (gimbalState) {
        (*output->mutable_gimbalstate()) = ConvertToGimbalState(gimbalState);
    }
    auto gimbals_cpp = frame_time_cpp->gimbalsState();
    auto gimbals_proto = output->mutable_gimbalsstate();
    for (auto iter = gimbals_cpp.begin(); iter != gimbals_cpp.end(); iter ++) {
        (*gimbals_proto)[(*iter).first] = ConvertToGimbalState((*iter).second);
    }
    
    auto flightcontrollerState = frame_time_cpp->flightControllerState();
    if (flightcontrollerState) {
        (*output->mutable_flightcontrollerstate()) = ConvertToFlightControllerState(flightcontrollerState);
    }
    
    auto cameraState = frame_time_cpp->cameraState();
    if (cameraState) {
        (*output->mutable_camerastate()) = ConvertToCameraState(cameraState);
    }
    auto cameras_cpp = frame_time_cpp->camerasState();
    auto cameras_proto = output->mutable_camerasstate();
    for (auto iter = cameras_cpp.begin(); iter != cameras_cpp.end(); iter ++) {
        (*cameras_proto)[(*iter).first] = ConvertToCameraState((*iter).second);
    }
    
    auto batteryState = frame_time_cpp->batteryState();
    if (batteryState) {
        (*output->mutable_batterystate()) = ConvertToBatteryState(batteryState);
    }
    auto batteries_cpp = frame_time_cpp->batteriesState();
    auto batteries_proto = output->mutable_batteriesstate();
    for (auto iter = batteries_cpp.begin(); iter != batteries_cpp.end(); iter ++) {
        (*batteries_proto)[(*iter).first] = ConvertToBatteryState((*iter).second);
    }
    
    auto go_business_data = frame_time_cpp->goBusinessData();
    if (go_business_data) {
        ConvertToGOBusiness(go_business_data, output->mutable_gobusinessdata());
    }
    
    auto mobile_device_state = frame_time_cpp->mobileDeviceState();
    if (mobile_device_state) {
        ConvertToMobileDeviceState(mobile_device_state, output->mutable_mobiledevicestate());
    }
    
    auto air_link = frame_time_cpp->airlinkState();
    if (air_link) {
        ConvertToAirLinkState(air_link, output->mutable_airlinkstate());
    }
    
    auto vision_data = frame_time_cpp->visionState();
    if (vision_data) {
        (*output->mutable_visionstate()) = ConvertToVisionState(vision_data);
    }
}

//MARK: - Config

Parser::Parser() {
    
}

Parser::~Parser() {
    parser_ = nullptr;
}

//MARK: - Base

FRError Parser::load(const std::string& file_path) {
    parser_ = DJIFR::standardization::CreateServerParser();
    
    auto error = parser_->load(file_path);
    if (error != DJIFR::standardization::SDKError::Success) {
        parser_ = nullptr;
    }
    
    return (FRError)error;
}

FRError Parser::startRequestParser(const std::string& sdk_key, const DJIFR::standardization::RequestCallback &callback) {
    if (!parser_) {
        return FRError::NoParser;
    }
    
    auto error = parser_->startRequestParser(sdk_key, callback);
    
    return (FRError)error;
}

FRError Parser::summaryInformation(std::shared_ptr<SummaryInformation> *output) {
    if (!parser_) {
        return FRError::NoParser;
    }
    
    std::shared_ptr<DJIFR::standardization::SummaryInformation> summary_cpp = nullptr;
    auto error_code_cpp = parser_->summaryInformation(&summary_cpp);
    
    if (error_code_cpp != DJIFR::standardization::SDKError::Success) {
        return (FRError)error_code_cpp;
    }
    
    auto summary = std::make_shared<SummaryInformation>();
    summary->set_platform((SummaryInformation_Platform)summary_cpp->platform());
    
    auto app_version_cpp_arr = summary_cpp->appVersion();
    for (auto iter = app_version_cpp_arr.begin(); iter != app_version_cpp_arr.end(); iter ++) {
        summary->add_appversion((*iter));
    }
    
    auto batteriesInformation_cpp = summary_cpp->batteriesInformation();
    if (batteriesInformation_cpp.size() > 0) {
        auto batteriesInformation_mutable = summary->mutable_batteriesinformation();
        for (auto iter = batteriesInformation_cpp.begin(); iter != batteriesInformation_cpp.end(); iter ++) {
            auto component_information = ConvertToComponentInformation((*iter).second);
            (*batteriesInformation_mutable)[(*iter).first] = component_information;
        }
    }
    
    auto camera_information_cpp = summary_cpp->camerasInformation();
    if (camera_information_cpp.size() > 0) {
        auto camera_information_mutable = summary->mutable_camerasinformation();
        for (auto iter = camera_information_cpp.begin(); iter != camera_information_cpp.end(); iter ++) {
            auto component_information = ConvertToComponentInformation((*iter).second);
            (*camera_information_mutable)[(*iter).first] = component_information;
        }
    }
    
    auto gimbal_information_cpp = summary_cpp->gimbalsInformation();
    if (gimbal_information_cpp.size() > 0) {
        auto gimbal_information_mutable = summary->mutable_gimbalsinformation();
        for (auto iter = gimbal_information_cpp.begin(); iter != gimbal_information_cpp.end(); iter ++) {
            auto component_information = ConvertToComponentInformation((*iter).second);
            (*gimbal_information_mutable)[(*iter).first] = component_information;
        }
    }
    
    if (summary_cpp->remoteControllerInformation()) {
        auto remote_controller_information = ConvertToComponentInformation(summary_cpp->remoteControllerInformation());
        (*summary->mutable_remotecontrollerinformation()) = remote_controller_information;
    }
    
    if (summary_cpp->flightControllerInformation()) {
        auto flight_controller_information = ConvertToComponentInformation(summary_cpp->flightControllerInformation());
        (*summary->mutable_flightcontrollerinformation()) = flight_controller_information;
    }
    
    summary->set_aircraftname(summary_cpp->aircraftName());
    summary->set_starttime(summary_cpp->startTime());
    
    if (summary_cpp->startCoordinate()) {
        auto start_coordinate = ConvertToLocationCoordinate(summary_cpp->startCoordinate());
        (*summary->mutable_startcoordinate()) = start_coordinate;
    }
    
    summary->set_totaldistance(summary_cpp->totalDistance());
    summary->set_totaltime(summary_cpp->totalTime());
    summary->set_samplingrate(summary_cpp->samplingRate());
    summary->set_maxheight(summary_cpp->maxHeight());
    summary->set_maxhorizontalspeed(summary_cpp->maxHorizontalSpeed());
    summary->set_maxvirticalspeed(summary_cpp->maxVirticalSpeed());
    summary->set_uuid(summary_cpp->uuid());
    summary->set_producttype((SDK_ProductType)summary_cpp->product_type());
    
    (*output) = summary;
    
    return FRError::Success;
}

FRError Parser::images(std::shared_ptr<ImageDatas> *output) {
    if (!parser_) {
        return FRError::NoParser;
    }
    
    std::vector<DJIFR::standardization::ImageDataSharedPtr> images_cpp;
    auto error_code_cpp = parser_->images(&images_cpp);
    if (error_code_cpp != DJIFR::standardization::SDKError::Success) {
        return (FRError)error_code_cpp;
    }
    
    auto images = std::make_shared<ImageDatas>();
    
    for (auto iter = images_cpp.begin(); iter != images_cpp.end(); iter ++) {
        ConvertToImageData(images->add_images(), (*iter));
    }
    
    (*output) = images;
    
    return FRError::Success;
}

FRError Parser::frame_time_states(std::shared_ptr<FrameTimeStates> *output) {
    if (!parser_) {
        return FRError::NoParser;
    }
    
    std::vector<DJIFR::standardization::ServerFrameTimeStateSharedPtr> frame_time_list_cpp;
    auto error_code_cpp = parser_->server_frame_time_list(&frame_time_list_cpp);
    if (error_code_cpp != DJIFR::standardization::SDKError::Success) {
        return (FRError)error_code_cpp;
    }
    
    auto frame_time_states = std::make_shared<FrameTimeStates>();
    for (auto iter = frame_time_list_cpp.begin(); iter != frame_time_list_cpp.end(); iter ++) {
        ConvertToFrameTimeState((*iter), frame_time_states->add_frametimestates());
    }
    
    (*output) = frame_time_states;
    
    return FRError::Success;
}

FRError Parser::filterFrameTimeList(std::map<FlightRecordDataType, bool> filter) {
    if (!parser_) {
        return FRError::NoParser;
    }
    
    return (FRError)parser_->filterFrameTimeList(filter);
}
