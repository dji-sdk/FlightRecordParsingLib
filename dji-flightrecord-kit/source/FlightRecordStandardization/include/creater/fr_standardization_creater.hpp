//
//  fr_standardization_creater.hpp
//  FlightRecordStandardization
//
//  Copyright © 2019 DJISDK. All rights reserved.
//

#ifndef fr_standardization_creater_hpp
#define fr_standardization_creater_hpp

#include <stdio.h>
#include "fr_standardization_parser.h"

namespace DJIFR {
    namespace standardization {
        ParserSharedPtr CreateParser();
    }
}

#endif /* fr_standardization_creater_hpp */
