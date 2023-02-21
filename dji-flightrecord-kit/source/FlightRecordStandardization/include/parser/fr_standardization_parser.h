//
//  fr_standardization_parser.h
//  FlightRecordKitiOS
//
//  Copyright © 2019 DJISDK. All rights reserved.
//

#ifndef fr_standardization_parser_h
#define fr_standardization_parser_h

#include <stdio.h>
#include "fr_standardization_summary_interface.h"
#include "fr_standardization_frametime_interface.h"
#include "fr_standardization_image_interface.h"
#include <vector>
#include "fr_standardization_error_code.h"

namespace DJIFR {
    namespace standardization {
        class Parser {
        public:
            /// load or reload the new file. Not a thread-safe method.
            /// @param file_path the file path.
            ///
            /// @return SDK error code.
            virtual SDKError load(const std::string& file_path) = 0;
            
            /// Gets the summary information of the flight record file. Not a thread-safe method.
            ///
            /// @Warning Call `startParser` before calling this method.
            ///
            /// @Note For example, to get the total distance of a single flight, the total time, the information of the aircraft components and the app version, etc.
            ///
            /// @param output an instance of `SummaryInformation`.
            ///
            /// @return SDK error code.
            virtual SDKError summaryInformation(SummaryInformationSharedPtr* output) = 0;
            
            /// Gets the image list of a single flight.
            /// Photos will only be collected using DJI Fly, DJI GO3, DJI GO4. Collect up to 4 graphs at random.
            /// For DJI Pilot, DJI GSPro or SDK-based third-party apps, this content is empty.
            /// When uploading resolution, please be aware that
            ///
            /// The photos are there for the user to easily distinguish between different flight records as they are viewed.
            /// These images can be viewed on the app's flight logs page or deleted by deleting the flight logs file, which is not automatically uploaded to DJI's servers.
            ///
            /// @Note The `ImageDataSharedPtr` stored the thumbnail, preview image data and the location where to take the picture.
            ///
            /// @param output an instance of the `ImageData` list.
            ///
            /// @return SDK error code.
            virtual SDKError images(std::vector<ImageDataSharedPtr>* output) = 0;
            
            /// Get frame time list.
            /// Use frame time to play back the flight process. Not a thread-safe method.
            ///
            /// @Warning Frame time may not be continuous. Due to the broken chain of the aircraft or the crash of the app.
            /// @Note This operation will take some time when the first time calls, you can choose to put in the sub-thread operation.
            ///
            /// @param output an instance of the `FrameTimeState` list.
            ///
            /// @return SDK error code.
            virtual SDKError frame_time_list(std::vector<FrameTimeStateSharedPtr>* output) = 0;
        };
    
        using ParserSharedPtr = std::shared_ptr<Parser>;
    }
}

#endif /* fr_standardization_parser_h */
