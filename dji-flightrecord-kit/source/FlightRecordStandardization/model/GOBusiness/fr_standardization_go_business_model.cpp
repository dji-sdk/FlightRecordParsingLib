//
//  fr_standardization_go_business_model.cpp
//  FlightRecordStandardization
//
//  Copyright © 2020 DJISDK. All rights reserved.
//

#include "fr_standardization_go_business_model.hpp"

using namespace DJIFR::standardization;

GOBusinessDataImp::GOBusinessDataImp() {
    
}

GOBusinessDataImp::~GOBusinessDataImp() {
    
}

uint8_t GOBusinessDataImp::version() const {
    return version_;
}

void GOBusinessDataImp::set_version(uint8_t version) {
    version_ = version;
}

std::string GOBusinessDataImp::tips() const {
    return tips_;
}
void GOBusinessDataImp::set_tips(const std::string& tips) {
    tips_ = tips;
}

std::string GOBusinessDataImp::warning() const {
    return warning_;
}

void GOBusinessDataImp::set_warning(const std::string& warning) {
    warning_ = warning;
}

std::string GOBusinessDataImp::seriousWarning() const {
    return seriousWarning_;
}

void GOBusinessDataImp::set_seriousWarning(const std::string& seriousWarning) {
    seriousWarning_ = seriousWarning;
}

BufferSharedPtr GOBusinessDataImp::goBusinessData() const {
    return goBusinessData_;
}

void GOBusinessDataImp::set_goBusinessData(const BufferSharedPtr& goBusinessData) {
    goBusinessData_ = goBusinessData;
}
