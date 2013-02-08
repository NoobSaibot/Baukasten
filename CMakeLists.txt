cmake_minimum_required(VERSION 2.8)

project("Baukasten")

add_definitions( -std=gnu++0x -Wall -ggdb )

include( core/CMakeLists.txt )
include( graphics/CMakeLists.txt )
include( io/CMakeLists.txt )

include_directories( ${CMAKE_CURRENT_SOURCE_DIR} )

add_executable(test main.cpp ${core_SRCS} ${io_SRCS} ${graphics_SRCS})
target_link_libraries( test GL GLEW GLU glfw )
