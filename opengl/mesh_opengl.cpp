#include "mesh_opengl.h"

#include "../vertex_format.h"

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

		GLint gl_hint = (hint == IMesh::STATIC) ? GL_STATIC_DRAW :
			( (hint == IMesh::DYNAMIC) ? GL_DYNAMIC_DRAW : GL_STREAM_DRAW );

		BK_GL_ASSERT( glGenVertexArrays(1, &m_vao) );
		BK_GL_ASSERT( glBindVertexArray(m_vao) );

		BK_GL_ASSERT( glGenBuffers(1, &m_vbo) );
		BK_GL_ASSERT( glBindBuffer(GL_ARRAY_BUFFER, m_vbo) );
		BK_GL_ASSERT( glBufferData(GL_ARRAY_BUFFER, size, NULL, gl_hint) );

		BK_GL_ASSERT(glBindBuffer(GL_ARRAY_BUFFER, m_vbo));
		BK_GL_ASSERT(glBufferData(GL_ARRAY_BUFFER, size, data, gl_hint));
		BK_GL_ASSERT(glBindBuffer(GL_ARRAY_BUFFER, 0));
	}

	VertexFormat format() const
	{
		return m_format;
	}

	int count() const
	{
		// 60 bytes / 4 bytes / 5
		return m_size / sizeof(float) / m_format.size();
	}

	void activate() const
	{
		BK_GL_ASSERT(glBindVertexArray(m_vao));
		BK_GL_ASSERT(glBindBuffer(GL_ARRAY_BUFFER, m_vbo));
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

void MeshOpengl::activate() const
{
	m_impl->activate();
}

void MeshOpengl::deactivate() const
{
	m_impl->deactivate();
}

