//
//  fr_standardization_parser_Imp.cpp
//  FlightRecordStandardization
//
//  Copyright © 2019 DJISDK. All rights reserved.
//

#include "fr_standardization_parser_Imp.hpp"
#include <memory>
#include <iostream>
#include <string>
#include <Utils/string/flight_record_utf8.hpp>
#include "fr_standardization_filler_set.h"
#include "fr_standardization_frametime_model.hpp"
#include "fr_standardization_summary_model.hpp"
#include "fr_standardization_image_model.hpp"
#include <Parser/decoder/flight_record_version_decoder_set.h>
#include <Parser/decryption/flight_record_decryption_layer_set.h>
#include <assert.h>
#include <string.h>
#include <Parser/decryption/flight_record_decryption_layer_set.h>
#include <Utils/math/FlightRecordMaths.h>
#include <model/keychain/FlightRecordKeychainModel.h>
#include "fr_standardization_utils.h"
#include <Utils/keychain/flight_record_decrypt_keychain.h>
#include "fr_standardization_utils_private.h"
#include <math.h>
#include <model/protocol/fr_protocol.h>
#include <Utils/encryption/rsa/flight_record_rsa_tool.hpp>
#include <model/protocol/dji_product_type.h>
#include "json11.hpp"
#include "CLHttpRequest.h"
#include <tomcrypt.h>
#include <ctime>
#include <chrono>
#include <sstream>
#include <iomanip>

using namespace DJIFR::standardization;
using namespace DJI::FlightRecord;

void toHex(void *const data,           //!< Data to convert
           const size_t dataLength,    //!< Length of the data to convert
           std::string &dest)          //!< Destination string
{
    unsigned char     *byteData = reinterpret_cast<unsigned char*>(data);
    std::stringstream hexStringStream;
    
    hexStringStream << std::hex << std::setfill('0');
    for(size_t index = 0; index < dataLength; ++index)
        hexStringStream << std::setw(2) << static_cast<int>(byteData[index]);
    dest = hexStringStream.str();
}

ParserImp::ParserImp() :
parser_(nullptr),
summary_info_(nullptr),
product_type_(ProductType::None) {
    
}

ParserImp::~ParserImp() {
    
}

//MARK: - Public

SDKError ParserImp::load(const std::string& file_path) {
    parser_ = std::make_shared<FlightRecordParserEngine>();
    
    auto set_file_result_code = parser_->SetFilePath(file_path);
    if (set_file_result_code != ParserResult::Success) {
        return convertParserResultToPublic(set_file_result_code);
    }
    
    Version13Decoder decoder13;
    parser_->AddVersionDecoder(decoder13);
    
    Version13V2Decoder decoder13V2;
    parser_->AddVersionDecoder(decoder13V2);
    
    DecryptionLayerPtr decryption13 = std::make_shared<Decryption13Layer>();
    auto error = parser_->addDecryptionLayer(decryption13);
    assert(error == ParserResult::Success);
    
    DecryptionLayerPtr decryption13V2 = std::make_shared<Decryption13V2Layer>();
    error = parser_->addDecryptionLayer(decryption13V2);
    assert(error == ParserResult::Success);

    return SDKError::Success;
}

