cmake_minimum_required(VERSION 3.10)

project(ALGOS)

set(SOURCES
    source.cpp
    lib/list/list.cpp
)

include_directories(lib/list)

add_executable(algos ${SOURCES})