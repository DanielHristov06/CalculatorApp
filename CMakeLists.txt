cmake_minimum_required(VERSION 3.10)
project(CalculatorApp)

set(CMAKE_CXX_STANDARD 23)

file(GLOB SRC_FILES CONFIGURE_DEPENDS src/*.cpp src/*.h)

add_executable(Calculator ${SRC_FILES})