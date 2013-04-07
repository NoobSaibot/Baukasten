#include "graphics/inc/opengl/mesh_opengl.h"

#include "core/Assert"
#include "graphics/IProgram"

#include "graphics/inc/opengl/assert_opengl.h"

#include <algorithm>

namespace {
struct Data {
	Data() : data(nullptr), size(0), count(0)
	{
	}

	int byteSize()
	{
		return size * sizeof(float);
	}

	float* data;
	unsigned int size;
	unsigned int count;
};

static void
_set_attrib(const bk::IProgram* program, Data d,
		const string& attrib, int stride, unsigned int offset)
{
	GLint pos;
	pos = program->attrib(attrib.c_str());
	BK_GL_ASSERT(glVertexAttribPointer(
		pos, d.count, GL_FLOAT, GL_FALSE, stride, (const GLvoid*)(offset)
	));
	BK_GL_ASSERT(glEnableVertexAttribArray(pos));
}
}

namespace bk {

class MeshOpenGLPrivate {
public:
	MeshOpenGLPrivate() : m_vbo(0), m_vao(0), m_active(false), m_dirty(false),
		m_program(nullptr)
	{
	}

	virtual ~MeshOpenGLPrivate()
	{
		BK_GL_ASSERT(glDeleteBuffers(1, &m_vbo));
		BK_GL_ASSERT(glDeleteVertexArrays(1, &m_vao));
		SAFE_ARR_DELETE(m_vertices.data);
		SAFE_ARR_DELETE(m_colors.data);
		SAFE_ARR_DELETE(m_texture.data);
		SAFE_ARR_DELETE(m_normals.data);
	}

	int count() const
	{
		return m_vertices.size / m_vertices.count;
	}

	void activate()
	{
		if (m_active) return;
		if (m_dirty) {
			initBuffer();
		}

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

	void setProgram(IProgram* program)
	{
		m_program = program;
		m_program->addRef();
	}

	void setVertices(const float* data, const unsigned int size,
			const unsigned int count)
	{
		setData(0, data, size, count);
	}

	void setColors(const float* data, const unsigned int size,
			const unsigned int count)
	{
		setData(1, data, size, count);
	}

	void setTexture(const float* data, const unsigned int size,
			const unsigned int count)
	{
		setData(2, data, size, count);
	}

	void setNormals(const float* data, const unsigned int size,
			const unsigned int count)
	{
		setData(3, data, size, count);
	}

private:
	void initBuffer()
	{
		BK_ASSERT(m_program != nullptr, "Shader Program must be set.");

		if (m_vao == 0) {
			BK_GL_ASSERT( glGenVertexArrays(1, &m_vao) );
		}
		BK_GL_ASSERT( glBindVertexArray(m_vao) );

		if (m_vbo == 0) {
			BK_GL_ASSERT( glGenBuffers(1, &m_vbo) );
		}
		BK_GL_ASSERT( glBindBuffer(GL_ARRAY_BUFFER, m_vbo) );

		// compute the size of data
		unsigned int size = m_vertices.byteSize() + m_colors.byteSize() +
			m_texture.byteSize() + m_normals.byteSize();

		// reserve memory for all the data that is actually
		// set (VERTICES, NORMALS, TEXTURE, ...)
		float* data = new float[size];

		// set everything to 0
		memset(data, 0, size * sizeof(float));

		// copy the set data to the "data" container {{
		std::copy(m_vertices.data, m_vertices.data + m_vertices.size, data);
		std::copy(m_colors.data, m_colors.data + m_colors.size, data+m_vertices.size);
		std::copy(m_texture.data, m_texture.data + m_texture.size,
				data+m_vertices.size+m_colors.size);
		std::copy(m_normals.data, m_normals.data + m_normals.size,
				data+m_vertices.size+m_colors.size+m_texture.size);
		// }}

		// upload the data to the graphics card and free the memory
		BK_GL_ASSERT( glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW) );
		SAFE_ARR_DELETE(data);

		int offset = 0;
		// have to keep the data around in case any field is set -- therefor the
		// object is dirty -- and the glbuffer has to be set again
		if (m_vertices.data != nullptr) {
			_set_attrib(m_program, m_vertices,
				m_program->getVariableName(ProgramVariableType::VERTEX), 0, offset);
			offset += m_vertices.byteSize();
		}

		if (m_colors.data != nullptr) {
			_set_attrib(m_program, m_colors,
				m_program->getVariableName(ProgramVariableType::COLOR), 0, offset);
			offset += m_colors.byteSize();
		}

		if (m_texture.data != nullptr) {
			_set_attrib(m_program, m_texture,
				m_program->getVariableName(ProgramVariableType::TEXTURE0), 0, offset);
			offset += m_texture.byteSize();
		}

		if (m_normals.data != nullptr) {
			_set_attrib(m_program, m_normals,
				m_program->getVariableName(ProgramVariableType::NORMAL), 0, offset);
			offset += m_normals.byteSize();
		}

		m_dirty = false;
	}

