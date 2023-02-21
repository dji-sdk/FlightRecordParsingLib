//
//  fr_standardization_image_interface.h
//  FlightRecordStandardization
//
//  Copyright © 2019 DJISDK. All rights reserved.
//

#ifndef fr_standardization_image_interface_h
#define fr_standardization_image_interface_h

#include <stdio.h>
#include <memory>
#include "fr_standardization_common_interface.h"

namespace DJIFR {
    namespace standardization {
        //MARK: - ImageData
        
        class ImageData {
        public:
            
            virtual LocationCoordinate2DSharedPtr coordinate() const = 0;
            
            virtual BufferSharedPtr previewImage() const = 0;
            
            virtual BufferSharedPtr thumbnail() const = 0;
        };
    
        using ImageDataSharedPtr = std::shared_ptr<ImageData>;
    }
}

#endif /* fr_standardization_image_interface_h */
