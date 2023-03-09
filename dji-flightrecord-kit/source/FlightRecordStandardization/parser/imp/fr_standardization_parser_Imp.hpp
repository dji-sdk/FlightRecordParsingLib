//
//  fr_standardization_parser_Imp.hpp
//  FlightRecordStandardization
//
//  Copyright © 2019 DJISDK. All rights reserved.
//

#ifndef fr_standardization_parser_Imp_hpp
#define fr_standardization_parser_Imp_hpp

#include <stdio.h>
#include "fr_server_standardization_parser.h"
#include <Parser/FlightRecordParserEngine.h>
#include <string>
#include <model/protocol/dji_product_type.h>

namespace DJIFR {
    namespace standardization {
        class FrameTimeStateImp;
        class SummaryInformationImp;
        class ImageDataImp;
        class ComponentInformationImp;
    
        class ParserImp : public ServerParser {
        public:
            ParserImp();
            virtual ~ParserImp();
            
            //MARK: - Parser Public Method
            
            /// load or reload the new file.
            /// @param file_path the file path.
            ///
            /// @return SDK error code.
            SDKError load(const std::string& file_path) override;
            
            /// Request the file key from DJIService
            /// @param sdk_key Your SDK key
            /// @param callback The pullback tells if the parsing was successful. If successful, you can start fetching data from the file.
            ///
            /// @return SDK error code.
            SDKError startRequestParser(const std::string& sdk_key, const RequestCallback &callback) override;
            
            /// Gets the summary information of the flight record file.
            ///
            /// @Warning Call `load` before calling this method.
            ///
            /// @Note For example, to get the total distance of a single flight, the total time, the information of the aircraft components and the app version, etc.
            ///
            /// @param output an instance of `SummaryInformation`.
            ///
            /// @return SDK error code.
            SDKError summaryInformation(SummaryInformationSharedPtr* output) override;
            
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
            SDKError images(std::vector<ImageDataSharedPtr>* output) override;
            
            /// Get frame time list.
            /// Use frame time to play back the flight process. Not a thread-safe method.
            ///
            /// @Warning Frame time may not be continuous. Due to the broken chain of the aircraft or the crash of the app.
            /// @Note This operation will take some time when the first time calls, you can choose to put in the sub-thread operation.
            ///
            /// @param output an instance of the `FrameTimeState` list.
            ///
            /// @return SDK error code.
            SDKError frame_time_list(std::vector<FrameTimeStateSharedPtr>* output) override;
            
            /// Get the server frame time list.
            /// Use frame time to play back the flight process. Not a thread-safe method.
            ///
            /// @Warning Frame time may not be continuous. Due to the broken chain of the aircraft or the crash of the app.
            /// @Note This operation will take some time when the first time calls, you can choose to put in the sub-thread operation.
            ///
            /// @param output an instance of the `FrameTimeState` list.
            ///
            /// @return SDK error code.
            SDKError server_frame_time_list(std::vector<ServerFrameTimeStateSharedPtr>* output) override;
                                 
             //MARK: - Frame Time
             
             /// Parser all the frame time to the member variable `frame_time_list_`.
             /// @param filter The key of the map is what data types need to be found. The value of the map refers to whether this data type is required. Empty map table represents all data types required.
             SDKError filterFrameTimeList(std::map<FlightRecordDataType, bool> filter) override;
            
        protected:
            
            //MARK: - Converter
            
            SDKError convertParserResultToPublic(DJI::FlightRecord::ParserResult result_code);
            
            //MARK: - Image
            
            SDKError parserImageData();
            
            //MARK: - Summary
            
            SDKError parserSummary();
            
            void fillSummary(FlightRecordDataType data_type,
                             uint8_t *buffer,
                             uint64_t length);
            
            /// To recalculate the information related to Summary, currently the following data is calculated:
            /// 1. maxHeight
            /// 2. maxHorizontalSpeed
            /// 3. maxVirticalSpeed
            /// 4. startCoordinate
            /// 5. totalDistance
            void recalculateSummary();
            
            std::shared_ptr<ComponentInformationImp> getSummaryValidCameraComponent(int index);
            
            std::shared_ptr<ComponentInformationImp> getSummaryValidBatteryComponent(int index);
            
            std::shared_ptr<ComponentInformationImp> getSummaryValidGimbalComponent(int index);
            
            std::shared_ptr<ComponentInformationImp> getSummaryValidFCComponent();
            
            std::shared_ptr<ComponentInformationImp> getSummaryValidRCComponent();
            
            //MARK: - Filler
            
            bool fillRCHardwareState(FlightRecordDataType data_type,
                                     uint8_t *buffer,
                                     uint64_t length,
                                     std::shared_ptr<FrameTimeStateImp>& output);
            
            bool fillMobileRC(FlightRecordDataType data_type,
                              uint8_t *buffer,
                              uint64_t length,
                              std::shared_ptr<FrameTimeStateImp>& output);
            
            bool fillGimbalState(FlightRecordDataType data_type,
                                 uint8_t *buffer,
                                 uint64_t length,
                                 std::shared_ptr<FrameTimeStateImp>& output);
            
            bool fillFlightController(FlightRecordDataType data_type,
                                      uint8_t *buffer,
                                      uint64_t length,
                                      std::shared_ptr<FrameTimeStateImp>& output);
            
            bool fillCameraState(FlightRecordDataType data_type,
                                 uint8_t *buffer,
                                 uint64_t length,
                                 std::shared_ptr<FrameTimeStateImp>& output);
            
            bool fillBatteryState(FlightRecordDataType data_type,
                                  uint8_t *buffer,
                                  uint64_t length,
                                  std::shared_ptr<FrameTimeStateImp>& output);
            
            bool fillAirlinkState(FlightRecordDataType data_type,
                                  uint8_t *buffer,
                                  uint64_t length,
                                  std::shared_ptr<FrameTimeStateImp>& output);
            
            bool fillGOBusiness(FlightRecordDataType data_type,
                                uint8_t *buffer,
                                uint64_t length,
                                std::shared_ptr<FrameTimeStateImp>& output);
            
            bool fillMobileDevice(FlightRecordDataType data_type,
                                  uint8_t *buffer,
                                  uint64_t length,
                                  std::shared_ptr<FrameTimeStateImp>& output);
            
            bool fillVisionData(FlightRecordDataType data_type,
                                uint8_t *buffer,
                                uint64_t length,
                                std::shared_ptr<FrameTimeStateImp>& output);
            
            /// Find the frame time with valid GPS coordinates from the given index forward.
            /// @param index Where do you start? Go ahead and find the plane.
            /// @param final_index If an object pointer is returned, the index is found here.
            std::shared_ptr<FrameTimeStateImp> findValidAircraftLocaion(int index, int *final_index);
            
        private:
            DJI::FlightRecord::FlightRecordParserEngineSharedPtr parser_;
            
            std::shared_ptr<SummaryInformationImp> summary_info_;
            
            /// Since there may be a file exceptionally closed, it is not possible to get an info to know if the info is valid or not, so it is possible to recreate the info situation here.
            bool is_recalculate_info_ = false;
            
            std::vector<std::shared_ptr<ImageDataImp>> images_;
            
            std::vector<std::shared_ptr<FrameTimeStateImp>> frame_time_list_;
            
            DJI::FlightRecord::ProductType product_type_;
            
            DJI::FlightRecord::DroneType drone_type_ = DJI::FlightRecord::DroneType::Unknown;
        };
    }
}

#endif /* fr_standardization_parser_Imp_hpp */
