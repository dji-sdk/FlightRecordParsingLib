//
//  fr_standardization_server_creater.h
//  FlightRecordStandardizationCpp
//
//  Copyright © 2019 DJISDK. All rights reserved.
//

#ifndef fr_standardization_server_creater_h
#define fr_standardization_server_creater_h

#include <stdio.h>
#include "fr_server_standardization_parser.h"
#include "fr_standardization_common_interface.h"

namespace DJIFR {
    namespace standardization {
        ServerParserSharedPtr CreateServerParser();
    }
}

#endif /* fr_standardization_server_creater_h */
