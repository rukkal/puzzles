cmake_minimum_required (VERSION 2.6)

set(CMAKE_C_COMPILER "gcc-5")
set(CMAKE_CXX_COMPILER "g++-5")

project (test)

set(CMAKE_VERBOSE_MAKEFILE ON)

set(CMAKE_INCLUDE_PATH "/usr/include")
set(CMAKE_LIBRARY_PATH "/usr/lib")

set(GCC_CXX_FLAGS "-std=c++14 -Wall -g")
set(GTEST_CXX_FLAGS "-pthread")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${GCC_CXX_FLAGS} ${GTEST_CXX_FLAGS}")

# the following variable assignment is obsiously not necessary
# it is here just to point out the variable's existence
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS}")

set(GTEST_LIBRARIES "-lgtest -lgtest_main")

add_executable(test test.cpp)
target_link_libraries(test ${GTEST_LIBRARIES})

