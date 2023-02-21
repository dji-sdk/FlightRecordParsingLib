cmake_minimum_required(VERSION 3.4.1)

set(current_project_name "FlightRecordEngine")
project(${current_project_name})

# root directory
set(all_project_root_path "${CMAKE_CURRENT_SOURCE_DIR}/../../")

# Pour in the File Filter traversal tool.
include(${all_project_root_path}/third-party/cmake/common/file/FileFilter.cmake)
message(${all_project_root_path}/third-party/cmake/common/file/FileFilter.cmake)

# Setting the location of common inventory across platforms
set(THIRD_PARTY_PATH "${all_project_root_path}/third-party")

file(GLOB_RECURSE All_SOURCES *.h *.hpp *.cpp)

source_group_by_dir(All_SOURCES ${CMAKE_CURRENT_SOURCE_DIR})
include_file_directory(All_SOURCES)
if (ENABLE_SHARED_LIB)
    Message("Build Shared Lib")
    add_library(${current_project_name} SHARED ${All_SOURCES})
else()
    Message("Build Static Lib")
    add_library(${current_project_name} STATIC ${All_SOURCES})
endif(ENABLE_SHARED_LIB)

set(root_directory_relative_current "${empty_param}")

set(MarcosArr LTC_PKCS_1 LTM_DESC)
foreach(item ${MarcosArr})
	add_definitions("-D${item}")
endforeach()

target_include_directories(
	${current_project_name}
	PUBLIC 
	"${THIRD_PARTY_PATH}/header/libtomcrypt/include"
	"${CMAKE_CURRENT_SOURCE_DIR}/."
)

string(TOLOWER ${platform} platformLowerStr)
Message(STATUS "✅ start ${platform} operation in ${current_project_name}")

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} --std=c++11 -O3 -fPIC")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} --std=c++11 -O0")

message(${platformLowerStr})
target_link_libraries(${current_project_name} ${THIRD_PARTY_PATH}/build/libtomcrypt/${platformLowerStr}/libtomcrypt.a)
target_link_libraries(${current_project_name} ${THIRD_PARTY_PATH}/build/libtomcrypt/${platformLowerStr}/libtommath.a)
