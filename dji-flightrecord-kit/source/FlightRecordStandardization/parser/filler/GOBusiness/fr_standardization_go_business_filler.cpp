//
//  fr_standardization_go_business_filler.cpp
//  FlightRecordStandardization
//
//  Copyright © 2020 DJISDK. All rights reserved.
//

#include "fr_standardization_go_business_filler.hpp"
#include <model/protocol/fr_protocol.h>
#include <string.h>
#include "fr_standardization_common.hpp"

using namespace DJIFR::standardization;
using namespace DJI::FlightRecord;

static bool FillShowTipsFlightRecordDataType(const std::string& data_source,
                                             std::shared_ptr<GOBusinessDataImp>& output) {
    output->set_version(0);
    output->set_tips(data_source);
    
    return true;
}

static bool FillShowWarningFlightRecordDataType(const std::string& data_source,
                                                std::shared_ptr<GOBusinessDataImp>& output) {
    output->set_version(0);
    output->set_warning(data_source);
    
    return true;
}

static bool FillShowSeriousWarningFlightRecordDataType(const std::string& data_source,
                                                       std::shared_ptr<GOBusinessDataImp>& output) {
    output->set_version(0);
    output->set_seriousWarning(data_source);
    
    return true;
}

static bool fillGOBusinessDataType(const BufferSharedPtr& data_source,
                                   std::shared_ptr<GOBusinessDataImp>& output) {
    output->set_version(1);
    output->set_goBusinessData(data_source);
    
    return true;
}

//MARK: - Public

bool DJIFR::standardization::Filler(std::shared_ptr<GOBusinessDataImp>& output,
                                    FlightRecordDataType data_type,
                                    uint8_t *buffer,
                                    uint64_t length) {
    switch (data_type) {
        case ShowTipsFlightRecordDataType:
        {
            std::string data_source((char *)buffer, length);
            return FillShowTipsFlightRecordDataType(data_source, output);
        }
            break;
        case ShowWarningFlightRecordDataType:
        {
            std::string data_source((char *)buffer, length);
            return FillShowWarningFlightRecordDataType(data_source, output);
        }
            break;
        case ShowSeriousWarningFlightRecordDataType:
        {
            std::string data_source((char *)buffer, length);
            return FillShowSeriousWarningFlightRecordDataType(data_source, output);
        }
            break;
        case GOBusinessDataType:
        {
            auto data_source = std::make_shared<Buffer>((void *)buffer, length);
            return fillGOBusinessDataType(data_source, output);
        }
            break;
            
        default:
            break;
    }
    
    return false;
}
