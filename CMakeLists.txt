cmake_minimum_required(VERSION 3.14)
project(l2log)

set(CMAKE_CXX_STANDARD 14)

add_executable(l2log main.cpp logger.cpp)
