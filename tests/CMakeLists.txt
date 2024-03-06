cmake_minimum_required(VERSION 3.5)

project(search_engine_tests LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(gtest_disable_pthreads on)

include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

add_executable(search_engine_tests invertedindex_test.cpp searchserver_test.cpp)

target_link_libraries(search_engine_tests PRIVATE gtest gtest_main)

