cmake_minimum_required(VERSION 3.12)
project(Calculator)

set(CMAKE_CXX_STANDARD 14)

add_executable(Calculator src/main.cpp src/Calculator.cpp src/Calculator.h src/utilities/Translator.cpp src/utilities/Translator.h)