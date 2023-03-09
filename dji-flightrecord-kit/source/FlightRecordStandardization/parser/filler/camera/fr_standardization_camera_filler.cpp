//
//  fr_standardization_camera_filler.cpp
//  FlightRecordStandardization
//
//  Copyright © 2019 DJISDK. All rights reserved.
//

#include "fr_standardization_camera_filler.hpp"
#include <model/protocol/fr_protocol.h>
#include <string.h>

using namespace DJIFR::standardization;

//MARK: - CameraInfoFlightRecordDataType

static CameraMode ConvertToPublicCameraMode(DJI_CAMERA_WORKING_MODE work_mode) {
    switch (work_mode) {
        case DJI_CAMERA_WORKING_MODE_PLAYBACK:
            return CameraMode::Playback;
        case DJI_CAMERA_WORKING_MODE_CAPTURE:
            return CameraMode::ShootPhoto;
        case DJI_CAMERA_WORKING_MODE_RECORDING:
            return CameraMode::RecordVideo;
        case DJI_CAMERA_WORKING_MODE_DOWNLOAD:
            return CameraMode::Playback;
        case DJI_CAMERA_WORKING_MODE_XCODE_PLAYBACK:
            return CameraMode::MediaDownload;
        case DJI_CAMERA_WORKING_MODE_BROADCAST:
            return CameraMode::Broadcast;
            
        default:
            break;
    }
    
    return CameraMode::Unknown;
}

static bool FillCameraInfo(const DJIFlightRecordCameraStatusInfoCollectStruct& data_source,
                           std::shared_ptr<CameraStateImp>& output) {
    output->set_isRecording(data_source.isVideoRecording != 0);
    output->set_isShootingSinglePhoto(data_source.captureState == 1);
    output->set_isInserted(data_source.hasSDCard);
    output->set_isInitializing(data_source.SDCardState == DJI_CAMERA_SDCARD_STATUS_INVALID_CARD);
    output->set_hasError((data_source.SDCardState == DJI_CAMERA_SDCARD_STATUS_INVALID_CARD || data_source.SDCardState == DJI_CAMERA_SDCARD_STATUS_ILLEGAL_FILE_SYS || data_source.SDCardState == DJI_CAMERA_SDCARD_STATUS_UNKOWN_ERROR));
    output->set_isVerified(data_source.SDCardState != DJI_CAMERA_SDCARD_STATUS_INVALID_CARD);
    output->set_isFull(data_source.SDCardState != DJI_CAMERA_SDCARD_STATUS_CARD_FULL);
    output->set_isFormatted(data_source.SDCardState != DJI_CAMERA_SDCARD_STATUS_UNFORMATTED);
    output->set_isFormatting(data_source.SDCardState == DJI_CAMERA_SDCARD_STATUS_FORMATING);
    output->set_isInvalidFormat(data_source.SDCardState == DJI_CAMERA_SDCARD_STATUS_ILLEGAL_FILE_SYS);
    output->set_isReadOnly(data_source.SDCardState == DJI_CAMERA_SDCARD_STATUS_W_POROTECTED);
    output->set_totalSpaceInMB(data_source.sdCardTotalCapacity);
    output->set_remainingSpaceInMB(data_source.sdCardRemainCapacity);
    output->set_availableCaptureCount(data_source.remainPhotoNum);
    output->set_availableRecordingTimeInSeconds(data_source.remainVideoTimer);
    
    bool isPlaybackSupported = false;
    switch ((DJI_CAMERA_TYPE)data_source.cameraType) {
        case DJI_CAMERA_TYPE_Phantom4:
        case DJI_CAMERA_TYPE_Insipre1:
        case DJI_CAMERA_TYPE_Insipre1Pro:
            isPlaybackSupported = true;
            break;
            
        default:
            break;
    }
    
    CameraMode camera_mode = ConvertToPublicCameraMode((DJI_CAMERA_WORKING_MODE)data_source.workMode);
    if (isPlaybackSupported == false &&
        camera_mode == CameraMode::Playback) {
        camera_mode = CameraMode::MediaDownload;
    }
    output->set_mode(camera_mode);
    
    return true;
}

//MARK: - Public

bool DJIFR::standardization::Filler(std::shared_ptr<CameraStateImp>& output,
                                    FlightRecordDataType data_type,
                                    uint8_t *buffer,
                                    uint64_t length) {
    switch (data_type) {
        case CameraInfoFlightRecordDataType:
        {
            DJIFlightRecordCameraStatusInfoCollectStruct data_source = {0};
            uint64_t data_length = std::min(length, (uint64_t)sizeof(data_source));
            if (data_length <= 0) {
                return false;
            }
            
            memcpy(&data_source, buffer, data_length);
            return FillCameraInfo(data_source, output);
        }
            break;
            
        default:
            break;
    }
    
    return false;
}
