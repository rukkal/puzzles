CMAKE_MINIMUM_REQUIRED (VERSION 2.6)

PROJECT (coding-puzzle)

SET(CMAKE_VERBOSE_MAKEFILE ON)

SET(GTEST_CXX_FLAGS "-pthread")
SET(GTEST_LIBRARIES "-lgtest -lgtest_main")
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 -Wall -g3 ${GTEST_CXX_FLAGS}")
SET(CMAKE_INCLUDE_PATH "/usr/include")
SET(CMAKE_LIBRARY_PATH "/usr/lib")

INCLUDE_DIRECTORIES("/usr/include/Catch/include")

MACRO(SUBDIRLIST result curdir)
    FILE(GLOB children RELATIVE ${curdir} ${curdir}/*)
    SET(dirlist "")
    FOREACH(child ${children})
        IF(IS_DIRECTORY ${curdir}/${child})
            LIST(APPEND dirlist ${child})
        ENDIF()
    ENDFOREACH()
    SET(${result} ${dirlist})
ENDMACRO()

SUBDIRLIST(subdirs ${CMAKE_CURRENT_LIST_DIR})
FOREACH(subdir ${subdirs})
    SET(executable_file test_${subdir})
    SET(test_cpp ${CMAKE_CURRENT_LIST_DIR}/${subdir}/test.cpp)
    IF(EXISTS ${test_cpp})
        EXECUTE_PROCESS(COMMAND ${CMAKE_COMMAND} -E echo "adding executable ${executable_file}")
        ADD_EXECUTABLE(${executable_file} ${test_cpp})
        TARGET_LINK_LIBRARIES(${executable_file} ${GTEST_LIBRARIES})
        SET(run_all_command ${run_all_command} COMMAND "./${executable_file}")
        SET(run_all_dependencies ${run_all_dependencies} "${executable_file}")
    ENDIF()
ENDFOREACH()

ADD_CUSTOM_TARGET(run_all ${run_all_command} DEPENDS ${run_all_dependencies})
