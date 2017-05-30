cmake_minimum_required(VERSION 3.7)
project(lab1)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fopenmp")

set(SOURCE_FILES main.cpp inc/t_measure.h)
add_executable(lab1 ${SOURCE_FILES})