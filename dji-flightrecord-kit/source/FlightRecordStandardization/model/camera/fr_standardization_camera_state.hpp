//
//  fr_standardization_camera_state.hpp
//  FlightRecordStandardization
//
//  Copyright © 2019 DJISDK. All rights reserved.
//

#ifndef fr_standardization_camera_state_hpp
#define fr_standardization_camera_state_hpp

#include <stdio.h>
#include <memory>
#include "fr_standardization_camera_interface.h"

namespace DJIFR {
    namespace standardization {
        class CameraStateImp : public CameraState {
        public:
            CameraStateImp();
            virtual ~CameraStateImp();
            
            std::shared_ptr<CameraStateImp> clone();
            
            //MARK: - Property Set & Get
            
            /// Returns the component index. Index is zero based.
            int index() const override;
            void set_index(int index);
            
            /// `YES` if the camera is recording video.
            bool isRecording() const override;
            void set_isRecording(bool isRecording);
            
            /// `YES` when the camera is performing any photo capture in any `DJICameraShootPhotoMode`. Between photo capture in interval and time lapse mode, this property will be `NO`. The camera is shooting a single photo.
            bool isShootingSinglePhoto() const override;
            void set_isShootingSinglePhoto(bool isShootingSinglePhoto);
            
            /// `YES` if the SD card is inserted in the camera. It is always `YES` when it is the internal storage.
            bool isInserted() const override;
            void set_isInserted(bool isInserted);
            
            /// `YES` if the storage is initializing. Note that if the storage is initializing,
            /// the value for other properties in `DJICameraStorageState` is undefined.
            bool isInitializing() const override;
            void set_isInitializing(bool isInitializing);
            
            /// `YES` if there is an error with the storage.
            bool hasError() const override;
            void set_hasError(bool hasError);
            
            /// `YES` if the SD card is verified as genuine. The SD card is not valid if it is fake,
            /// which can be a problem if the SD card was purchased by a non-reputable retailer.
            /// It is always `YES` when it is the internal storage.
            bool isVerified() const override;
            void set_isVerified(bool isVerified);
            
            /// `YES` if the storage cannot save any more media.
            bool isFull() const override;
            void set_isFull(bool isFull);
            
            /// `YES` if the storage is formatted.
            bool isFormatted() const override;
            void set_isFormatted(bool isFormatted);
            
            /// `YES` if the storage is formatting.
            bool isFormatting() const override;
            void set_isFormatting(bool isFormatting);
            
            /// `YES` if the storage filesystem format is invalid.
            bool isInvalidFormat() const override;
            void set_isInvalidFormat(bool isInvalidFormat);
            
            /// `YES` if the storage is read-only.
            bool isReadOnly() const override;
            void set_isReadOnly(bool isReadOnly);
            
            /// Total space in Megabytes（MB）available on the storage.
            uint32_t totalSpaceInMB() const override;
            void set_totalSpaceInMB(uint32_t totalSpaceInMB);
            
            /// Remaining space in Megabytes（MB）on the storage.
            uint32_t remainingSpaceInMB() const override;
            void set_remainingSpaceInMB(uint32_t remainingSpaceInMB);
            
            /// Returns the number of pictures that can be taken with the remaining space available on the storage.
            uint32_t availableCaptureCount() const override;
            void set_availableCaptureCount(uint32_t availableCaptureCount);
            
            /// Returns the number of seconds available for recording with the remaining space available on the storage.
            uint32_t availableRecordingTimeInSeconds() const override;
            void set_availableRecordingTimeInSeconds(uint32_t availableRecordingTimeInSeconds);
            
            /// The current mode of the camera.
            CameraMode mode() const override;
            void set_mode(CameraMode mode);
            
        private:
            int index_ = 0;
            
            bool isRecording_ = false;
            
            bool isShootingSinglePhoto_ = false;
            
            bool isInserted_ = false;
            
            bool isInitializing_ = false;
            
            bool hasError_ = false;
            
            bool isVerified_ = false;
            
            bool isFull_ = false;
            
            bool isFormatted_ = false;
            
            bool isFormatting_ = false;
            
            bool isInvalidFormat_ = false;
            
            bool isReadOnly_ = false;
            
            uint32_t totalSpaceInMB_ = 0;
            
            uint32_t remainingSpaceInMB_ = 0;
            
            uint32_t availableCaptureCount_ = 0;
            
            uint32_t availableRecordingTimeInSeconds_ = 0;
            
            CameraMode mode_ = CameraMode::Unknown;
        };
    }
}

#endif /* fr_standardization_camera_state_hpp */