SDKError ParserImp::startRequestParser(const std::string& sdk_key, const RequestCallback &callback) {
    if (!parser_) {
        assert(false && "please call the `load` method first");
        return SDKError::NoParser;
    }
    
    std::vector<std::map<FeaturePoint, DJI::FlightRecord::BufferPtr>> all_keychains;
    int file_index = 0;
    auto parser_block = [this, &all_keychains, &file_index] (FlightRecordParserEngine *engine, FlightRecordDataType data_type, int index, uint8_t *buffer, uint64_t length, bool *stop) {
        switch (data_type) {
            case KeyStorage:
            {
                for (auto index = all_keychains.size(); index < file_index + 1; index ++) {
                    all_keychains.push_back(std::map<FeaturePoint, BufferPtr>());
                }
                
                FlightRecordKeyChainInDetail *keychain_detail = (FlightRecordKeyChainInDetail *)buffer;
                if (keychain_detail->featurePoint == DJI::FlightRecord::FeaturePoint::AgricultureFeature) {
                    break;
                }
                
                auto aes_ciphertext = std::make_shared<DJI::FlightRecord::Buffer>((void *)keychain_detail->aes_key_ciphertext.data, keychain_detail->aes_key_ciphertext.data_length);
                all_keychains[file_index][keychain_detail->featurePoint] = aes_ciphertext;
            }
                break;
            case FlightRecordRecover:
            {
                file_index ++;
            }
                break;
                
            default:
                break;
        }
    };
    
    std::map<FeaturePoint, std::string> featurePointStrMap = {
        { FeaturePoint::BaseFeature, "FR_Standardization_Feature_Base_1" },
        { FeaturePoint::VisionFeature, "FR_Standardization_Feature_Vision_2" },
        { FeaturePoint::WaypointFeature, "FR_Standardization_Feature_Waypoint_3" },
        { FeaturePoint::AgricultureFeature, "FR_Standardization_Feature_Agriculture_4" },
        { FeaturePoint::AirLinkFeature, "FR_Standardization_Feature_AirLink_5" },
        { FeaturePoint::AfterSalesFeature, "FR_Standardization_Feature_AfterSales_6" },
        { FeaturePoint::DJIFlyCustomFeature, "FR_Standardization_Feature_DJIFlyCustom_7" },
        { FeaturePoint::FlightHubFeature, "FR_Standardization_Feature_FlightHub_9" },
        { FeaturePoint::GimbalFeature, "FR_Standardization_Feature_Gimbal_10" },
        { FeaturePoint::RCFeature, "FR_Standardization_Feature_RC_11" },
        { FeaturePoint::CameraFeature, "FR_Standardization_Feature_Camera_12" },
        { FeaturePoint::BatteryFeature, "FR_Standardization_Feature_Battery_13" },
        { FeaturePoint::FlySafeFeature, "FR_Standardization_Feature_FlySafe_14" },
    };
    
    std::map<std::string, FeaturePoint> featurePointMap = {
        { "FR_Standardization_Feature_Base_1", FeaturePoint::BaseFeature },
        { "FR_Standardization_Feature_Vision_2", FeaturePoint::VisionFeature },
        { "FR_Standardization_Feature_Waypoint_3", FeaturePoint::WaypointFeature },
        { "FR_Standardization_Feature_Agriculture_4", FeaturePoint::AgricultureFeature },
        { "FR_Standardization_Feature_AirLink_5", FeaturePoint::AirLinkFeature },
        { "FR_Standardization_Feature_AfterSales_6", FeaturePoint::AfterSalesFeature },
        { "FR_Standardization_Feature_DJIFlyCustom_7", FeaturePoint::DJIFlyCustomFeature },
        { "FR_Standardization_Feature_FlightHub_9", FeaturePoint::FlightHubFeature },
        { "FR_Standardization_Feature_Gimbal_10", FeaturePoint::GimbalFeature },
        { "FR_Standardization_Feature_RC_11", FeaturePoint::RCFeature },
        { "FR_Standardization_Feature_Camera_12", FeaturePoint::CameraFeature },
        { "FR_Standardization_Feature_Battery_13", FeaturePoint::BatteryFeature },
        { "FR_Standardization_Feature_FlySafe_14", FeaturePoint::FlySafeFeature }
    };
    
    auto error = parser_->parseDetailData(parser_block);
    
    {
        DJI::FlightRecord::VersionExtension version_extension;
        parser_->obtainVersionExtension(version_extension);
        
        auto keychains_Arr = json11::Json::array{};
        for (auto i = 0; i < all_keychains.size(); i ++) {
            auto files_map = all_keychains.at(i);
            std::vector<json11::Json> keychains;
            for (auto ciphertext_iter = files_map.begin(); ciphertext_iter != files_map.end(); ciphertext_iter ++) {
                auto feature_point_str_iter = featurePointStrMap.find((*ciphertext_iter).first);
                if (feature_point_str_iter == featurePointStrMap.end()) {
                    continue;
                }
                
                auto ciphertext = (*ciphertext_iter).second;
                unsigned char base64_str_buf[ciphertext->buffer_length_ * 2];
                unsigned long base64_len = ciphertext->buffer_length_ * 2;
                memset(base64_str_buf, 0, base64_len);
                base64_encode((unsigned char *)ciphertext->buffer_pointer_, ciphertext->buffer_length_, base64_str_buf, &base64_len);
                std::string base64_str((char *)base64_str_buf, base64_len);
                
                auto feature_point_str = (*feature_point_str_iter).second;
                auto item = json11::Json::object {
                    { "featurePoint", feature_point_str },
                    { "aesCiphertext", base64_str }
                };
                
                keychains.push_back(item);
            }
            
            keychains_Arr.push_back(keychains);
        }
        
        auto keychains_map = json11::Json::object {
            { "department", (int)version_extension.department },
            { "version", (int)version_extension.version },
            { "keychainsArray", keychains_Arr }
        };
        
        std::string request_json;
        json11::Json(keychains_map).dump(request_json);
        
        auto body = json11::Json::array();
        body.push_back(json11::Json::object {
            {"version", (int)version_extension.version},
            {"sdk_key", sdk_key},
            {"type", "StartParser"},
        });
        
        std::string appKey("VnvGg8ApqcbyFrc");
        std::string bodyStr;
        json11::Json(body).dump(bodyStr);
        
        int md5Idex, err;
        hmac_state hmac;
        unsigned char key[16];
        char dst[16];
        unsigned long dstlen;
        memcpy(key, appKey.c_str(), appKey.length());
        
        if (register_hash(&md5_desc) == -1) {
            return SDKError::Failure;
        }
        
        md5Idex = find_hash("md5");
        
        if ((err = hmac_init(&hmac, md5Idex, key, appKey.length())) != CRYPT_OK) {
            return SDKError::Failure;
        }
        
        if ((err = hmac_process(&hmac, (unsigned char *)bodyStr.c_str(), bodyStr.length())) != CRYPT_OK) {
            return SDKError::Failure;
        }
        
        if ((err = hmac_done(&hmac, (unsigned char *)dst, &dstlen)) != CRYPT_OK) {
            return SDKError::Failure;
        }
        
        std::string sign_str;
        toHex(dst, dstlen, sign_str);
        
        dji::core::CLHttpRequest *request = dji::core::CLHttpRequest::Post("https://statistical-report.djiservice.org/api/report/web", (char *)bodyStr.c_str(), bodyStr.length());
        request->SetTimeout(30);
        request->SetRequestHeader("Accept", "application/json");
        request->SetRequestHeader("appid", "572918");
        request->SetRequestHeader("sign", sign_str);
        request->SetRequestHeader("Content-Type", "application/json;charset=UTF-8");
        
        request->SendRequest([this, request_json, sdk_key, callback, featurePointMap, version_extension](dji::core::CLHttpRequest *request, bool succeeded) {
            dji::core::CLHttpRequest *httpReq = dji::core::CLHttpRequest::Post("https://dev.dji.com/openapi/v1/flight-records/keychains", (char *)request_json.c_str(), request_json.length());
            httpReq->SetTimeout(30);
            httpReq->SetRequestHeader("Accept", "application/json");
            httpReq->SetRequestHeader("Api-Key", sdk_key);
            uint64_t now = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
            httpReq->SendRequest([this, callback, featurePointMap, &now, version_extension](dji::core::CLHttpRequest *request, bool succeeded) {
                uint64_t current = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
                if (callback == NULL) {
                    delete request;
                    return;
                }
                
                if (!succeeded) {
                    callback(ServerError::NetworkIsNotReachable, "");
                    delete request;
                    return;
                }
                
                std::string error;
                auto json = json11::Json::parse((char *)request->GetResponseData(), error);
                if (error.length() > 0) {
                    callback(ServerError::ParserFailure, error);
                    delete request;
                    return;
                }
                
                auto result = json["result"];
                switch (request->GetResponseCode()) {
                    case 200:
                    {
                        auto keychainsArray = json["data"];
                        auto keychains_arr_json = keychainsArray.array_items();
                        std::vector<std::map<FeaturePoint, DJI::FlightRecord::AESKeychainPtr>> plaintext_all_aes_key;
                        for (auto i = 0; i < keychains_arr_json.size(); i ++) {
                            auto keychains_json = keychains_arr_json.at(i).array_items();
                            std::map<FeaturePoint, DJI::FlightRecord::AESKeychainPtr> all_aes_key;
                            for (auto j = 0; j < keychains_json.size(); j ++) {
                                auto keychain_json = keychains_json.at(j).object_items();
                                auto featurePoint_iter = featurePointMap.find(keychain_json["featurePoint"].string_value());
                                if (featurePoint_iter == featurePointMap.end()) {
                                    callback(ServerError::ParserFailure, "");
                                    delete request;
                                    return;
                                }
                                auto feature_point = (*featurePoint_iter).second;
                                
                                auto aes_key_json = keychain_json["aesKey"].string_value();
                                char aes_key_buf[256];
                                unsigned long aes_key_buf_len = 256;
                                base64_decode((unsigned char *)aes_key_json.c_str(), aes_key_json.length(), (unsigned char *)aes_key_buf, &aes_key_buf_len);
                                auto aes_key = std::make_shared<DJI::FlightRecord::Buffer>((void *)aes_key_buf, aes_key_buf_len);
                                
                                auto aes_iv_json = keychain_json["aesIv"].string_value();
                                char aes_iv_buf[32];
                                unsigned long aes_iv_buf_len = 32;
                                base64_decode((unsigned char *)aes_iv_json.c_str(), aes_iv_json.length(), (unsigned char *)aes_iv_buf, &aes_iv_buf_len);
                                auto aes_iv = std::make_shared<DJI::FlightRecord::Buffer>((void *)aes_iv_buf, aes_iv_buf_len);
                                
                                auto aes_keychain = std::make_shared<DJI::FlightRecord::AESKeychain>(aes_key, aes_iv);
                                all_aes_key[feature_point] = aes_keychain;
                            }
                            
                            plaintext_all_aes_key.push_back(all_aes_key);
                        }
                        
                        switch (version_extension.version) {
                            case DJI::FlightRecord::VersionCategory::Version13_1:
                            {
                                DecryptionLayerPtr decryption = std::make_shared<Decryption13Layer>(plaintext_all_aes_key);
                                parser_->addDecryptionLayer(decryption);
                            }
                                break;
                            case DJI::FlightRecord::VersionCategory::Version13_2:
                            {
                                DecryptionLayerPtr decryption = std::make_shared<Decryption13V2Layer>(plaintext_all_aes_key);
                                parser_->addDecryptionLayer(decryption);
                            }
                                break;
                                
                            default:
                                break;
                        }
                        
                        
                        callback(ServerError::Success, result["msg"].string_value());
                    }
                        break;
                    case 400:
                    {
                        if (callback) {
                            callback(ServerError::InvaidParameter, result["msg"].string_value());
                        }
                        delete request;
                        return;
                    }
                        break;
                    case 403:
                    {
                        if (callback) {
                            callback(ServerError::NotPermission, result["msg"].string_value());
                        }
                        delete request;
                        return;
                    }
                        break;
                        
                    default:
                        break;
                }
            });
        });
    }
    
    return convertParserResultToPublic(error);
}

