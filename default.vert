#version 130

uniform mat4 camera;
uniform mat4 transformation;

in vec4 bk_vertex;
in vec2 bk_texture;

out vec2 fragTexCoord;

void main() {
	fragTexCoord = bk_texture;
	gl_Position = camera * transformation * bk_vertex;
}

