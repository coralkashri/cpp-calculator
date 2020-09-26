cmake_minimum_required(VERSION 3.17.3)
set(PROJECT_NAME Calculator)
project(${PROJECT_NAME})

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++20")

add_subdirectory(google_tests/lib)
include_directories(google_tests/lib/googletest/include google_tests/lib/googletest/)

file(GLOB_RECURSE SOURCES RELATIVE ${CMAKE_SOURCE_DIR} "src/*")
file(GLOB_RECURSE UTILITIES RELATIVE ${CMAKE_SOURCE_DIR} "src/utilities/*")

add_executable(${PROJECT_NAME} ${SOURCES})

add_executable(Google_Tests_run src/calculator.cpp src/calculator.h src/translator.cpp src/translator.h ${UTILITIES}  google_tests/test1.cpp)

target_link_libraries(Google_Tests_run gtest gtest_main)