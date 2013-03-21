project("Baukasten")

include( core/CMakeLists.txt )
include( graphics/CMakeLists.txt )
include( io/CMakeLists.txt )
include( input/CMakeLists.txt )
include( model/CMakeLists.txt )

include_directories( ${CMAKE_CURRENT_SOURCE_DIR} )

set(demo_SRCS main.cpp)

add_executable(demo ${demo_SRCS}
	${core_SRCS} ${input_SRCS} ${io_SRCS} ${graphics_SRCS}
	${model_SRCS})
target_link_libraries( demo GL GLEW GLU glfw )
