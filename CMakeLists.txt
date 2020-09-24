cmake_minimum_required(VERSION 3.12)
project(Calculator)

set(CMAKE_CXX_STANDARD 20)

add_executable(Calculator src/main.cpp src/calculator.cpp src/calculator.h src/utilities/translator.cpp src/utilities/translator.h)