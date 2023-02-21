//
//  fr_standardization_image_model.hpp
//  FlightRecordStandardization
//
//  Copyright © 2019 DJISDK. All rights reserved.
//

#ifndef fr_standardization_image_model_hpp
#define fr_standardization_image_model_hpp

#include <stdio.h>
#include "fr_standardization_common.hpp"
#include "fr_standardization_image_interface.h"

namespace DJIFR {
    namespace standardization {
        //MARK: - ImageDataImp
        
        class ImageDataImp : public ImageData {
        public:
            ImageDataImp();
            virtual ~ImageDataImp();
            
            LocationCoordinate2DSharedPtr coordinate() const override;
            void set_coordinate(const LocationCoordinate2DSharedPtr& coordinate);
            
            BufferSharedPtr previewImage() const override;
            void set_previewImage(const BufferSharedPtr& image);
            
            BufferSharedPtr thumbnail() const override;
            void set_thumbnail(const BufferSharedPtr& image);
            
        private:
            LocationCoordinate2DSharedPtr coordinate_;
            
            BufferSharedPtr preview_image_;
            
            BufferSharedPtr thumbnail_;
        };
    }
}

#endif /* fr_standardization_image_model_hpp */
