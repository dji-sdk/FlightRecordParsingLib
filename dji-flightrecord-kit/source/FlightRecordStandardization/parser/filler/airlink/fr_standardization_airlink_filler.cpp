//
//  fr_standardization_airlink_filler.cpp
//  FlightRecordStandardization
//
//  Copyright © 2020 DJISDK. All rights reserved.
//

#include "fr_standardization_airlink_filler.hpp"
#include <model/protocol/fr_protocol.h>
#include <string.h>
#include <math.h>

using namespace DJIFR::standardization;
using namespace DJI::FlightRecord;

static bool FillOFDMRadioSignalPush(const dji_ofdm_radio_signal_push& data_source,
                                    std::shared_ptr<AirLinkStateImp>& output) {
    if (output->drone_type() == DroneType::Unknown) {
        return true;
    }
    
    switch (output->drone_type()) {
            // WIFI & LightBridge
        case DroneType::YQqHWaFYevzieChe:
        case DroneType::kqZiGqPiBuJtGbXI:
        case DroneType::SjtZVcHLcFvOrATk:
        case DroneType::axPYBMhqOPxIAmRT:
        case DroneType::nZgzsaZeSVoFDbCU:
        case DroneType::VajTqWfawuZTCdTz:
        case DroneType::CMDBsWvfrkHQsQzP:
        case DroneType::gvEBDHARYJjdhoer:
        case DroneType::EbeKfeODxZwEYpPS:
        case DroneType::dYxdHETreaRpuiyw:
        case DroneType::xtRdpvrXtxzvwDzF:
        case DroneType::iUDZbWKZULbBLQaC:
        case DroneType::gwijeEWNaJaeGehp:
        case DroneType::yjPSxNFfUVSgCwsk:
        case DroneType::YQqHWaFYevzieChe2:
        case DroneType::NJaWiOHsBzaJEsKG:
        case DroneType::eaaxmyeNLEOTJxYR:
        case DroneType::dZHFAjNYqzCRJVjl:
        case DroneType::DctuROpGZjRKFcMe:
        case DroneType::BHjzymzgwTEeueKI:
        case DroneType::zbrTIBekxqBMpinl:
        case DroneType::MGSJdYCYeEyILnqX:
        case DroneType::LnJMmgAzSGznmAhd:
        case DroneType::jzdPaWJwlLoyHJVW:
        case DroneType::eXWvzQSyEIakaYNBE:
        case DroneType::KlVwDfaUzMhdaFSv:
        case DroneType::iQijNLoVOFIwVzDH:
        case DroneType::BtJYsbsfVdQSFzkL:
        case DroneType::VgtTrHQftoHtijqi:
        {
            if (data_source.is_up) {
                output->set_has_uplinkSignalQuality(true);
                output->set_uplinkSignalQuality(data_source.signal_percent);
            } else {
                output->set_has_downlinkSignalQuality(true);
                output->set_downlinkSignalQuality(data_source.signal_percent);
            }
            
            return true;
        }
        case DroneType::mbQylgbZZfSXWFrl:
        {
            if (data_source.is_up) {
                output->set_has_uplinkSignalQuality(true);
                output->set_uplinkSignalQuality(data_source.signal_percent);
            } else {
                output->set_has_downlinkSignalQuality(true);
                int32_t down_percent = (int32_t)(101 - sqrt(pow(10.0, ((data_source.signal_percent - 53) / 10.0))));
                output->set_downlinkSignalQuality(down_percent);
            }
            
            return true;
        }
            // OcuSync
        default:
        {
            uint8_t signalPercent = data_source.signal_percent;
            uint8_t outputSignalPercent = 0;
            if (signalPercent <= 6) {
                outputSignalPercent = 0;
            } else if (signalPercent <= 16) {
                outputSignalPercent = 19/9*(signalPercent-7)+1;
            } else if (signalPercent <= 30) {
                outputSignalPercent = 19/13*(signalPercent-17)+21;
            } else if (signalPercent <= 55) {
                outputSignalPercent = 19/24*(signalPercent-31)+41;
            } else if (signalPercent <= 70) {
                outputSignalPercent = 19/14*(signalPercent-56)+61;
            } else if (signalPercent <= 90) {
                outputSignalPercent = signalPercent+10;
            } else {
                outputSignalPercent = 100;
            }
            
            if (data_source.is_up) {
                output->set_has_uplinkSignalQuality(true);
                output->set_uplinkSignalQuality(outputSignalPercent);
            } else {
                output->set_has_downlinkSignalQuality(true);
                output->set_downlinkSignalQuality(outputSignalPercent);
            }
            
            return true;
        }
    }
    
    return false;
}

static bool FillOSDData(const dji_fc_osd_push& data_source,
                        std::shared_ptr<AirLinkStateImp>& output) {
    
    output->set_drone_type((DroneType)data_source.droneType);
    
    return true;
}

//MARK: - Public

bool DJIFR::standardization::Filler(std::shared_ptr<AirLinkStateImp>& output,
                                    FlightRecordDataType data_type,
                                    uint8_t *buffer,
                                    uint64_t length) {
    switch (data_type) {
        case AgricultureOFDMRadioSignalPush:
        {
            dji_ofdm_radio_signal_push data_source = {0};
            uint64_t data_length = std::min(length, (uint64_t)sizeof(data_source));
            if (data_length <= 0) {
                return false;
            }
            
            memcpy(&data_source, buffer, data_length);
            return FillOFDMRadioSignalPush(data_source, output);
        }
            break;
        case OSDFlightRecordDataType:
        {
            dji_fc_osd_push data_source = {0};
            uint64_t data_length = std::min(length, (uint64_t)sizeof(data_source));
            if (data_length <= 0) {
                return false;
            }
            
            memcpy(&data_source, buffer, data_length);
            return FillOSDData(data_source, output);
        }
            break;
            
        default:
            break;
    }
    
    return false;
}
