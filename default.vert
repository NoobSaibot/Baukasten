#version 130

uniform mat4 projection;
uniform mat4 camera;
uniform mat4 translation;

in vec4 vert;
in vec2 vertTexCoord;

out vec2 fragTexCoord;

void main() {
	fragTexCoord = vertTexCoord;
	gl_Position = camera * translation * vert;
}

