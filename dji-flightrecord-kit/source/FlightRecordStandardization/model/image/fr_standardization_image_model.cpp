//
//  fr_standardization_image_model.cpp
//  FlightRecordStandardization
//
//  Copyright © 2019 DJISDK. All rights reserved.
//

#include "fr_standardization_image_model.hpp"

using namespace DJIFR::standardization;

//MARK: - ImageDataImp

ImageDataImp::ImageDataImp() :
coordinate_(nullptr),
preview_image_(nullptr),
thumbnail_(nullptr) {
    
}

ImageDataImp::~ImageDataImp() {
    preview_image_ = nullptr;
    thumbnail_ = nullptr;
}

LocationCoordinate2DSharedPtr ImageDataImp::coordinate() const {
    return coordinate_;
}

void ImageDataImp::set_coordinate(const LocationCoordinate2DSharedPtr& coordinate) {
    coordinate_ = coordinate;
}

BufferSharedPtr ImageDataImp::previewImage() const {
    return preview_image_;
}

void ImageDataImp::set_previewImage(const BufferSharedPtr& image) {
    preview_image_ = image;
}

BufferSharedPtr ImageDataImp::thumbnail() const {
    return thumbnail_;
}

void ImageDataImp::set_thumbnail(const BufferSharedPtr& image) {
    thumbnail_ = image;
}