	void setData(int type, const float* data, const unsigned int size,
			const unsigned int count)
	{
		switch (type) {
		case 0: // vertices
			SAFE_ARR_DELETE(m_vertices.data);
			m_vertices.data = new float[size];
			std::copy(data, data + size, m_vertices.data);
			m_vertices.size = size;
			m_vertices.count = count;

			break;
		case 1: // colors
			SAFE_ARR_DELETE(m_colors.data);
			m_colors.data = new float[size];
			std::copy(data, data + size, m_colors.data);
			m_colors.size = size;
			m_colors.count = count;

			break;
		case 2: // texture
			SAFE_ARR_DELETE(m_texture.data);
			m_texture.data = new float[size];
			std::copy(data, data + size, m_texture.data);
			m_texture.size = size;
			m_texture.count = count;

			break;
		case 3: // normals
			SAFE_ARR_DELETE(m_normals.data);
			m_normals.data = new float[size];
			std::copy(data, data + size, m_normals.data);
			m_normals.size = size;
			m_normals.count = count;

			break;
		}

		m_dirty = true;
	}

	GLuint m_vbo, m_vao;
	int m_size;
	mutable bool m_active;
	Data m_vertices;
	Data m_colors;
	Data m_texture;
	Data m_normals;
	bool m_dirty;
	IProgram* m_program;
};

MeshOpenGL::MeshOpenGL(const string& name) :
	IMesh(name), m_impl(new MeshOpenGLPrivate())
{
}

MeshOpenGL::~MeshOpenGL()
{
	SAFE_DELETE(m_impl);
}

int MeshOpenGL::count() const
{
	return m_impl->count();
}

void
MeshOpenGL::activate()
{
	m_impl->activate();
}

bool
MeshOpenGL::isActive() const
{
	return m_impl->isActive();
}

void
MeshOpenGL::deactivate() const
{
	m_impl->deactivate();
}

void
MeshOpenGL::setProgram(IProgram* program)
{
	m_impl->setProgram(program);
}

void
MeshOpenGL::setVertices(const unsigned int size, const unsigned int count,
		const float* data)
{
	m_impl->setVertices(data, size, count);
}

void
MeshOpenGL::setVertices(const unsigned int size, const unsigned int count,
		std::initializer_list<float> data)
{
	m_impl->setVertices(data.begin(), size, count);
}

void
MeshOpenGL::setColors(const unsigned int size, const unsigned int count,
		const float* data)
{
	m_impl->setColors(data, size, count);
}

void
MeshOpenGL::setColors(const unsigned int size, const unsigned int count,
		std::initializer_list<float> data)
{
	m_impl->setColors(data.begin(), size, count);
}

void
MeshOpenGL::setTexture(const unsigned int size, const unsigned int count,
		const float* data)
{
	m_impl->setTexture(data, size, count);
}

void
MeshOpenGL::setTexture(const unsigned int size, const unsigned int count,
		std::initializer_list<float> data)
{
	m_impl->setTexture(data.begin(), size, count);
}

void
MeshOpenGL::setNormals(const unsigned int size, const unsigned int count,
		const float* data)
{
	m_impl->setNormals(data, size, count);
}

void
MeshOpenGL::setNormals(const unsigned int size, const unsigned int count,
		std::initializer_list<float> data)
{
	m_impl->setNormals(data.begin(), size, count);
}

}

