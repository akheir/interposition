cmake_minimum_required(VERSION 3.7)

set(SOURCE_FILES fopen_test.cpp)

add_executable(fopen_test fopen_test.cpp)
target_link_libraries (fopen_test LINK_PUBLIC interposition)

