//
//  fr_standardization_go_business_interface.h
//  FlightRecordStandardization
//
//  Copyright © 2020 DJISDK. All rights reserved.
//

#ifndef fr_standardization_go_business_interface_h
#define fr_standardization_go_business_interface_h

#include <stdio.h>
#include <vector>
#include <memory>
#include "fr_standardization_common_interface.h"
#include <string>

namespace DJIFR {
    namespace standardization {
        //MARK: - GOBusinessData
        class GOBusinessData {
        public:
            /// Version information, currently available in two versions
            /// 0: Flight record version 11 and below, filled with TIPS, or WARNING
            /// 1: Flight record version 12 and above
            virtual uint8_t version() const = 0;
            
            /// Strings stored for version 11 and below, indicating a prompt for TIPS.
            virtual std::string tips() const = 0;
            
            /// Strings stored for version 111 and below, indicating a prompt for WARNING
            virtual std::string warning() const = 0;
            
            /// Strings stored for version 11 and below, indicating a prompt for a seriouse warning
            virtual std::string seriousWarning() const = 0;
            
            /// The version 12 data is stored as a Protobuf data
            /// Requires upper level processing using Protobuf parsing
            virtual BufferSharedPtr goBusinessData() const = 0;
        };
    
        using GOBusinessDataSharedPtr = std::shared_ptr<GOBusinessData>;
    }
}

#endif /* fr_standardization_go_business_interface_h */
