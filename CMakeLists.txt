cmake_minimum_required(VERSION 3.2)
project(reliability-task1)

set(CMAKE_CXX_FLAGS "-std=c99 ${CMAKE_CXX_FLAGS}")

set(SOURCE_FILES 421_Romanov.c)
add_executable(reliability-task1 ${SOURCE_FILES})