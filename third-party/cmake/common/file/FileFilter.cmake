# Please use `include` to add this cmake file at first
# Sample: include(fullpath/FileFilter.cmake)
# ============================= macro function define begin =============================

# add the filter for the file tree.
function(source_group_by_dir source_files source_folder)
    set(sgbd_cur_dir ${source_folder}/)
    foreach(sgbd_file ${${source_files}})
        string(REGEX REPLACE ${sgbd_cur_dir} "" sgbd_fpath ${sgbd_file})
        string(REGEX REPLACE "[^/\\\\]+$" "" sgbd_group_name ${sgbd_fpath})

        if(${enable_log})
            message("🚗 filter file: ${sgbd_fpath}")
        endif()
        
        if(sgbd_group_name)
            string(REPLACE "/"   "\\\\"  sgbd_group_name_normal ${sgbd_group_name})
            source_group(${sgbd_group_name_normal} FILES ${sgbd_file})
        else(sgbd_group_name)
            source_group("\\" FILES ${sgbd_file})
        endif(sgbd_group_name)	
    endforeach(sgbd_file)
endfunction(source_group_by_dir)

# include all the files directory
function(include_file_directory source_files)
    message(${source_files})
    foreach(sgbd_file ${${source_files}})
        string(REGEX REPLACE "[^/\\\\]+$" "" sgbd_group_name ${sgbd_file})

        if(${enable_log})
            message("🚙 add header search path: ${sgbd_fpath}")
        endif()
        
        if(sgbd_group_name)
            message(${sgbd_group_name})
            include_directories(${sgbd_group_name})
        endif(sgbd_group_name)	
    endforeach(sgbd_file)
endfunction(include_file_directory)

# ============================= macro function define end =============================