SDKError ParserImp::summaryInformation(SummaryInformationSharedPtr* output) {
    if (!summary_info_) {
        parserSummary();
    }
    
    if (!is_recalculate_info_) {
        if (frame_time_list_.size() <= 0) {
            std::map<FlightRecordDataType, bool> filter;
            auto frame_time_result = filterFrameTimeList(filter);
            if (frame_time_result != SDKError::Success) {
                return frame_time_result;
            } else {
                recalculateSummary();
                is_recalculate_info_ = true;
            }
        } else {
            recalculateSummary();
            is_recalculate_info_ = true;
        }
    }
    
    *output = summary_info_;
    
    return SDKError::Success;
}

SDKError ParserImp::images(std::vector<ImageDataSharedPtr>* output) {
    auto image_result = parserImageData();
    if (image_result == SDKError::Success) {
        std::vector<ImageDataSharedPtr> images;
        for (auto item = images_.begin(); item != images_.end(); item ++) {
            images.push_back(*item);
        }
        
        *output = images;
    }
    
    return image_result;
}

SDKError ParserImp::frame_time_list(std::vector<FrameTimeStateSharedPtr>* output) {
    auto frame_time_result = SDKError::Success;
    
    if (frame_time_list_.size() <= 0) {
        std::map<FlightRecordDataType, bool> filter;
        frame_time_result = filterFrameTimeList(filter);
    }
    
    if (frame_time_result == SDKError::Success) {
        std::vector<FrameTimeStateSharedPtr> frame_time_list;
        for (auto item = frame_time_list_.begin(); item != frame_time_list_.end(); item ++) {
            frame_time_list.push_back(*item);
        }
        
        *output = frame_time_list;
    }
    
    return frame_time_result;
}

SDKError ParserImp::server_frame_time_list(std::vector<ServerFrameTimeStateSharedPtr>* output) {
    auto frame_time_result = SDKError::Success;
    
    if (frame_time_list_.size() <= 0) {
        std::map<FlightRecordDataType, bool> filter;
        frame_time_result = filterFrameTimeList(filter);
    }
    
    if (frame_time_result == SDKError::Success) {
        std::vector<ServerFrameTimeStateSharedPtr> frame_time_list;
        for (auto item = frame_time_list_.begin(); item != frame_time_list_.end(); item ++) {
            frame_time_list.push_back(*item);
        }
        
        *output = frame_time_list;
    }
    
    return frame_time_result;
}

//MARK: - Converter

