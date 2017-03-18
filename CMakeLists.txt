cmake_minimum_required (VERSION 2.6)

project (coding-puzzle)

set(CMAKE_VERBOSE_MAKEFILE ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 -Wall -g3")
include_directories("/usr/include/Catch/include")
include_directories("graph/digraph")

function(get_subdirectories_recursively result current_dir)
    file(GLOB children RELATIVE ${current_dir} ${current_dir}/*)
    set(dirlist "")
    foreach(child ${children})
        if(IS_DIRECTORY ${current_dir}/${child})
            list(APPEND dirlist ${current_dir}/${child})
            get_subdirectories_recursively(subdirs ${current_dir}/${child})
            list(APPEND dirlist ${subdirs})
        endif()
    endforeach()
    set(${result} ${dirlist} PARENT_SCOPE)
endfunction(get_subdirectories_recursively)

function(get_test_files_cpp result dir)
    file(GLOB test_files RELATIVE ${dir} ${dir}/test*.cpp)
    set(${result} ${test_files} PARENT_SCOPE)
endfunction(get_test_files_cpp)

get_subdirectories_recursively(subdirs ${CMAKE_CURRENT_LIST_DIR})
foreach(subdir ${subdirs})
    get_test_files_cpp(test_files_cpp ${subdir})
    foreach(test_file_cpp ${test_files_cpp})
        message("adding target ${subdir}/${test_file_cpp}")
        get_filename_component(test_file ${test_file_cpp} NAME_WE)

        add_executable(${test_file} ${subdir}/${test_file_cpp})
        set(run_target run_${test_file})
        add_custom_target(${run_target} COMMAND "./${test_file}" DEPENDS ${subdir}/${test_file_cpp})
        set(run_all_command ${run_all_command} COMMAND "./${test_file}")
        set(run_all_dependencies ${run_all_dependencies} "${test_file}")
    endforeach()
endforeach()

#Note: this would allow generating executables in subdirectories. It is probably a dangerous hack though. In fact slashes should not be allowed in target names
#add_executable(huga_testhuga "/home/mkean/code/puzzles/segment_tree/test.cpp")
#set_target_properties(huga_testhuga PROPERTIES OUTPUT_NAME huga/testhuga)

add_custom_target(run_all ${run_all_command} DEPENDS ${run_all_dependencies})
