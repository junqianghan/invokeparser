cmake_minimum_required(VERSION 3.7)
project(invokeparse)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp file_io.cpp pattern_parser.cpp log_parser.cpp)
add_executable(invokeparse ${SOURCE_FILES})