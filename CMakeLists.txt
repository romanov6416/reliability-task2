cmake_minimum_required(VERSION 3.2)
project(reliability-task1)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES 421_Romanov.c)
add_executable(reliability-task1 ${SOURCE_FILES})