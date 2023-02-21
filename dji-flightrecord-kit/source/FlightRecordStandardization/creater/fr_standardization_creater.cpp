//
//  fr_standardization_creater.cpp
//  FlightRecordStandardization
//
//  Copyright © 2019 DJISDK. All rights reserved.
//

#include "fr_standardization_creater.hpp"
#include "fr_standardization_parser_Imp.hpp"
#include "fr_standardization_server_creater.h"
#include <Utils/keychain/flight_record_decrypt_keychain.h>

using namespace DJIFR::standardization;
using namespace DJI::FlightRecord;

ParserSharedPtr DJIFR::standardization::CreateParser() {
    auto parser = std::make_shared<ParserImp>();
    
    return parser;
}

ServerParserSharedPtr DJIFR::standardization::CreateServerParser() {
    auto parser = std::make_shared<ParserImp>();
    
    return parser;
}
