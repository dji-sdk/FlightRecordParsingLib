//
//  flight_record_version_decoder.cpp
//  FlightRecordEngine
//
//  Copyright © 2017 DJI. All rights reserved.
//

#include <Parser/decoder/flight_record_version_decoder.h>
#include <model/protocol/fr_protocol.h>
#include <Utils/File/FlightRecordFileHandleUtils.h>
#include <Parser/decoder/flight_record_version_decoder_set.h>

using namespace DJI::FlightRecord;

VersionDecoder::VersionDecoder():
minimum_support_version_(0),
support_decode_version_category_(VersionCategory::None) {
    
}

VersionDecoder::~VersionDecoder() {
    decode_detail_info_lambda_ = nullptr;
    decode_detail_data_lambda_ = nullptr;
    get_detail_data_message_lambda_ = nullptr;
}

ParserResult VersionDecoder::DecodeDetailInfo(const FileHandlerUtilsPtr& file_handler, BufferPtr &output, BufferPtr &signature) {
    if (decode_detail_info_lambda_) {
        return decode_detail_info_lambda_(file_handler, output, signature);
    }
    
    return ParserResult::Failure;
}

BufferPtr VersionDecoder::DecodeDetailData(const FileCacheUtilsPtr& cache) {
    if (decode_detail_data_lambda_) {
        return decode_detail_data_lambda_(cache);
    }
    
    return nullptr;
}

ParserResult VersionDecoder::getDetailDataMessage(const FileHandlerUtilsPtr& file_handler, DetailDataMessage &message) {
    if (get_detail_data_message_lambda_) {
        return get_detail_data_message_lambda_(file_handler, message);
    }
    
    return ParserResult::Failure;
}

int VersionDecoder::minimum_support_version() {
    return minimum_support_version_;
}

void VersionDecoder::set_minimum_support_version(int version) {
    minimum_support_version_ = version;
}

VersionCategory VersionDecoder::support_decode_version_category() {
    return support_decode_version_category_;
}

void VersionDecoder::set_support_decode_version_category(VersionCategory version) {
    support_decode_version_category_ = version;
}

//////////////////////////////// Getter Lambda ////////////////////////////////
DJIDecodeDetailInfoFunction VersionDecoder::DecodeDetailInfoLambda() {
    return decode_detail_info_lambda_;
}

DJIDecodeDetailDataFunction VersionDecoder::DecodeDetailDataLambda() {
    return decode_detail_data_lambda_;
}

DJIGetDetailDataMessageFunction VersionDecoder::getDetailDataMessageLambda() {
    return get_detail_data_message_lambda_;
}

//////////////////////////////// Setter Lambda ////////////////////////////////
void VersionDecoder::setDecodeDetailInfoLambda(DJIDecodeDetailInfoFunction lambda) {
    decode_detail_info_lambda_ = lambda;
}

void VersionDecoder::setDecodeDetailDataLambda(DJIDecodeDetailDataFunction lambda) {
    decode_detail_data_lambda_ = lambda;
}

void VersionDecoder::setGetDetailDataMessageLambda(DJIGetDetailDataMessageFunction lambda) {
    get_detail_data_message_lambda_ = lambda;
}

//MARK: - Version Category
VersionExtension DJI::FlightRecord::ParseVersion(const FileHandlerUtilsPtr& file_handler) {
    VersionExtension version_extension;
    version_extension.department = Department::Unknown;
    version_extension.version = VersionCategory::None;
    DJIFlightRecordDetailFilePrefixStruct detailPrefix = {0};
    file_handler->seekFromStart(0);
    if (file_handler->read(&detailPrefix, sizeof(detailPrefix)) != sizeof(detailPrefix)) {
        return version_extension;
    }
    
    if (detailPrefix.detailInfoFormatVersion == Version13DecoderMaxVersion ||
        detailPrefix.detailInfoFormatVersion == Version13_2DecoderMaxVersion) {
        return GetVersionCategoryBy13Decoder(file_handler);
    }
    
    return version_extension;
}
