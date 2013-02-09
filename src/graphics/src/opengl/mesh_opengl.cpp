#include "graphics/inc/opengl/mesh_opengl.h"

#include "graphics/IProgram"
#include "graphics/VertexFormat"

static void
_set_attrib(const IProgram* program, VertexFormat::Data d, const int size, const string& attrib)
{
	GLint pos;
	pos = program->attrib(attrib.c_str());
	BK_GL_ASSERT(glVertexAttribPointer(
		pos, d.size, GL_FLOAT, GL_FALSE, size * sizeof(GLfloat), (const GLvoid*)(d.padding * sizeof(GLfloat))
	));
	BK_GL_ASSERT(glEnableVertexAttribArray(pos));
}

class MeshOpenGLPrivate {
public:
	MeshOpenGLPrivate() : m_active(false)
	{
	}

	virtual ~MeshOpenGLPrivate()
	{
	}

	void init(const IProgram& program, const float* data, const IMesh::UsageHint hint,
			const VertexFormat format, const int size)
	{
		m_format = format;
		m_size = size;

		GLint gl_hint = (hint == IMesh::STATIC) ? GL_STATIC_DRAW :
			( (hint == IMesh::DYNAMIC) ? GL_DYNAMIC_DRAW : GL_STREAM_DRAW );

		BK_GL_ASSERT( glGenVertexArrays(1, &m_vao) );
		BK_GL_ASSERT( glBindVertexArray(m_vao) );

		BK_GL_ASSERT( glGenBuffers(1, &m_vbo) );
		BK_GL_ASSERT( glBindBuffer(GL_ARRAY_BUFFER, m_vbo) );
		BK_GL_ASSERT( glBufferData(GL_ARRAY_BUFFER, size, data, gl_hint) );

		for ( VertexFormat::Data d: m_format.elements() ) {
			switch ( d.type ) {
			case VertexFormat::COLOR:
			case VertexFormat::NORMAL:
			case VertexFormat::TANGENT:
			case VertexFormat::BINORMAL:
			case VertexFormat::BLENDWEIGHTS:
			case VertexFormat::BLENDINDICES:
			case VertexFormat::TEXCOORD1:
			case VertexFormat::TEXCOORD2:
			case VertexFormat::TEXCOORD3:
			case VertexFormat::TEXCOORD4:
			case VertexFormat::TEXCOORD5:
			case VertexFormat::TEXCOORD6:
			case VertexFormat::TEXCOORD7:
				break;
			case VertexFormat::POSITION:
				_set_attrib(&program, d, m_format.size(), "vert");
				break;
			case VertexFormat::TEXCOORD0:
				_set_attrib(&program, d, m_format.size(), "vertTexCoord");
				break;
			}
		}

		BK_GL_ASSERT( glBindBuffer(GL_ARRAY_BUFFER, 0) );
	}

	VertexFormat format() const
	{
		return m_format;
	}

	int count() const
	{
		return m_size / sizeof(float) / m_format.size();
	}

	void activate() const
	{
		if (m_active) return;
		BK_GL_ASSERT(glBindVertexArray(m_vao));
		m_active = true;
	}

	bool isActive() const
	{
		return m_active;
	}

	void deactivate() const
	{
		BK_GL_ASSERT(glBindVertexArray(0));
		BK_GL_ASSERT(glBindBuffer(GL_ARRAY_BUFFER, 0));
		m_active = false;
	}

private:
	GLuint m_vbo, m_vao;
	VertexFormat m_format;
	int m_size;
	mutable bool m_active;
};

MeshOpenGL::MeshOpenGL() :
	m_impl(new MeshOpenGLPrivate())
{
}

MeshOpenGL::~MeshOpenGL()
{
	SAFE_DELETE(m_impl);
}

void MeshOpenGL::init(const IProgram& program, const float* data, const UsageHint hint,
		const VertexFormat format, const int size)
{
	m_impl->init(program, data, hint, format, size);
}

VertexFormat MeshOpenGL::format() const
{
	return m_impl->format();
}

int MeshOpenGL::count() const
{
	return m_impl->count();
}

void MeshOpenGL::activate() const
{
	m_impl->activate();
}

bool
MeshOpenGL::isActive() const
{
	return m_impl->isActive();
}

void MeshOpenGL::deactivate() const
{
	m_impl->deactivate();
}

