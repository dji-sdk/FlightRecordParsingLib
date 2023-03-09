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
        enum class CameraMode {
            /// Capture mode. In this mode, the user can capture pictures.
            ShootPhoto = 0,
            /// Record mode. In this mode, the user can record videos.
            RecordVideo = 1,
            /// Playback mode. In this mode, the user can preview photos and videos, and can
            /// delete files. It is supported by Phantom 3 Professional camera, X3, X5 and X5R
            /// cameras on aircraft and Phantom 4 camera. Playback mode is not supported by Z30,
            /// X5S, X4S, Phantom 4 Pro, Mavic Pro, Phantom 3 Standard, Phantom 3 Advanced,
            /// Phantom 3 4K and Osmo series.
            Playback = 2,
            /// In this mode, the user can download media to the Mobile Device. Not supported by
            /// X5 camera nor X5R camera while mounted on aircraft.
            MediaDownload = 3,
            /// In this mode, live stream resolution and frame rate will be 1080i50 (PAL) or
            /// 720p60 (NTSC). In this mode videos can be recorded. Still photos can also be
            /// taken only when video is recording. The only way to exit broadcast mode is to
            /// change modes to `DJICameraModeRecordVideo`. Only supported by Inspire 2.
            Broadcast = 4,
            /// The camera work mode is unknown.
            Unknown = 0xFF,
        };
    
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
            
            /// The current mode of the camera.
            virtual CameraMode mode() const = 0;
        };
    
        using CameraStateSharedPtr = std::shared_ptr<CameraState>;
    }
}

#endif /* fr_standardization_camera_interface_h */
