cmake_minimum_required(VERSION 3.4.1)

project(tommath)

include_directories(${CMAKE_CURRENT_SOURCE_DIR})

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

file(GLOB_RECURSE All_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp ${CMAKE_CURRENT_SOURCE_DIR}/*.c ${CMAKE_CURRENT_SOURCE_DIR}/*.h ${CMAKE_CURRENT_SOURCE_DIR}/*.ipp ${CMAKE_CURRENT_SOURCE_DIR}/*.h)
list(FILTER All_SOURCES EXCLUDE REGEX "demo/*.*")
list(FILTER All_SOURCES EXCLUDE REGEX "etc/*.*")
list(FILTER All_SOURCES EXCLUDE REGEX "mtest/*.*")
list(FILTER All_SOURCES EXCLUDE REGEX "pre_gen/*.*")

# 生成library
add_library(tommath STATIC ${All_SOURCES})