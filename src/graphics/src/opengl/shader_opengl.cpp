#include "graphics/inc/opengl/shader_opengl.h"

static GLint _to_opengl_type(const IShader::Type type)
{
	switch ( type ) {
	case IShader::VERTEX:
		return GL_VERTEX_SHADER;
	case IShader::FRAGMENT:
		return GL_FRAGMENT_SHADER;
	}
}

class ShaderOpenGLPrivate {
public:
	ShaderOpenGLPrivate(const string& source, const IShader::Type type)
	{
		BK_GL_ASSERT(m_shader = glCreateShader(_to_opengl_type(type)));

		const char* _source = source.c_str();
		BK_GL_ASSERT(glShaderSource(m_shader, 1, (const GLchar**)&_source, NULL));
		BK_GL_ASSERT(glCompileShader(m_shader));

		GLint success;
		glGetShaderiv(m_shader, GL_COMPILE_STATUS, &success);
		if (success != GL_TRUE) {
			string msg("Compile failure in shader:\n");

			GLint infoLogLength;
			glGetShaderiv(m_shader, GL_INFO_LOG_LENGTH, &infoLogLength);
			char* strInfoLog = new char[infoLogLength + 1];
			glGetShaderInfoLog(m_shader, infoLogLength, NULL, strInfoLog);

			msg += strInfoLog;
			BK_DEBUG(strInfoLog);
			BK_PRINT(_source);

			delete[] strInfoLog;

			glDeleteShader(m_shader);
			m_shader = 0;
		}
		BK_ASSERT(m_shader != 0);
	}

	~ShaderOpenGLPrivate()
	{
		BK_GL_ASSERT(glDeleteShader(m_shader));
	}

	GLuint handler()
	{
		return m_shader;
	}

	IShader::Type type() const
	{
		return m_type;
	}

private:
	GLuint m_shader;
	IShader::Type m_type;
};

ShaderOpenGL::ShaderOpenGL(const string& source, const IShader::Type type) :
	m_impl(new ShaderOpenGLPrivate(source, type))
{
}

ShaderOpenGL::~ShaderOpenGL()
{
	SAFE_DELETE(m_impl);
}

IShader::Type
ShaderOpenGL::type() const
{
	return m_impl->type();
}

int
ShaderOpenGL::handler() const
{
	return m_impl->handler();
}

