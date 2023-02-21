cmake_minimum_required(VERSION 3.4.1)

set(current_project_name "FRSample")
project("${current_project_name}")

set(all_project_root_path "${CMAKE_CURRENT_SOURCE_DIR}/../../../")

add_executable(${current_project_name} main.cc)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} --std=c++11 -O3 -fPIC")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} --std=c++11 -O0")

# Pour in the File Filter traversal tool.
include(${all_project_root_path}/third-party/cmake/common/file/FileFilter.cmake)

file(GLOB_RECURSE StandardizationCppHeader ${all_project_root_path}/dji-flightrecord-kit/source/FlightRecordStandardizationCpp/*.hpp ${all_project_root_path}/dji-flightrecord-kit/source/FlightRecordStandardizationCpp/*.h ${all_project_root_path}/dji-flightrecord-kit/source/FlightRecordStandardization/*.h)
include_file_directory(StandardizationCppHeader)

add_subdirectory(${all_project_root_path}/dji-flightrecord-kit/source/FlightRecordStandardizationCpp StandardizationCppBuild)
target_link_libraries(${current_project_name} FlightRecordStandardizationCpp)