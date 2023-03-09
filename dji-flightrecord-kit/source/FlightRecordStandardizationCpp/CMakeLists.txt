cmake_minimum_required(VERSION 3.4.1)

set(current_project_name "FlightRecordStandardizationCpp")
project(${current_project_name})

# root directory
set(all_project_root_path "${CMAKE_CURRENT_SOURCE_DIR}/../../../")

# Pour in the File Filter traversal tool.
include(${all_project_root_path}/third-party/cmake/common/file/FileFilter.cmake)

# Added source files
file(GLOB_RECURSE All_SOURCES *.h *.hpp *.cpp *.cc)

# Adding file paths and header files
source_group_by_dir(All_SOURCES ${CMAKE_CURRENT_SOURCE_DIR})
include_file_directory(All_SOURCES)

if(ENABLE_SHARED_LIB)
    Message(STATUS "✅ Build Shared Lib in ${current_project_name}")
    add_library(${current_project_name} SHARED ${All_SOURCES})
else()
    Message(STATUS "✅ Build Static Lib in ${current_project_name}")
    add_library(${current_project_name} STATIC ${All_SOURCES})
endif(ENABLE_SHARED_LIB)

# Special configurations for different platforms
string(TOLOWER ${platform} platformLowerStr)
Message(STATUS "✅ start ${platform} operation in ${current_project_name}")

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} --std=c++11 -O3 -fPIC")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} --std=c++11 -O0")

if(${platformLowerStr} MATCHES "mac")

elseif(${platformLowerStr} MATCHES "ubuntu")

endif()

# Folder path to introduce FlightRecordStandardizationCpp
target_include_directories(
    ${current_project_name}
    PUBLIC
    "${CMAKE_CURRENT_SOURCE_DIR}/../FlightRecordStandardizationCpp"
    "${all_project_root_path}/dji-flightrecordengine/source/"
    "${all_project_root_path}/third-party/source/protobuf-3.21.12/src"
)

# include FlightRecordStandardization Header
file(GLOB_RECURSE StandardizationHeader ${all_project_root_path}/dji-flightrecord-kit/source/FlightRecordStandardization/*.h)
include_file_directory(StandardizationHeader)

# Adding repositories
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/../FlightRecordStandardization StandardizationBuild)
target_link_libraries(${current_project_name} FlightRecordStandardization)

add_subdirectory(${all_project_root_path}/third-party/source/protobuf-3.21.12/src standardProtobufBuild)
target_link_libraries(${current_project_name} DJIProtobuf)

