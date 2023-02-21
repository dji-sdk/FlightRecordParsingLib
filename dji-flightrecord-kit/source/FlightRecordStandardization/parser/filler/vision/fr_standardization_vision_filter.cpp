//
//  fr_standardization_vision_filter.cpp
//  FlightRecordStandardization
//
//

#include "fr_standardization_vision_filter.hpp"
#include <model/protocol/fr_protocol.h>
#include <string.h>

using namespace DJIFR::standardization;
using namespace DJI::FlightRecord;

static void FillRadar(std::shared_ptr<VisionDetectionStateImp> output, dji_vision_push_front_detetion_push *internalData) {
    switch (output->position()) {
        case VisionSensorPosition::Nose:
        case VisionSensorPosition::Tail:
        {
            output->detectionSectors().clear();
            int failCount = 0;
            for (int i = 0; i < internalData->detection_count; i ++) {
                auto obstacle = std::make_shared<ObstacleDetectionSectorImp>();
                auto distanceInMeters = internalData->detect_distance[i].detect_distance_CM * 0.01;
                if (distanceInMeters > 15) {
                    failCount ++;
                }
                
                obstacle->set_obstacleDistanceInMeters(distanceInMeters);
                obstacle->set_warningLevel((ObstacleDetectionSectorWarning)internalData->detect_distance[i].warning_level);
                output->detectionSectors().push_back(obstacle);
            }
            
            if (failCount == internalData->detection_count) {
                output->detectionSectors().clear();
                output->set_isSensorBeingUsed(false);
                output->set_systemWarning(VisionSystemWarning::Invalid);
                output->set_obstacleDistanceInMeters(0);
            }
        }
            break;
            
        default:
        {
            output->set_obstacleDistanceInMeters(internalData->detect_distance[0].detect_distance_CM / 100.0);
            
            if (output->obstacleDistanceInMeters() > 10.0) {
                output->set_isSensorBeingUsed(false);
                output->set_systemWarning(VisionSystemWarning::Invalid);
                output->set_obstacleDistanceInMeters(0);
            }
        }
            break;
    }
}

static bool isValidDetectionData(bool visionWorkFlag,
                                 bool availableFlag,
                                 uint8_t rawWarningLevel) {
    if (visionWorkFlag == false ||
        availableFlag == false) {
        return false;
    } else if (rawWarningLevel > 5) {
        return false;
    }
    
    return true;
}

static void FillGuidanceData(std::shared_ptr<VisionStateImp> output, dji_vision_push_guidance_detetion_push *internalData) {
    auto detectionStateMap = output->detectionStateMap();
    for (auto iter = detectionStateMap.begin(); iter != detectionStateMap.end(); iter ++) {
        auto detectionState = (*iter).second;
        
        bool availableFlag = false;
        uint8_t rawWarningLevel = 10;
        switch (detectionState->position()) {
            case DJIFR::standardization::VisionSensorPosition::Nose:
            {
                availableFlag = internalData->visionFlag.front_detect_available_flag;
                rawWarningLevel = internalData->front_detect.warning_level;
            }
                break;
            case DJIFR::standardization::VisionSensorPosition::Tail:
            {
                availableFlag = internalData->visionFlag.back_detect_available_flag;
                rawWarningLevel = internalData->back_detect.warning_level;
            }
                break;
            case DJIFR::standardization::VisionSensorPosition::Right:
            {
                availableFlag = internalData->visionFlag.right_detect_available_flag;
                rawWarningLevel = internalData->back_detect.warning_level;
            }
                break;
            case DJIFR::standardization::VisionSensorPosition::Left:
            {
                availableFlag = internalData->visionFlag.left_detect_available_flag;
                rawWarningLevel = internalData->left_detect.warning_level;
            }
                break;
                
            default:
                break;
        }
        
        if (isValidDetectionData(internalData->visionFlag.vision_work_flag, availableFlag, rawWarningLevel) == false) {
            detectionState->set_isSensorBeingUsed(false);
            detectionState->set_systemWarning(VisionSystemWarning::Invalid);
            detectionState->set_obstacleDistanceInMeters(0);
            detectionState->detectionSectors().clear();
        } else {
            VisionSystemWarning warning = VisionSystemWarning::Invalid;
            switch (rawWarningLevel) {
                case 0:
                case 1:
                case 2:
                    warning = VisionSystemWarning::Safe;
                    break;
                case 3:
                    warning = VisionSystemWarning::Dangerous;
                    break;
                    
                default:
                    break;
            }
            
            detectionState->set_systemWarning(warning);
            detectionState->set_isSensorBeingUsed(true);
        }
    }
    
    if (output->controlState() == nullptr) {
        auto controlState = std::make_shared<VisionControlStateImp>();
        output->set_controlState(controlState);
    }
    
    auto controlState = output->controlStateImp();
    controlState->set_isBraking(internalData->visionFlag.brake_flag);
}

