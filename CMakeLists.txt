cmake_minimum_required(VERSION 3.17.3)
set(PROJECT_NAME Calculator)
project(${PROJECT_NAME})

set(CMAKE_CXX_STANDARD 20)

file(GLOB_RECURSE SOURCES RELATIVE ${CMAKE_SOURCE_DIR} "src/*")

add_executable(${PROJECT_NAME} ${SOURCES} src/utilities/exceptions.h)