#include "shader.h"

#include "base.h"
#include "filesystem.h"

Shader::Shader(const string& source, const GLuint type) :
	Managed()
{
	BK_GL_ASSERT(setId(glCreateShader(type)));

	const char* _source = source.c_str();
	BK_GL_ASSERT(glShaderSource(id(), 1, (const GLchar**)&_source, NULL));
	BK_GL_ASSERT(glCompileShader(id()));

	GLint success;
	glGetShaderiv(id(), GL_COMPILE_STATUS, &success);
	if (success != GL_TRUE) {
		string msg("Compile failure in shader:\n");

		GLint infoLogLength;
		glGetShaderiv(id(), GL_INFO_LOG_LENGTH, &infoLogLength);
		char* strInfoLog = new char[infoLogLength + 1];
		glGetShaderInfoLog(id(), infoLogLength, NULL, strInfoLog);

		msg += strInfoLog;
		BK_DEBUG(strInfoLog);
		BK_PRINT(_source);

		delete[] strInfoLog;

		glDeleteShader(id());
		setId(0);
	}
	BK_ASSERT(id() != 0);
}

Shader::~Shader()
{
}

Shader*
Shader::fromFile( const string& path, const GLuint type )
{
	return Shader::fromSource( Filesystem::readAll( path ), type );
}

Shader*
Shader::fromSource( const string& source, const GLuint type )
{
	return new Shader( source, type );
}

GLuint Shader::type() const
{
	return m_type;
}

