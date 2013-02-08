#include "graphics/inc/opengl/program_opengl.h"

#include "graphics/IShader"

class ProgramOpenGLPrivate {
public:
	ProgramOpenGLPrivate(const ShaderList& shader)
	{
		BK_GL_ASSERT(m_program = (glCreateProgram()));
		for( IShader* s: shader ) {
			BK_ASSERT(s->handler() != 0);
			BK_GL_ASSERT(glAttachShader(m_program, s->handler()));
		}
		BK_GL_ASSERT(glLinkProgram(m_program));
		GLint status;
		glGetProgramiv(m_program, GL_LINK_STATUS, &status);
		if (status == GL_FALSE) {
			std::string msg("Program linking failure: ");

			GLint infoLogLength;
			glGetProgramiv(m_program, GL_INFO_LOG_LENGTH, &infoLogLength);
			char* strInfoLog = new char[infoLogLength + 1];
			glGetProgramInfoLog(m_program, infoLogLength, NULL, strInfoLog);
			msg += strInfoLog;
			delete[] strInfoLog;

			glDeleteProgram(m_program);
			m_program = 0;
			BK_DEBUG(msg);
		}

		BK_ASSERT(status == GL_TRUE);
		for( IShader* s: shader ) {
			BK_GL_ASSERT(glDetachShader(m_program, s->handler()));
		}
	}

	~ProgramOpenGLPrivate()
	{
		BK_GL_ASSERT(glDeleteProgram(m_program));
	}

	int attrib(const string& name) const
	{
		GLint pos;
		BK_GL_ASSERT(pos = glGetAttribLocation(m_program, name.c_str()));
		return pos;
	}

	void setAttrib(const string& name, const mat4& value)
	{
	}

	int constant(const string& name) const
	{
		GLint pos;
		BK_GL_ASSERT(pos = glGetUniformLocation(m_program, name.c_str()));
		return pos;
	}

	void setConstant(const string& name, const mat4& value)
	{
		BK_GL_ASSERT(glUniformMatrix4fv(
			constant(name.c_str()), 1, GL_FALSE, value_ptr(value)
		));
	}

	void activate() const
	{
		BK_GL_ASSERT(glUseProgram(m_program));
	}

	void deactivate() const
	{
		BK_GL_ASSERT(glUseProgram(0));
	}

private:
	GLuint m_program;
};

ProgramOpenGL::ProgramOpenGL(const ShaderList& shader) :
	m_impl(new ProgramOpenGLPrivate(shader))
{
}

ProgramOpenGL::~ProgramOpenGL()
{
	SAFE_DELETE(m_impl);
}

int ProgramOpenGL::attrib(const string& name) const
{
	BK_ASSERT(m_impl);
	return m_impl->attrib(name);
}

void ProgramOpenGL::setAttrib(const string& name, const mat4& value)
{
	BK_ASSERT(m_impl);
	m_impl->setAttrib(name, value);
}

int ProgramOpenGL::constant(const string& name) const
{
	BK_ASSERT(m_impl);
	return m_impl->constant(name);
}

void ProgramOpenGL::setConstant(const string& name, const mat4& value)
{
	BK_ASSERT(m_impl);
	m_impl->setConstant(name, value);
}

void ProgramOpenGL::activate() const
{
	BK_ASSERT(m_impl);
	m_impl->activate();
}

void ProgramOpenGL::deactivate() const
{
	BK_ASSERT(m_impl);
	m_impl->deactivate();
}
