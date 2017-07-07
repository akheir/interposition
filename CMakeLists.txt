cmake_minimum_required(VERSION 3.7)
project(interposition)

SET(LIBRARY_OUTPUT_PATH ${CMAKE_BINARY_DIR}/lib)
link_directories(${CMAKE_BINARY_DIR}/lib)
SET(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR}/bin)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

set(SOURCE_FILES interposition.cpp)


add_library(interposition SHARED ${SOURCE_FILES})
target_link_libraries (interposition LINK_PUBLIC dl)

add_subdirectory(tests)
