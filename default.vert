#version 130

uniform mat4 projection;
uniform mat4 camera;
uniform mat4 transformation;

in vec4 bk_vertex;
in vec2 bk_texture0;
in vec3 bk_color;

out vec2 bk_fragTex0;
out vec3 bk_Color;

void main() {
	bk_fragTex0 = bk_texture0;
	bk_Color = bk_color;
	gl_Position = camera * transformation * bk_vertex;
}

