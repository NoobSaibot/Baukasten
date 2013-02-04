#include "mesh_opengl.h"

#include "../vertex_format.h"
#include "../iprogram.h"

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

/*!
 * \brief MeshOpenglPrivate class declaration.
 */
class MeshOpenglPrivate {
public:
	MeshOpenglPrivate()
	{
	}

	virtual ~MeshOpenglPrivate()
	{
	}

	void init(const float* data, const IMesh::UsageHint hint,
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
		BK_GL_ASSERT( glBufferData(GL_ARRAY_BUFFER, size, NULL, gl_hint) );

		BK_GL_ASSERT( glBindBuffer(GL_ARRAY_BUFFER, m_vbo) );
		BK_GL_ASSERT( glBufferData(GL_ARRAY_BUFFER, size, data, gl_hint) );
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

	void activate(const IProgram& program) const
	{
		BK_GL_ASSERT(glBindVertexArray(m_vao));
		BK_GL_ASSERT(glBindBuffer(GL_ARRAY_BUFFER, m_vbo));

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
	}

	void deactivate() const
	{
		BK_GL_ASSERT(glBindVertexArray(0));
		BK_GL_ASSERT(glBindBuffer(GL_ARRAY_BUFFER, 0));
	}

private:
	GLuint m_vbo, m_vao;
	VertexFormat m_format;
	int m_size;
};

MeshOpengl::MeshOpengl() :
	m_impl(new MeshOpenglPrivate())
{
}

MeshOpengl::~MeshOpengl()
{
	delete m_impl;
	m_impl = 0;
}

void MeshOpengl::init(const float* data, const UsageHint hint,
		const VertexFormat format, const int size)
{
	m_impl->init(data, hint, format, size);
}

VertexFormat MeshOpengl::format() const
{
	return m_impl->format();
}

int MeshOpengl::count() const
{
	return m_impl->count();
}

void MeshOpengl::activate(const IProgram& program) const
{
	m_impl->activate(program);
}

void MeshOpengl::deactivate() const
{
	m_impl->deactivate();
}

