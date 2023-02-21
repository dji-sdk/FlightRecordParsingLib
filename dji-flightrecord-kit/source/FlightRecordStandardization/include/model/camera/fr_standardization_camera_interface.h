//
//  fr_standardization_camera_interface.h
//  FlightRecordStandardization
//
//  Copyright © 2019 DJISDK. All rights reserved.
//

#ifndef fr_standardization_camera_interface_h
#define fr_standardization_camera_interface_h

#include <stdio.h>
#include <memory>

namespace DJIFR {
    namespace standardization {
        class CameraState {
        public:
            
            //MARK: - Property Set & Get
            
            /// Returns the component index. Index is zero based.
            virtual int index() const = 0;
            
            /// `YES` if the camera is recording video.
            virtual bool isRecording() const = 0;
            
            /// `YES` when the camera is performing any photo capture in any
            /// `DJICameraShootPhotoMode`. Between photo capture in interval and time lapse
            /// mode, this property will be `NO`. The camera is shooting a single photo.
            virtual bool isShootingSinglePhoto() const = 0;
            
            /// `YES` if the SD card is inserted in the camera. It is always `YES` when it is the internal storage.
            virtual bool isInserted() const = 0;
            
            /// `YES` if the storage is initializing. Note that if the storage is initializing,
            /// the value for other properties in `DJICameraStorageState` is undefined.
            virtual bool isInitializing() const = 0;
            
            /// `YES` if there is an error with the storage.
            virtual bool hasError() const = 0;
            
            /// `YES` if the SD card is verified as genuine. The SD card is not valid if it is fake,
            /// which can be a problem if the SD card was purchased by a non-reputable retailer.
            /// It is always `YES` when it is the internal storage.
            virtual bool isVerified() const = 0;
            
            /// `YES` if the storage cannot save any more media.
            virtual bool isFull() const = 0;
            
            /// `YES` if the storage is formatted.
            virtual bool isFormatted() const = 0;
            
            /// `YES` if the storage is formatting.
            virtual bool isFormatting() const = 0;
            
            /// `YES` if the storage filesystem format is invalid.
            virtual bool isInvalidFormat() const = 0;
            
            /// `YES` if the storage is read-only.
            virtual bool isReadOnly() const = 0;
            
            /// Total space in Megabytes（MB）available on the storage.
            virtual uint32_t totalSpaceInMB() const = 0;
            
            /// Remaining space in Megabytes（MB）on the storage.
            virtual uint32_t remainingSpaceInMB() const = 0;
            
            /// Returns the number of pictures that can be taken with the remaining space available on the storage.
            virtual uint32_t availableCaptureCount() const = 0;
            
            /// Returns the number of seconds available for recording with the remaining space available on the storage.
            virtual uint32_t availableRecordingTimeInSeconds() const = 0;
        };
    
        using CameraStateSharedPtr = std::shared_ptr<CameraState>;
    }
}

#endif /* fr_standardization_camera_interface_h */
