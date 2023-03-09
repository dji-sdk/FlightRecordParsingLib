//
//  fr_server_standardization_parser.h
//  FlightRecordStandardization
//
//  Copyright © 2019 DJISDK. All rights reserved.
//

#ifndef fr_server_standardization_parser_h
#define fr_server_standardization_parser_h

#include <functional>
#include "fr_standardization_parser.h"
#include "FlightRecordProtocolEnum.h"
#include <Utils/featurePoint/flight_record_feature_point_enum.h>
#include "fr_server_standardization_frametime_interface.h"

namespace DJIFR {
    namespace standardization {
        typedef std::function<void (ServerError error_code, const std::string& error_description)> RequestCallback;
    
        /// This is an internal interface for DJI Server or the LDM User.
        class ServerParser : public Parser {
        public:
            
            /// Request the file key from DJIService
            /// @param sdk_key Your SDK key
            /// @param callback The pullback tells if the parsing was successful. If successful, you can start fetching data from the file.
            ///
            /// @return SDK error code.
            virtual SDKError startRequestParser(const std::string& sdk_key, const RequestCallback &callback) = 0;
            
            /// Reparse all the frame time to the member variable `frame_time_list_` with the filter map.
            /// @param filter The key of the map is what data types need to be found. The value of the map refers to whether this data type is required. Empty map table represents all data types required.
            virtual SDKError filterFrameTimeList(std::map<FlightRecordDataType, bool> filter) = 0;
            
            /// Get the server frame time list.
            /// Use frame time to play back the flight process. Not a thread-safe method.
            ///
            /// @Warning Frame time may not be continuous. Due to the broken chain of the aircraft or the crash of the app.
            /// @Note This operation will take some time when the first time calls, you can choose to put in the sub-thread operation.
            ///
            /// @param output an instance of the `FrameTimeState` list.
            ///
            /// @return SDK error code.
            virtual SDKError server_frame_time_list(std::vector<ServerFrameTimeStateSharedPtr>* output) = 0;
        };
    
        using ServerParserSharedPtr = std::shared_ptr<ServerParser>;
    }
}

#endif /* fr_server_standardization_parser_h */