SDKError ParserImp::convertParserResultToPublic(DJI::FlightRecord::ParserResult result_code) {
    switch (result_code) {
        case DJI::FlightRecord::ParserResult::InvalidParam:
            return SDKError::InvalidParameters;
        case DJI::FlightRecord::ParserResult::ReadFileError:
        case DJI::FlightRecord::ParserResult::InitFileHandleFailed:
        case DJI::FlightRecord::ParserResult::NoFileHandle:
        case DJI::FlightRecord::ParserResult::NoParser:
            return SDKError::FileOperationFailed;
        case DJI::FlightRecord::ParserResult::VerifyFileFailed:
        case DJI::FlightRecord::ParserResult::DecodeFailed:
            return SDKError::IllegalFileContent;
        case DJI::FlightRecord::ParserResult::VersionNotSupport:
        case DJI::FlightRecord::ParserResult::DecoderNotFound:
            return SDKError::VersionNotSupport;
        case DJI::FlightRecord::ParserResult::Success:
            return SDKError::Success;
        case DJI::FlightRecord::ParserResult::FeatureNotSupported:
            return SDKError::FeatureNotSupported;
            
        default:
            break;
    }
    
    return SDKError::Failure;
}

//MARK: - Image

SDKError ParserImp::parserImageData() {
    images_.clear();
    
    auto result_code = parser_->parseImageData(ParseImageType::Thumbnail, [this](FlightRecordParserEngine *engine, int index, uint8_t *buffer, long length) {
        std::shared_ptr<ImageDataImp> image_ptr = nullptr;
        
        try {
            image_ptr = this->images_.at(index);
        } catch (...) {
            image_ptr = std::make_shared<ImageDataImp>();
            this->images_.push_back(image_ptr);
        }
        
        auto image_buf = std::make_shared<Buffer>((void *)buffer, length);
        image_ptr->set_thumbnail(image_buf);
    });
    
    if (result_code != ParserResult::Success) {
        return convertParserResultToPublic(result_code);
    }
    
    result_code = parser_->parseImageData(ParseImageType::Snapshot, [this](FlightRecordParserEngine *engine, int index, uint8_t *buffer, long length) {
        std::shared_ptr<ImageDataImp> image_ptr = nullptr;
        
        try {
            image_ptr = this->images_.at(index);
        } catch (...) {
            image_ptr = std::make_shared<ImageDataImp>();
            this->images_.push_back(image_ptr);
        }
        
        auto image_buf = std::make_shared<Buffer>((void *)buffer, length);
        image_ptr->set_previewImage(image_buf);
    });
    
    if (result_code != ParserResult::Success) {
        return convertParserResultToPublic(result_code);
    }
    
    DJIFlightRecordDetailDataEndStruct info = {0};
    auto info_result_code = parser_->obtainInfo(info);
    if (info_result_code != ParserResult::Success) {
        return convertParserResultToPublic(info_result_code);
    }
    
    size_t image_count = std::min(images_.size(), (size_t)MomentPicNum);
    for (int i = 0; i < image_count; i ++) {
        auto image_ptr = images_.at(i);
        
        auto latitude_degree = Rad2deg(info.momentPicLatitude[i]);
        auto longitude_degree = Rad2deg(info.momentPicLongitude[i]);
        auto location = std::make_shared<LocationCoordinate2DImp>(latitude_degree, longitude_degree);
        image_ptr->set_coordinate(location);
    }
    
    return SDKError::Success;
}

//MARK: - Summary

SDKError ParserImp::parserSummary() {
    summary_info_ = std::make_shared<SummaryInformationImp>();
    
    DJIFlightRecordDetailDataEndStruct info = {0};
    auto info_result_code = parser_->obtainInfo(info);
    if (info_result_code != ParserResult::Success) {
        return convertParserResultToPublic(info_result_code);
    }
    
    uint8_t version = 0;
    auto version_result_code = parser_->obtainVersion(version);
    if (version_result_code != ParserResult::Success) {
        return convertParserResultToPublic(version_result_code);
    }
    
    uint8_t appVersion[4];
    std::string battery_sn_str;
    std::string camera_sn_str;
    std::string rc_sn_str;
    std::string fc_sn_str;
    std::string aircraft_name_str;
    
    if (version > 5) {
        memcpy(&appVersion, &info.newFRData.appVersion, sizeof(appVersion));
        
        // get battery sn
        battery_sn_str = ConvertRawDataToUTF8((const char *)info.newFRData.batterySN, sizeof(info.newFRData.batterySN));
        
        // get camera sn
        camera_sn_str = ConvertRawDataToUTF8((const char *)info.newFRData.cameraSN, sizeof(info.newFRData.cameraSN));
        
        // get rc sn
        rc_sn_str = ConvertRawDataToUTF8((const char *)info.newFRData.rcSN, sizeof(info.newFRData.rcSN));
        
        // get fc sn
        fc_sn_str = ConvertRawDataToUTF8((const char *)info.newFRData.aircraftSN, sizeof(info.newFRData.aircraftSN));
        
        // get aircraft name
        aircraft_name_str = ConvertRawDataToUTF8((const char *)info.newFRData.aircraftName, sizeof(info.newFRData.aircraftName));
        
        // fill the product type
        product_type_ = (ProductType)info.newFRData.productType;
    }
    
    summary_info_->set_product_type(product_type_);
    
    // fill the battery sn
    if (battery_sn_str.length() > 0) {
        auto component = getSummaryValidBatteryComponent(0);
        component->set_serialNumber(battery_sn_str);
    }
    
    // fill the camera sn
    if (camera_sn_str.length() > 0) {
        auto component = getSummaryValidCameraComponent(0);
        component->set_serialNumber(camera_sn_str);
    }
    
    // fill the rc sn
    if (rc_sn_str.length() > 0) {
        auto component = getSummaryValidRCComponent();
        component->set_serialNumber(rc_sn_str);
    }
    
    // fill the fc sn
    if (fc_sn_str.length() > 0) {
        auto component = getSummaryValidFCComponent();
        component->set_serialNumber(fc_sn_str);
    }
    
    // fill the aircraft name
    summary_info_->set_aircraftName(aircraft_name_str);
    
    // fill the start time.
    summary_info_->set_startTime(info.timeStamp / 1000.0);
    
    // fill the platform
    summary_info_->set_platform(ConvertInternalPlatformToPublic((DJI::FlightRecord::Platform)appVersion[0]));
    
    // fill the start coordinate
    auto location = std::make_shared<LocationCoordinate2DImp>(info.latitude, info.longitude);
    summary_info_->set_startCoordinate(location);
    
    // fill the total distance
    summary_info_->set_totalDistance(info.totalDistance / 1000.0);
    
    // fill the total time
    summary_info_->set_totalDistance(info.totalTime / 1000.0);
    
    // fill the app version string
    std::vector<int32_t> app_version;
    for (int i = 0; i < 3; i ++) {
        app_version.push_back(appVersion[i + 1]);
    }
    summary_info_->set_appVersion(app_version);
    summary_info_->set_samplingRate(10);
    
    // fill max data
    summary_info_->set_maxHeight(info.maxHeight);
    summary_info_->set_maxHorizontalSpeed(info.maxHorizontalSpeed);
    summary_info_->set_maxVirticalSpeed(info.maxVirticalSpeed);
    
    auto uuid_len = sizeof(info.uuid);
    if (isValidContent(info.uuid, uuid_len)) {
        summary_info_->set_uuid(std::string(info.uuid, uuid_len));
    }
    
    return SDKError::Success;
}

