cmake_minimum_required(VERSION 3.10)

project(ALGOS)

set(SOURCES
    source.cpp
)

set (CMAKE_CXX_STANDARD 17)

set (CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(lib/rbtree
                    lib/tree)

add_executable(algos ${SOURCES})