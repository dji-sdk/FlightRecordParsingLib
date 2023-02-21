//
//  main.c
//  FlightRecordConversionServiceExecutable
//
//

#include <stdio.h>
#include "DJIFRProtoParser.hpp"
#include <assert.h>
#include <thread>
#include <unistd.h>

int main(int argc, char *argv[]) {
    std::string file_path("The flight record file path");
    auto parser = std::make_shared<DJIFRProto::Standard::Parser>();
    auto result = parser->load(file_path);
    assert(result == DJIFRProto::Standard::Success);
    
    result = parser->startRequestParser("The SDK Key", [&parser](DJIFR::standardization::ServerError error_code, const std::string& error_description) {
        if (error_code == DJIFR::standardization::ServerError::Success) {
            std::shared_ptr<DJIFRProto::Standard::SummaryInformation> info = nullptr;
            auto result = parser->summaryInformation(&info);
            assert(result == DJIFRProto::Standard::Success);
            
            std::shared_ptr<DJIFRProto::Standard::FrameTimeStates> frame_time_list;
            result = parser->frame_time_states(&frame_time_list);
            assert(result == DJIFRProto::Standard::Success);
        } else {
            printf("error code: %d decription: %s\n", error_code, error_description.c_str());
        }
    });
    assert(result == DJIFRProto::Standard::Success);
    
    return 0;
}
