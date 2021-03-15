cmake_minimum_required(VERSION 3.17)
project(hash_table)

set(CMAKE_CXX_STANDARD 20)

add_executable(hash_table main.cpp src/product.h src/TableProducts.cpp src/TableProducts.h src/Hash.cpp src/Hash.h tests/tests.cpp)

add_definitions(-std=gnu++17 -U__STRICT_ANSI__)

add_subdirectory(googletest)
include_directories(googletest/googletest/include)

add_executable(tests tests/tests.cpp)

target_link_libraries(tests gtest)