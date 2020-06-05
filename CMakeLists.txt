cmake_minimum_required(VERSION 3.10)
project(l2log)

set(CMAKE_CXX_STANDARD 11)

add_executable(l2log main.cpp src/logger.h)

add_subdirectory(test/googletest)
include_directories(test/googletest/googletest/include)

add_executable(sample_test test/logger_test.cpp)
add_executable(sample_test2 test/logger_test.cpp test/test_main.cpp)

target_link_libraries(sample_test gtest gtest_main)
target_link_libraries(sample_test2 gtest gtest_main)