cmake_minimum_required (VERSION 2.6)

project (coding-puzzle)

set(CMAKE_VERBOSE_MAKEFILE ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall -g3")

include_directories("../Catch/include")

add_executable(test test.cpp)
