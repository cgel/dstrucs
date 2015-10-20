cmake_minimum_required(VERSION 2.8)
project(dstructs)

set(CMAKE_CXX_FLAGS "-g -Wall -O0")

add_definitions(-D__PC)

enable_testing()

add_subdirectory(libs/googletest)
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

add_subdirectory(./bst)
add_subdirectory(heap)
