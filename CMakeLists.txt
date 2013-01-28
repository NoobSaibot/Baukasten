cmake_minimum_required(VERSION 2.8)

project("Baukasten")

add_definitions( -std=gnu++0x -Wall -ggdb )

set(graphics_SRCS
  bitmap.cpp
  camera.cpp
  drawable.cpp
  filesystem.cpp
  main.cpp
  managed.cpp
  mesh.cpp
  model.cpp
  opengl/mesh_opengl.cpp
  program.cpp
  scene.cpp
  shader.cpp
  texture.cpp
  vertex_format.cpp
)

add_executable(test ${graphics_SRCS})
target_link_libraries( test GL GLEW GLU glfw )
