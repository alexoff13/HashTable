cmake_minimum_required(VERSION 3.17)
project(hash_table)

set(CMAKE_CXX_STANDARD 20)

add_executable(hash_table main.cpp product.h TableProducts.cpp TableProducts.h Hash.cpp Hash.h)