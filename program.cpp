#include "program.h"

#include "shader.h"

Program* Program::createProgram(const Shaders& shader)
{
	return new Program(shader);
}

Program::Program(const Shaders& shader) :
	Drawable()
{
	BK_GL_ASSERT(setId(glCreateProgram()));
	for( Shader* s: shader ) {
		BK_ASSERT(s->id() != 0);
		BK_GL_ASSERT(glAttachShader(id(), s->id()));
	}
	BK_GL_ASSERT(glLinkProgram(id()));
	GLint status;
	glGetProgramiv(id(), GL_LINK_STATUS, &status);
	if (status == GL_FALSE) {
		std::string msg("Program linking failure: ");

		GLint infoLogLength;
		glGetProgramiv(id(), GL_INFO_LOG_LENGTH, &infoLogLength);
		char* strInfoLog = new char[infoLogLength + 1];
		glGetProgramInfoLog(id(), infoLogLength, NULL, strInfoLog);
		msg += strInfoLog;
		delete[] strInfoLog;

		glDeleteProgram(id()); setId(0);
		BK_DEBUG(msg);
	}

	BK_ASSERT(status == GL_TRUE);
	for( Shader* s: shader ) {
		BK_GL_ASSERT(glDetachShader(id(), s->id()));
	}
}

Program::~Program()
{
}

GLint Program::attrib(const string& attrib) const
{
	GLint pos;
	BK_GL_ASSERT(pos = glGetAttribLocation(id(), attrib.c_str()));
	return pos;
}

GLint Program::constant(const string& uni) const
{
	GLint pos;
	BK_GL_ASSERT(pos = glGetUniformLocation(id(), uni.c_str()));
	return pos;
}

void Program::setConstant(const string& name, const mat4& matrix)
{
	BK_GL_ASSERT(glUniformMatrix4fv(
		constant(name.c_str()), 1, GL_FALSE, value_ptr(matrix)
	));
}

void Program::activate() const
{
	BK_GL_ASSERT(glUseProgram(id()));
}

void Program::deactivate() const
{
	BK_GL_ASSERT(glUseProgram(0));
}

