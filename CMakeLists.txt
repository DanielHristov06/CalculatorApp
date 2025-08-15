cmake_minimum_required(VERSION 3.16)
project(CalculatorApp)

set(CMAKE_CXX_STANDARD 23)

include_directories("include")

file(GLOB_RECURSE SRC_FILES "src/*.cpp")

file(GLOB_RECURSE HEADER_FILES "include/*.h")

add_executable(Calculator ${SRC_FILES} ${HEADER_FILES})