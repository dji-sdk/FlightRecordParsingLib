cmake_minimum_required(VERSION 3.4.1)

set(current_project_name "DJIProtobuf")
project(${current_project_name})

# 根目录
set(all_project_root_path "${CMAKE_CURRENT_SOURCE_DIR}/../../../../")

# 倒入File Filter遍历工具
include(${all_project_root_path}/third-party/cmake/common/file/FileFilter.cmake)

# 添加 DJIProtobuf 的源文件
file(GLOB_RECURSE All_SOURCES google/*.h google/*.cc)
file(GLOB_RECURSE header_list google/*.h)

# 添加 DJIProtobuf 动态库
source_group_by_dir(All_SOURCES ${CMAKE_CURRENT_SOURCE_DIR})
if (ENABLE_SHARED_LIB)
    Message("Build Shared Lib")
    add_library(DJIProtobuf SHARED ${All_SOURCES})
else()
    Message("Build Static Lib")
    add_library(DJIProtobuf STATIC ${All_SOURCES})
endif(ENABLE_SHARED_LIB)

# 需要添加的header search
target_include_directories(
	${current_project_name}
	PUBLIC
	"${CMAKE_CURRENT_SOURCE_DIR}"
)

set(CMAKE_DEBUG_POSTFIX "")

# 添加对应的宏
add_definitions(-DHAVE_PTHREAD)

# 不同平台的特殊配置
string(TOLOWER ${platform} platformLowerStr)
Message(STATUS "✅ start ${platform} operation in ${current_project_name}")

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} --std=c++11 -O3 -fPIC")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} --std=c++11 -O0")


