cmake_minimum_required(VERSION 2.8)

add_definitions(-std=gnu++0x -Wall -ggdb)

include_directories( ${CMAKE_CURRENT_SOURCE_DIR} )

add_subdirectory(src)
