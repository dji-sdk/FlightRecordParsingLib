//
//  DJIFRProtoParser.hpp
//  FlightRecordStandardizationCpp
//
//  Copyright © 2019 DJISDK. All rights reserved.
//

#ifndef DJIFRProtoParser_hpp
#define DJIFRProtoParser_hpp

#include <stdio.h>
#include "FRSummaryModelProto.pb.h"
#include "FRRCModelProto.pb.h"
#include "FRMobileRCModelProto.pb.h"
#include "FRImageModelProto.pb.h"
#include "FRGimbalModelProto.pb.h"
#include "FRFrameTimeModelProto.pb.h"
#include "FRFlightControllerModelProto.pb.h"
#include "FRCommonModelProto.pb.h"
#include "FRCameraStateProto.pb.h"
#include "FRBatteryStateProto.pb.h"
#include "Error.pb.h"
#include "fr_standardization_server_creater.h"

namespace DJIFRProto {
    namespace Standard {
        class Parser {
        public:
            //MARK: - Config
            
            Parser();
            ~Parser();
            
            //MARK: - Base
            
            /// load or reload the new file.
            /// @param file_path the file path.
            ///
            /// @return SDK error code.
            FRError load(const std::string& file_path);
            
            /// Request the file key from DJIService
            /// @param sdk_key Your SDK key
            /// @param callback The pullback tells if the parsing was successful. If successful, you can start fetching data from the file.
            ///
            /// @return SDK error code.
            FRError startRequestParser(const std::string& sdk_key, const DJIFR::standardization::RequestCallback &callback);
            
            /// Gets the summary information of the flight record file.
            ///
            /// @Warning Call `startParser` before calling this method.
            ///
            /// @Note For example, to get the total distance of a single flight, the total time, the information of the aircraft components and the app version, etc.
            ///
            /// @param output an instance of `SummaryInformation`.
            ///
            /// @return SDK error code.
            FRError summaryInformation(std::shared_ptr<SummaryInformation> *output);
            
            /// Gets the image list of a single flight.
            /// Photos will only be collected using DJI Fly, DJI GO3, DJI GO4. Collect up to 4 graphs at random.
            /// When uploading resolution, please be aware that 
            ///
            /// @Note The `ImageDataSharedPtr` stored the thumbnail, preview image data and the location where to take the picture.
            ///
            /// @param output an instance of the `ImageData` list.
            ///
            /// @return SDK error code.
            FRError images(std::shared_ptr<ImageDatas> *output);
            
            /// Get frame time list.
            /// Use frame time to play back the flight process.
            ///
            /// @Warning Frame time may not be continuous. Due to the broken chain of the aircraft or the crash of the app.
            ///
            /// @param output an instance of the `FrameTimeState` list.
            ///
            /// @return SDK error code.
            FRError frame_time_states(std::shared_ptr<FrameTimeStates> *output);
            
            //MARK: - Server
            
            /// Reparse all the frame time to the member variable `frame_time_list_` with the filter map.
            /// @param filter The key of the map is what data types need to be found. The value of the map refers to whether this data type is required. Empty map table represents all data types required.
            FRError filterFrameTimeList(std::map<FlightRecordDataType, bool> filter);
            
        private:
            // the internal parser
            std::shared_ptr<DJIFR::standardization::ServerParser> parser_;
        };
    }
}

#endif /* DJIFRProtoParser_hpp */
