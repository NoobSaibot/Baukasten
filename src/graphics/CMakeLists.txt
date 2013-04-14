include_directories( "/usr/include/freetype2" )

set(graphics_SRCS
  graphics/src/animation.cpp
  graphics/src/bitmap.cpp
  graphics/src/camera.cpp
  graphics/src/form.cpp
  graphics/src/font.cpp
  graphics/src/graphics.cpp
  graphics/src/icontext.cpp
  graphics/src/iform.cpp
  graphics/src/text_form.cpp
  graphics/src/opengl/context_opengl.cpp
  graphics/src/opengl/display_opengl.cpp
  graphics/src/opengl/graphics_opengl.cpp
  graphics/src/opengl/mesh_opengl.cpp
  graphics/src/opengl/program_opengl.cpp
  graphics/src/opengl/shader_opengl.cpp
  graphics/src/opengl/texture_opengl.cpp
)