void ParserImp::fillSummary(FlightRecordDataType data_type,
                            uint8_t *buffer,
                            uint64_t length) {
    if (!summary_info_) {
        parserSummary();
    }
    
    if (length <= 0) {
        return;
    }
    
    switch (data_type) {
        case CustomFlightRecordDataType:
        {
            DJIFlightRecordCustomInfoStruct data_source = {0};
            memcpy(&data_source, buffer, std::min(sizeof(data_source), (size_t)length));
            
            if (summary_info_->startTime() <= 0 && data_source.updateTimeStamp > 0) {
                summary_info_->set_startTime(data_source.updateTimeStamp / 1000.0);
            }
        }
            break;
        case RecoverInfoDataType:
        {
            DJIFlightRecordRecoverInfoStruct data_source = {0};
            memcpy(&data_source, buffer, std::min(sizeof(data_source), (size_t)length));
            
            ProductType product_type = (ProductType)data_source.productType;
            if (product_type != ProductType::None) {
                if (product_type_ == ProductType::None) {
                    product_type_ = product_type;
                    summary_info_->set_product_type(product_type_);
                }
            }
            
            Platform platform = ConvertInternalPlatformToPublic((DJI::FlightRecord::Platform)data_source.appVersion[0]);
            summary_info_->set_platform(platform);
            
            std::vector<int32_t> app_version;
            for (int i = 0; i < 3; i ++) {
                app_version.push_back(data_source.appVersion[i + 1]);
            }
            summary_info_->set_appVersion(app_version);
            
            auto new_battery_sn = ConvertRawDataToUTF8((const char *)data_source.batterySN, sizeof(data_source.batterySN));
            if (new_battery_sn.size() > 0) {
                auto exist_component = getSummaryValidBatteryComponent(0);
                exist_component->set_serialNumber(new_battery_sn);
            }
            
            auto aircraft_name_str = ConvertRawDataToUTF8(data_source.aircraftName, sizeof(data_source.aircraftName));
            if (aircraft_name_str.size() > 0) {
                summary_info_->set_aircraftName(aircraft_name_str);
            }
            
            auto new_camera_sn = ConvertRawDataToUTF8((const char *)data_source.cameraSN, sizeof(data_source.cameraSN));
            if (new_camera_sn.size() > 0) {
                auto exist_component = getSummaryValidCameraComponent(0);
                exist_component->set_serialNumber(new_camera_sn);
            }
            
            auto new_rc_sn = ConvertRawDataToUTF8((const char *)data_source.rcSN, sizeof(data_source.rcSN));
            if (new_rc_sn.size() > 0) {
                auto exist_component = getSummaryValidRCComponent();
                exist_component->set_serialNumber(new_rc_sn);
            }
            
            // auto new_fc_sn = ConvertRawDataToUTF8((const char *)data_source.aircraftSN, sizeof(data_source.aircraftSN));
            // if (new_fc_sn.size() > 0) {
            //     auto exist_component = getSummaryValidFCComponent();
            //     exist_component->set_serialNumber(new_fc_sn);
            // }
        }
            break;
        case FirmwareVersionType:
        {
            size_t item_len = sizeof(singleVersionInfo);
            int count = floor(length / item_len);
            if (count <= 0) {
                return;
            }
            
            for (int i = 0; i < count; i ++) {
                singleVersionInfo version;
                memcpy(&version, buffer + sizeof(singleVersionInfo) * i, sizeof(singleVersionInfo));
                
                std::shared_ptr<ComponentInformationImp> component = nullptr;
                
                switch ((DJI_SENDTYPE)version.senderType) {
                    case DJI_SENDTYPE_CAMERA:
                        component = getSummaryValidCameraComponent(version.subSenderType);
                        break;
                    case DJI_SENDTYPE_MC:
                        component = getSummaryValidFCComponent();
                        break;
                    case DJI_SENDTYPE_BATTERY:
                        component = getSummaryValidBatteryComponent(version.subSenderType);
                        break;
                    case DJI_SENDTYPE_GIMBAL:
                        component = getSummaryValidGimbalComponent(version.subSenderType);
                        break;
                    case DJI_SENDTYPE_RC:
                        component = getSummaryValidRCComponent();
                        break;
                    default:
                        break;
                }
                
                if (!component) {
                    return;
                }
                
                std::vector<int32_t> new_firmware_version;
                for (int i = 0; i < 4; i ++) {
                    new_firmware_version.push_back(version.firmwareVersion.versions[i]);
                }
                component->set_firmwareVersion(new_firmware_version);
            }
        }
            break;
        case ComponentSerialNumberDataType:
        {
            DJIFlightRecordComponentSN *data_source = (DJIFlightRecordComponentSN *)buffer;
            if (data_source->dataLength + sizeof(DJIFlightRecordComponentSN) < length) {
                // invalid buffer.
                return;
            }
            
            auto new_sn = ConvertRawDataToUTF8((const char*)data_source->componentSN, data_source->dataLength);
            std::shared_ptr<ComponentInformationImp> component = nullptr;
            if (new_sn.size() > 0) {
                switch (data_source->type) {
                    case DJIFlightRecordComponentType_RC:
                        component = getSummaryValidRCComponent();
                        break;
                    case DJIFlightRecordComponentType_Camera:
                        component = getSummaryValidCameraComponent(data_source->seq);
                        break;
                    case DJIFlightRecordComponentType_Gimbal:
                        component = getSummaryValidGimbalComponent(data_source->seq);
                        break;
                    case DJIFlightRecordComponentType_Battery:
                        component = getSummaryValidBatteryComponent(data_source->seq);
                        break;
                    case DJIFlightRecordComponentType_FlightController:
                        component = getSummaryValidFCComponent();
                        break;
                        
                    default:
                        break;
                }
            }
            
            if (component) {
                component->set_serialNumber(new_sn);
            }
        }
            break;
            
        default:
            break;
    }
}

