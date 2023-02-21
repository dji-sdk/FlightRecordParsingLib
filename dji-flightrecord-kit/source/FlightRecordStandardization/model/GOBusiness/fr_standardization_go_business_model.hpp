//
//  fr_standardization_go_business_model.hpp
//  FlightRecordStandardization
//
//  Copyright © 2020 DJISDK. All rights reserved.
//

#ifndef fr_standardization_go_business_model_hpp
#define fr_standardization_go_business_model_hpp

#include <stdio.h>
#include "fr_standardization_go_business_interface.h"

namespace DJIFR {
    namespace standardization {
        //MARK: - GOBusinessDataImp
        class GOBusinessDataImp : public GOBusinessData {
        public:
            GOBusinessDataImp();
            virtual ~GOBusinessDataImp();
            
            /// Version information, currently available in two versions
            /// 0: Flight record version 11 and below, filled with TIPS, or WARNING
            /// 1: Flight record version 12 and above
            uint8_t version() const override;
            void set_version(uint8_t version);
            
            /// Strings stored for version 11 and below, indicating a prompt for TIPS.
            std::string tips() const override;
            void set_tips(const std::string& tips);
            
            /// Strings stored for version 111 and below, indicating a prompt for WARNING
            std::string warning() const override;
            void set_warning(const std::string& warning);
            
            /// Strings stored for version 11 and below, indicating a prompt for a seriouse warning
            std::string seriousWarning() const override;
            void set_seriousWarning(const std::string& seriousWarning);
            
            /// The version 12 data is stored as a Protobuf data
            /// Requires upper level processing using Protobuf parsing
            BufferSharedPtr goBusinessData() const override;
            void set_goBusinessData(const BufferSharedPtr& goBusinessData);
            
        private:
            uint8_t version_ = 0;
            
            std::string tips_;
            
            std::string warning_;
            
            std::string seriousWarning_;
            
            BufferSharedPtr goBusinessData_ = nullptr;
        };
    }
}

#endif /* fr_standardization_go_business_model_hpp */
