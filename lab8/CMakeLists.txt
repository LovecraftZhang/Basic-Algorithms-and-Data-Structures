cmake_minimum_required(VERSION 3.6)
project(lab8)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES
        avl.cc
        Unit.cc
        Unit.h)

add_executable(lab8 ${SOURCE_FILES})