void ParserImp::recalculateSummary() {
    if (summary_info_->totalDistance() < 0) {
        summary_info_->set_totalDistance(0);
    }
    
    if (summary_info_->maxHeight() < 0) {
        summary_info_->set_maxHeight(0);
    }
    
    if (summary_info_->maxHorizontalSpeed() < 0) {
        summary_info_->set_maxHorizontalSpeed(0);
    }
    
    if (summary_info_->maxVirticalSpeed() < 0) {
        summary_info_->set_maxVirticalSpeed(0);
    }
    
    size_t frame_time_list_len = frame_time_list_.size();
    bool has_get_start_point = false;
    double start_flight_time = 0;
    for (size_t index = 0; index < frame_time_list_len; index ++) {
        auto frame_time = frame_time_list_[index];
        auto fc = frame_time->flightControllerStateImp();
        if (fc == nullptr) {
            break;
        }
        auto aircraft_location = fc->aircraftLocation();
        
        if (!aircraft_location) {
            continue;
        }
        
        if (index == 0) {
            start_flight_time = fc->flightTimeInSeconds();
        }
        
        if (!has_get_start_point) {
            if (CoordinateIsValid(fc->aircraftLocation()->latitude(),
                                  fc->aircraftLocation()->longitude(),
                                  fc->isGPSBeingUsed(),
                                  fc->gpsLevel())) {
                summary_info_->set_startCoordinate(fc->aircraftLocation());
                has_get_start_point = true;
            }
        }
        
        if (index == frame_time_list_len - 1) {
            summary_info_->set_totalDistance(fc->cumulativeFlightDistance());
        }
        
        summary_info_->set_totalTime(fc->flightTimeInSeconds() - start_flight_time);
        
        if (fc->altitude() > summary_info_->maxHeight()) {
            summary_info_->set_maxHeight(fc->altitude());
        }
        
        if (fc->velocity()->velocityZ() > summary_info_->maxVirticalSpeed()) {
            summary_info_->set_maxVirticalSpeed(fc->velocity()->velocityZ());
        }
        
        auto new_horizonal_speed = sqrt(pow(fc->velocity()->velocityX(), 2) + pow(fc->velocity()->velocityY(), 2));
        if (new_horizonal_speed > summary_info_->maxHorizontalSpeed()) {
            summary_info_->set_maxHorizontalSpeed(new_horizonal_speed);
        }
    }
    
    is_recalculate_info_ = true;
}

std::shared_ptr<ComponentInformationImp> ParserImp::getSummaryValidCameraComponent(int index) {
    auto cameras_map = summary_info_->camerasInformationImp();
    auto camera_iter = cameras_map->find(index);
    if (camera_iter != cameras_map->end()) {
        return (*camera_iter).second;
    }
    
    auto component = std::make_shared<ComponentInformationImp>();
    component->set_index(index);
    (*cameras_map)[index] = component;
    
    return component;
}

std::shared_ptr<ComponentInformationImp> ParserImp::getSummaryValidBatteryComponent(int index) {
    auto battery_info_map = summary_info_->batteriesInformationImp();
    auto battery_iter = battery_info_map->find(index);
    if (battery_iter != battery_info_map->end()) {
        return (*battery_iter).second;
    }
    
    auto component = std::make_shared<ComponentInformationImp>();
    component->set_index(index);
    (*battery_info_map)[index] = component;
    
    return component;
}

std::shared_ptr<ComponentInformationImp> ParserImp::getSummaryValidGimbalComponent(int index) {
    auto gimbals_map = summary_info_->gimbalsInformationImp();
    auto gimbal_iter = gimbals_map->find(index);
    if (gimbal_iter != gimbals_map->end()) {
        return (*gimbal_iter).second;
    }
    
    auto component = std::make_shared<ComponentInformationImp>();
    component->set_index(index);
    (*gimbals_map)[index] = component;
    
    return component;
}

std::shared_ptr<ComponentInformationImp> ParserImp::getSummaryValidFCComponent() {
    auto component = summary_info_->flightControllerInformationImp();
    if (!component) {
        component = std::make_shared<ComponentInformationImp>();
        component->set_index(0);
        summary_info_->set_flightControllerInformation(component);
    }
    return component;
}

std::shared_ptr<ComponentInformationImp> ParserImp::getSummaryValidRCComponent() {
    auto component = summary_info_->remoteControllerInformationImp();
    if (!component) {
        component = std::make_shared<ComponentInformationImp>();
        component->set_index(0);
        summary_info_->set_remoteControllerInformation(component);
    }
    return component;
}

//MARK: - Frame Time

