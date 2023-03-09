cmake_minimum_required(VERSION 3.4.1)

set(current_project_name "FlightRecordStandardization")
project(${current_project_name})

# root directory
set(all_project_root_path "${CMAKE_CURRENT_SOURCE_DIR}/../../../")

# Pour in the File Filter traversal tool.
include(${all_project_root_path}/third-party/cmake/common/file/FileFilter.cmake)

# Added source files
file(GLOB_RECURSE All_SOURCES *.h *.hpp *.cpp)

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

if(${platformLowerStr} STREQUAL "ubuntu")
    target_link_libraries(${current_project_name} pthread)
endif()

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} --std=c++11 -O3 -fPIC")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} --std=c++11 -O0")

# Folder path to introduce FlightRecordEngine
target_include_directories(
    ${current_project_name}
    PUBLIC 
    ${all_project_root_path}/dji-flightrecordengine/source/
    ${all_project_root_path}/third-party/header/libtomcrypt/include
    ${all_project_root_path}/third-party/header/libcurl/include
)

# Introduction of the Engine library
add_subdirectory(${all_project_root_path}/dji-flightrecordengine/source EngineBuild)
target_link_libraries(${current_project_name} FlightRecordEngine)

# Import third party - libcurl/libssl/libcrypto
add_library(libcurl STATIC IMPORTED)
set_target_properties( libcurl PROPERTIES
    IMPORTED_LOCATION ${all_project_root_path}/third-party/build/libcurl/lib/${platformLowerStr}/libcurl.a
    INTERFACE_INCLUDE_DIRECTORIES "${all_project_root_path}/third-party/header/libcurl/include"
)

add_library(libssl STATIC IMPORTED)
set_target_properties( libssl PROPERTIES
    IMPORTED_LOCATION ${all_project_root_path}/third-party/build/libopenssl/lib/${platformLowerStr}/libssl.a
    INTERFACE_INCLUDE_DIRECTORIES "${all_project_root_path}/third-party/header/libopenssl/include"
)

find_package(Threads)
add_library(libcrypto STATIC IMPORTED)
set_target_properties( libcrypto PROPERTIES
    IMPORTED_LOCATION ${all_project_root_path}/third-party/build/libopenssl/lib/${platformLowerStr}/libcrypto.a
    INTERFACE_INCLUDE_DIRECTORIES "${all_project_root_path}/third-party/header/libopenssl/include"
    INTERFACE_LINK_LIBRARIES "Threads::Threads"
)
set(CURLS libcurl libssl libcrypto dl)
target_link_libraries(${current_project_name} ${CURLS})



