#version 130
in vec4 vert;
in vec2 vertTexCoord;
out vec2 fragTexCoord;

void main() {
	fragTexCoord = vertTexCoord;
	gl_Position = vert;
}

