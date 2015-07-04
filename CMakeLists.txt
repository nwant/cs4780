cmake_minimum_required(VERSION 3.2)
project(proj1_rc5)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -traditional-cpp")

set(SOURCE_FILES main.cpp)
add_executable(rc5 ${SOURCE_FILES} RC5.cpp RC5.h BinaryUtility.cpp BinaryUtility.h)