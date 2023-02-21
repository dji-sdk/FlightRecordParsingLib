cmake_minimum_required(VERSION 3.4.1)

project(tomcrypt)

set(CPP_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)
include_directories(${CPP_SOURCE_DIR}/headers)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -v -lgcov")

macro(source_group_by_dir source_files)
	set(sgbd_cur_dir ${CMAKE_CURRENT_SOURCE_DIR}/)
	foreach(sgbd_file ${${source_files}})
		string(REGEX REPLACE ${sgbd_cur_dir} "" sgbd_fpath ${sgbd_file})
		string(REGEX REPLACE "[^/\\\\]+$" "" sgbd_group_name ${sgbd_fpath})
		if(sgbd_group_name)
			string(REPLACE "/"   "\\\\"  sgbd_group_name_normal ${sgbd_group_name})
			source_group(${sgbd_group_name_normal} FILES ${sgbd_file})
		endif(sgbd_group_name)
	endforeach(sgbd_file)
endmacro(source_group_by_dir)

file(GLOB_RECURSE All_SOURCES ${CPP_SOURCE_DIR}/*.cpp ${CPP_SOURCE_DIR}/*.c ${CPP_SOURCE_DIR}/*.h ${CPP_SOURCE_DIR}/*.ipp ${CPP_SOURCE_DIR}/*.h)
list(FILTER All_SOURCES EXCLUDE REGEX "demo/*.*")
list(FILTER All_SOURCES EXCLUDE REGEX "etc/*.*")
list(FILTER All_SOURCES EXCLUDE REGEX "mtest/*.*")

# 生成library
add_library(tomcrypt STATIC ${All_SOURCES})