SDKError ParserImp::filterFrameTimeList(std::map<FlightRecordDataType, bool> filter) {
    frame_time_list_.clear();
    bool has_first_osd = false;
    auto error_code = SDKError::Success;
    auto parser_block = [this, filter, &has_first_osd, &error_code] (FlightRecordParserEngine *engine, FlightRecordDataType data_type, int index, uint8_t *buffer, uint64_t length, bool *stop) {
        if (buffer == nullptr || length <= 0) {
            return;
        }
        
        if (error_code != SDKError::Success) {
            (*stop) = true;
            return;
        }
        
        switch (data_type) {
            case CustomFlightRecordDataType:
            case RecoverInfoDataType:
            case FirmwareVersionType:
            case ComponentSerialNumberDataType:
                fillSummary(data_type, buffer, length);
                break;
                
            default:
                break;
        }
        
        if (filter.size() > 0) {
            if (data_type != OSDFlightRecordDataType) {
                auto filter_iter = filter.find(data_type);
                if (filter_iter == filter.end()) {
                    return;
                }
                
                if (!(*filter_iter).second) {
                    return;
                }
            }
        }
        
        if ((data_type == OSDFlightRecordDataType && index >= 0) ||
            this->frame_time_list_.size() <= 0) {
            
            if (frame_time_list_.size() > 0) {
                if (has_first_osd) {
                    frame_time_list_.push_back(frame_time_list_.back()->clone());
                }
            } else {
                auto frame_time = std::make_shared<FrameTimeStateImp>();
                frame_time_list_.push_back(frame_time);
            }
            
            if (data_type == OSDFlightRecordDataType) {
                has_first_osd = true;
            }
        }
        
        auto frame_time = frame_time_list_.back();
        if (!frame_time) {
            return;
        }
        
        bool fill_operation_result = true;
        SDKError error_code = SDKError::Success;
        
        do {
            switch (data_type) {
                case RCFlightRecordDataType:
                case RCPushGPSFlightRecordDataType:
                {
                    fill_operation_result = fillRCHardwareState(data_type, buffer, length, frame_time);
                }
                    break;
                case AppSpecialControlJoyStickDataType:
                {
                    fill_operation_result = fillMobileRC(data_type, buffer, length, frame_time);
                }
                    break;
                case GimbalFlightRecordDataType:
                {
                    fill_operation_result = fillGimbalState(data_type, buffer, length, frame_time);
                }
                    break;
                case CenterBatteryFlightRecordDataType:
                case SmartBatteryGroupDataType:
                {
                    fill_operation_result = fillBatteryState(data_type, buffer, length, frame_time);
                }
                    break;
                case OSDFlightRecordDataType:
                {
                    dji_fc_osd_push osd = {0};
                    memcpy(&osd, buffer, std::min((size_t)length, sizeof(osd)));
                    drone_type_ = (DJI::FlightRecord::DroneType)osd.droneType;
                    
                    fill_operation_result = fillFlightController(data_type, buffer, length, frame_time);
                    if (fill_operation_result == false) {
                        break;
                    }
                    
                    fill_operation_result = fillBatteryState(data_type, buffer, length, frame_time);
                    if (fill_operation_result == false) {
                        break;
                    }
                    
                    fill_operation_result = fillAirlinkState(data_type, buffer, length, frame_time);
                    if (fill_operation_result == false) {
                        break;
                    }
                }
                    break;
                case PushedBatteryFlightRecordDataType:
                {
                    fill_operation_result = fillFlightController(data_type, buffer, length, frame_time);
                    if (fill_operation_result == false) {
                        break;
                    }
                    
                    fill_operation_result = fillBatteryState(data_type, buffer, length, frame_time);
                    if (fill_operation_result == false) {
                        break;
                    }
                }
                    break;
                case OSDHomeFlightRecordDataType:
                case MCParamDataType:
                case AppVirtualStickDataType:
                {
                    fill_operation_result = fillFlightController(data_type, buffer, length, frame_time);
                }
                    break;
                case VisionGroupDataType:
                {
                    fill_operation_result = fillFlightController(data_type, buffer, length, frame_time);
                    if (fill_operation_result == false) {
                        break;
                    }
                    
                    fill_operation_result = fillVisionData(data_type, buffer, length, frame_time);
                    if (fill_operation_result == false) {
                        break;
                    }
                }
                    break;
                case CameraInfoFlightRecordDataType:
                {
                    fill_operation_result = fillCameraState(data_type, buffer, length, frame_time);
                }
                    break;
                case AgricultureOFDMRadioSignalPush:
                {
                    fill_operation_result = fillAirlinkState(data_type, buffer, length, frame_time);
                }
                    break;
                case ShowTipsFlightRecordDataType:
                case ShowWarningFlightRecordDataType:
                case ShowSeriousWarningFlightRecordDataType:
                {
                    fill_operation_result = fillGOBusiness(data_type, buffer, length, frame_time);
                }
                    break;
                case AppLocationDataType:
                {
                    fill_operation_result = fillMobileDevice(data_type, buffer, length, frame_time);
                }
                    break;
                    
                default:
                    break;
            }
        } while (0);
        
        // Cumulative calculation distance
        if (data_type == OSDFlightRecordDataType && frame_time_list_.size() >= 2) {
            int last_frame_Index = 0;
            auto last_frame_time = findValidAircraftLocaion((int)frame_time_list_.size() - 1, &last_frame_Index);
            if (!last_frame_time) {
                return;
            }
            
            int second_frame_time_index = 0;
            auto second_frame_time = findValidAircraftLocaion(last_frame_Index - 1, &second_frame_time_index);
            
            if (!second_frame_time) {
                return;
            }
            
            auto new_distance = CoordinateDistance(last_frame_time->flightControllerState()->aircraftLocation()->latitude(),
                                                   last_frame_time->flightControllerState()->aircraftLocation()->longitude(),
                                                   second_frame_time->flightControllerState()->aircraftLocation()->latitude(),
                                                   second_frame_time->flightControllerState()->aircraftLocation()->longitude());
            last_frame_time->flightControllerStateImp()->set_cumulativeFlightDistance(second_frame_time->flightControllerStateImp()->cumulativeFlightDistance() + new_distance);
        }
    };
    
    auto detail_operation_code = convertParserResultToPublic(parser_->parseDetailData(parser_block));
    
    if (error_code != SDKError::Success) {
        return error_code;
    }
    
    return detail_operation_code;
}

//MARK: - Filler