static void FillMCAvoidStatus(std::shared_ptr<VisionStateImp> output,
                              dji_fc_avoid_status_push *internalData) {
    if (output->controlState() == nullptr) {
        auto controlState = std::make_shared<VisionControlStateImp>();
        output->set_controlState(controlState);
    }
    
    auto controlState = output->controlStateImp();
    controlState->set_isAscentLimitedByObstacle(internalData->roof_limit_work_flag);
    controlState->set_isAvoidingActiveObstacleCollision(internalData->is_avoid_overshoot_act);
    output->set_collisionAvoidanceEnabled(internalData->user_avoid_enable);
}

static void FillWarningStatus(std::shared_ptr<VisionStateImp> output,
                              DJITomatoVisionCommonWarningStatusData *internalData) {
    if (output->controlState() == nullptr) {
        auto controlState = std::make_shared<VisionControlStateImp>();
        output->set_controlState(controlState);
    }
    
    auto controlState = output->controlStateImp();
    
    auto visionStatus = internalData->aircraftVisionStatus;
    auto landingState = internalData->missionStatus.smartGoHomeStatus.landingState;
    controlState->set_isPerformingPrecisionLanding(visionStatus.is_landing && (landingState.landingCorrecting || landingState.landingExecuting));
}

bool DJIFR::standardization::Filler(std::shared_ptr<VisionStateImp>& output,
                                    FlightRecordDataType data_type,
                                    uint8_t *buffer,
                                    uint64_t length) {
    switch (data_type) {
        case VisionGroupDataType:
        {
            if (buffer == nullptr || length <= 2) {
                return false;
            }
            
            // using to get the buffer data;
            auto readBlockBody = [](void *readBuffer, long readBufferLength, void *dstPtr, long dstSize, long *needOffset) -> bool {
                long needOffsetValue = *needOffset;
                if (needOffsetValue + dstSize >= readBufferLength) {
                    return false;
                }
                
                uint8_t *dstPtrSrc = (uint8_t *)readBuffer + needOffsetValue;
                memcpy(dstPtr, dstPtrSrc, dstSize);
                needOffsetValue += dstSize;
                
                if (needOffsetValue + 1 > readBufferLength) {
                    return false;
                }
                
                uint8_t endFlag;
                uint8_t *endFlagSrc = (uint8_t *)readBuffer + needOffsetValue;
                memcpy(&endFlag, endFlagSrc, sizeof(endFlag));
                needOffsetValue += sizeof(endFlag);
                
                if (endFlag != VisionGroupDataType_End) {
                    return false;
                }
                
                *needOffset = needOffsetValue;
                
                return true;
            };
            
            // using to get the block type, block size
            auto readBlockHeader = [](void *readBuffer, long readBufferLength, long *needOffset, FlightRecordVisionGroupDataType *blockType, uint8_t *blockSize) -> bool {
                long needOffsetValue = *needOffset;
                if (needOffsetValue + sizeof(FlightRecordVisionGroupDataType) + sizeof(uint8_t) >= readBufferLength) {
                    return false;
                }
                
                uint8_t *blockTypeSrc = (uint8_t *)readBuffer + needOffsetValue;
                memcpy(blockType, blockTypeSrc, sizeof(FlightRecordVisionGroupDataType));
                needOffsetValue += sizeof(FlightRecordVisionGroupDataType);
                
                uint8_t *blockSizeSrc = (uint8_t *)readBuffer + needOffsetValue;
                memcpy(blockSize, blockSizeSrc, sizeof(uint8_t));
                needOffsetValue += sizeof(uint8_t);
                
                *needOffset = needOffsetValue;
                
                return true;
            };
            
            auto readBlockOneByOne = [readBlockBody, readBlockHeader](void *allBlockBuffer, long allBlockLength, std::shared_ptr<VisionStateImp>& output, long *needOffset) -> bool {
                FlightRecordVisionGroupDataType dataType;
                uint8_t dataSize;
                if (!readBlockHeader(allBlockBuffer, allBlockLength, needOffset, &dataType, &dataSize)) {
                    return false;
                }
                
                switch (dataType) {
                    case VisionGroupDataType_VisionDetectionRadarFront:
                    case VisionGroupDataType_VisionDetectionRadarBack:
                    case VisionGroupDataType_VisionDetectionRadarRight:
                    case VisionGroupDataType_VisionDetectionRadarLeft:
                    case VisionGroupDataType_VisionDetectionRadarDown:
                    {
                        if (dataSize < sizeof(dji_vision_push_front_detetion_push)) {
                            return false;
                        }
                        
                        dji_vision_push_front_detetion_push *internalData = nullptr;
                        bool result = true;
                        
                        do {
                            internalData = (dji_vision_push_front_detetion_push *)malloc(dataSize);
                            if (!readBlockBody(allBlockBuffer, allBlockLength, internalData, dataSize, needOffset)) {
                                result = false;
                                break;
                            }
                            
                            // can fill the vision data.
                            auto find_iter = output->detectionStateMap().find((VisionSensorPosition)dataType);
                            std::shared_ptr<VisionDetectionStateImp> detectionState = nullptr;
                            if (find_iter == output->detectionStateMap().end()) {
                                detectionState = std::make_shared<VisionDetectionStateImp>();
                                output->detectionStateMap()[(VisionSensorPosition)dataType] = detectionState;
                            } else {
                                detectionState = (*find_iter).second;
                            }
                            
                            detectionState->set_position((VisionSensorPosition)internalData->sensor_direction);
                            FillRadar(detectionState, internalData);
                        } while (0);
                        
                        if (internalData) {
                            free(internalData);
                        }
                        
                        if (!result) {
                            return result;
                        }
                    }
                        break;
                    case VisionGroupDataType_MCAvoidStatus:
                    {
                        if (dataSize < sizeof(dji_fc_avoid_status_push)) {
                            return false;
                        }
                        
                        dji_fc_avoid_status_push *internalData = nullptr;
                        bool result = true;
                        
                        do {
                            internalData = (dji_fc_avoid_status_push *)malloc(dataSize);
                            if (!readBlockBody(allBlockBuffer, allBlockLength, internalData, dataSize, needOffset)) {
                                result = false;
                                break;
                            }
                            
                            // can fill the mc avoid status data.
                            FillMCAvoidStatus(output, internalData);
                        } while (0);
                        
                        if (internalData) {
                            free(internalData);
                        }
                        
                        if (!result) {
                            return result;
                        }
                    }
                        break;
                    case VisionGroupDataType_GuidanceDetect:
                    {
                        if (dataSize < sizeof(dji_vision_push_guidance_detetion_push)) {
                            return false;
                        }
                        
                        dji_vision_push_guidance_detetion_push *internalData = nullptr;
                        bool result = true;
                        
                        do {
                            internalData = (dji_vision_push_guidance_detetion_push *)malloc(dataSize);
                            if (!readBlockBody(allBlockBuffer, allBlockLength, internalData, dataSize, needOffset)) {
                                result = false;
                                break;
                            }
                            
                            // can fill guidance detect.
                            FillGuidanceData(output, internalData);
                        } while (0);
                        
                        if (internalData) {
                            free(internalData);
                        }
                        
                        if (!result) {
                            return result;
                        }
                    }
                        break;
                    case VisionGroupDataType_WarningStatus:
                    {
                        if (dataSize < sizeof(DJITomatoVisionCommonWarningStatusData)) {
                            return false;
                        }
                        
                        DJITomatoVisionCommonWarningStatusData *internalData = nullptr;
                        bool result = true;
                        
                        do {
                            internalData = (DJITomatoVisionCommonWarningStatusData *)malloc(dataSize);
                            if (!readBlockBody(allBlockBuffer, allBlockLength, internalData, dataSize, needOffset)) {
                                result = false;
                                break;
                            }
                            
                            // can fill warning status.
                            FillWarningStatus(output, internalData);
                        } while (0);
                        
                        if (internalData) {
                            free(internalData);
                        }
                        
                        if (!result) {
                            return result;
                        }
                    }
                        break;
                        
                    default:
                        return false;
                }
                
                return true;
            };
            
            bool onceReadSuccess = false;
            long offset = 0;
            
            while (readBlockOneByOne(buffer, length, output, &offset)) {
                onceReadSuccess = true;
                if (offset >= length) {
                    break;
                }
            }
            
            return true;
        }
            break;
            
        default:
            break;
    }
    
    return true;
}
