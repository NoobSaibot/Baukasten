#include "mesh.h"

Mesh::Mesh(const VertexFormat format, const int size) :
	m_size(size), m_format(format)
{
}

Mesh::~Mesh()
{
}

Mesh* Mesh::createMesh(const float* data, const UsageHint hint,
		const VertexFormat format, const int size)
{
	BK_ASSERT(data != 0);
	GLuint vbo, vao;
	GLint gl_hint = (hint == STATIC) ? GL_STATIC_DRAW :
		( (hint == DYNAMIC) ? GL_DYNAMIC_DRAW : GL_STREAM_DRAW );

	BK_GL_ASSERT( glGenVertexArrays(1, &vao) );
	BK_GL_ASSERT( glBindVertexArray(vao) );

	BK_GL_ASSERT( glGenBuffers(1, &vbo) );
	BK_GL_ASSERT( glBindBuffer(GL_ARRAY_BUFFER, vbo) );
	BK_GL_ASSERT( glBufferData(GL_ARRAY_BUFFER, size, NULL, gl_hint) );
	BK_GL_ASSERT( glBufferData(GL_ARRAY_BUFFER, size, data, gl_hint) );
	BK_GL_ASSERT( glBindBuffer(GL_ARRAY_BUFFER, 0) );

	Mesh* mesh = new Mesh(format, size);
	mesh->setId(vbo);
	mesh->m_vao = vao;

	return mesh;
}

VertexFormat Mesh::format() const
{
	return m_format;
}

int Mesh::count() const
{
	// 60 bytes / 4 bytes / 5
	return m_size / sizeof(float) / m_format.size();
}

void Mesh::activate() const
{
	BK_GL_ASSERT(glBindVertexArray(m_vao));
	BK_GL_ASSERT(glBindBuffer(GL_ARRAY_BUFFER, id()));
}

void Mesh::deactivate() const
{
	BK_GL_ASSERT(glBindVertexArray(0));
	BK_GL_ASSERT(glBindBuffer(GL_ARRAY_BUFFER, 0));
}