bool ParserImp::fillRCHardwareState(FlightRecordDataType data_type,
                                    uint8_t *buffer,
                                    uint64_t length,
                                    std::shared_ptr<FrameTimeStateImp>& output) {
    if (!output->rcHardwareState()) {
        auto rc_hardware = std::make_shared<RCHardwareStateImp>();
        output->set_rcHardwareState(rc_hardware);
    }
    auto rc_state = output->rcHardwareStateImp();
    if (!DJIFR::standardization::Filler(rc_state, this->product_type_, data_type, buffer, length)) {
        assert(false && "should fill the rc state success");
        return false;
    }
    
    return true;
}

bool ParserImp::fillMobileRC(FlightRecordDataType data_type,
                             uint8_t *buffer,
                             uint64_t length,
                             std::shared_ptr<FrameTimeStateImp>& output) {
    if (!output->mobileRemoteController()) {
        auto mobile_rc = std::make_shared<MobileRemoteControllerStateImp>();
        output->set_mobileRemoteController(mobile_rc);
    }
    auto mobile_rc = output->mobileRemoteControllerImp();
    if (!Filler(mobile_rc, data_type, buffer, length)) {
        assert(false && "should fill the rc state success");
        return false;
    }
    
    return true;
}

bool ParserImp::fillGimbalState(FlightRecordDataType data_type,
                                uint8_t *buffer,
                                uint64_t length,
                                std::shared_ptr<FrameTimeStateImp>& output) {
    if (!output->gimbalState()) {
        auto gimbal_state = std::make_shared<GimbalStateImp>();
        output->set_gimbalState(gimbal_state);
    }
    
    auto gimbal_state = output->gimbalStateImp();
    if (!Filler(gimbal_state, data_type, buffer, length)) {
        assert(false && "should fill the gimbal state success");
        return false;
    }
    
    return true;
}

bool ParserImp::fillFlightController(FlightRecordDataType data_type,
                                     uint8_t *buffer,
                                     uint64_t length,
                                     std::shared_ptr<FrameTimeStateImp>& output) {
    if (!output->flightControllerState()) {
        auto fc_state = std::make_shared<FlightControllerStateImp>();
        output->set_flightControllerState(fc_state);
    }
    
    auto fc_state = output->flightControllerStateImp();
    if (!Filler(fc_state, data_type, buffer, length)) {
        assert(false && "should fill the fc state success");
        return false;
    }
    
    return true;
}

bool ParserImp::fillCameraState(FlightRecordDataType data_type,
                                uint8_t *buffer,
                                uint64_t length,
                                std::shared_ptr<FrameTimeStateImp>& output) {
    if (!output->cameraState()) {
        auto camera_state = std::make_shared<CameraStateImp>();
        output->set_cameraState(camera_state);
    }
    
    auto camera_state = output->cameraStateImp();
    if (!Filler(camera_state, data_type, buffer, length)) {
        assert(false && "should fill the camera state success");
        return false;
    }
    
    return true;
}

bool ParserImp::fillBatteryState(FlightRecordDataType data_type,
                                 uint8_t *buffer,
                                 uint64_t length,
                                 std::shared_ptr<FrameTimeStateImp>& output) {
    if (!Filler(output->batteriesState(), data_type, buffer, length)) {
        assert(false && "should fill the battery state success");
        return false;
    }
    
    return true;
}

bool ParserImp::fillAirlinkState(FlightRecordDataType data_type,
                                 uint8_t *buffer,
                                 uint64_t length,
                                 std::shared_ptr<FrameTimeStateImp>& output) {
    if (!output->airlinkState()) {
        auto state = std::make_shared<AirLinkStateImp>();
        output->set_airlinkState(state);
    }
    
    auto state = output->airlinkStateImp();
    if (!Filler(state, data_type, buffer, length)) {
        assert(false && "should fill the airlink state success");
        return false;
    }
    
    return true;
}

bool ParserImp::fillGOBusiness(FlightRecordDataType data_type,
                               uint8_t *buffer,
                               uint64_t length,
                               std::shared_ptr<FrameTimeStateImp>& output) {
    if (!output->goBusinessData()) {
        auto state = std::make_shared<GOBusinessDataImp>();
        output->set_goBusinessData(state);
    }
    
    auto state = output->goBusinessDataImp();
    if (!Filler(state, data_type, buffer, length)) {
        assert(false && "should fill the go business state success");
        return false;
    }
    
    return true;
}

bool ParserImp::fillMobileDevice(FlightRecordDataType data_type,
                                 uint8_t *buffer,
                                 uint64_t length,
                                 std::shared_ptr<FrameTimeStateImp>& output) {
    if (!output->mobileDeviceState()) {
        auto state = std::make_shared<MobileDeviceStateImp>();
        output->set_mobileDeviceState(state);
    }
    
    auto state = output->mobileDeviceStateImp();
    if (!Filler(state, data_type, buffer, length)) {
        assert(false && "should fill the mobile device state success");
        return false;
    }
    
    return true;
}

bool ParserImp::fillVisionData(FlightRecordDataType data_type,
                               uint8_t *buffer,
                               uint64_t length,
                               std::shared_ptr<FrameTimeStateImp>& output) {
    if (!output->visionState()) {
        auto vision = std::make_shared<VisionStateImp>();
        output->set_visionState(vision);
    }
    
    auto vision = output->visionStateImp();
    if (!Filler(vision, data_type, buffer, length)) {
        assert(false && "should fill the vision success");
        return false;
    }
    
    return true;
}

std::shared_ptr<FrameTimeStateImp> ParserImp::findValidAircraftLocaion(int index, int *final_index) {
    if (index > frame_time_list_.size() - 1) {
        return nullptr;
    }
    
    int findIndex = index;
    while (findIndex >= 0) {
        auto frame_time = frame_time_list_.at(findIndex);
        auto flight_controller = frame_time->flightControllerStateImp();
        if (CoordinateIsValid(flight_controller->aircraftLocation()->latitude(),
                              flight_controller->aircraftLocation()->longitude(),
                              flight_controller->isGPSBeingUsed(),
                              flight_controller->gpsLevel())) {
            (*final_index) = findIndex;
            return frame_time;
        }
        
        findIndex --;
    }
    
    return nullptr;
}
