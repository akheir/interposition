#  Copyright (c) 2017 Alireza Kheirkhahan
#
#  Distributed under the Boost Software License, Version 1.0. (See accompanying
#  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

cmake_minimum_required(VERSION 3.7)
project(interposition)

SET(LIBRARY_OUTPUT_PATH ${CMAKE_BINARY_DIR}/lib)
link_directories(${CMAKE_BINARY_DIR}/lib)
SET(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR}/bin)

SET(CMAKE_CXX_STANDARD 11)
SET(CMAKE_POSITION_INDEPENDENT_CODE ON)

IF(UNIX)
    IF(CMAKE_COMPILER_IS_GNUCC)
        SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fvisibility=hidden")
    ENDIF(CMAKE_COMPILER_IS_GNUCC)
ENDIF(UNIX)

SET(SOURCE_FILES interposition.cpp)
add_library(interposition SHARED ${SOURCE_FILES})
target_link_libraries (interposition LINK_PUBLIC dl)

add_subdirectory(tests)
