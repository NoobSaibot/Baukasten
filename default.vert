#version 130

uniform mat4 projection;
uniform mat4 camera;
uniform mat4 transformation;

in vec4 bk_vertex;
in vec2 bk_texture0;

out vec2 bk_fragTex0;

void main() {
	bk_fragTex0 = bk_texture0;
	gl_Position = camera * transformation * bk_vertex;
}

