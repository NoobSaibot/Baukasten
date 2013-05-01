#include "graphics/inc/opengl/mesh_opengl.h"

#include "core/Assert"
#include "graphics/IProgram"

#include "graphics/inc/opengl/assert_opengl.h"

#include <algorithm>

namespace {
template<typename T>
struct Data {
	Data() : data(nullptr), size(0), count(0)
	{
	}

	int byteSize()
	{
		return size * sizeof(T);
	}

	T* data;
	u32 size;
	u32 count;
};

static void
_set_attrib(const bk::IProgram* program, Data<f32> d,
		const string& attrib, int stride, u32 offset)
{
	GLint pos;
	pos = program->attrib(attrib.c_str());
	BK_GL_ASSERT(glVertexAttribPointer(
		pos, d.count, GL_FLOAT, GL_FALSE, stride, (const GLvoid*)(offset)
	));
	BK_GL_ASSERT(glEnableVertexAttribArray(pos));
}

static GLenum _bk_toGLType(bk::PrimitiveType type)
{
	switch ( type ) {
	case bk::PrimitiveType::PATCHES:         return GL_PATCHES;
	case bk::PrimitiveType::POINTS:          return GL_POINTS;
	case bk::PrimitiveType::LINES:           return GL_LINES;
	case bk::PrimitiveType::LINE_LOOP:       return GL_LINE_LOOP;
	case bk::PrimitiveType::LINE_STRIP:      return GL_LINE_STRIP;
	case bk::PrimitiveType::TRIANGLES:       return GL_TRIANGLES;
	case bk::PrimitiveType::TRIANGLE_FAN:    return GL_TRIANGLE_FAN;
	case bk::PrimitiveType::TRIANGLE_STRIP:  return GL_TRIANGLE_STRIP;
	}
	return GL_TRIANGLES;
}
}

namespace bk {

class MeshOpenGLPrivate {
public:
	MeshOpenGLPrivate(IMesh* mesh) : m_vbo(0), m_vao(0), m_active(false), m_dirty(false),
		m_program(nullptr), m_mesh(mesh), m_drawIndexed(false)
	{
		BK_GL_ASSERT( glGenVertexArrays(1, &m_vao) );
		BK_GL_ASSERT( glGenBuffers(1, &m_vbo) );
		BK_GL_ASSERT( glGenBuffers(1, &m_eabo) );
	}

	virtual ~MeshOpenGLPrivate()
	{
		BK_GL_ASSERT(glDeleteBuffers(1, &m_vbo));
		BK_GL_ASSERT(glDeleteBuffers(1, &m_eabo));
		BK_GL_ASSERT(glDeleteVertexArrays(1, &m_vao));
		SAFE_ARR_DELETE(m_vertices.data);
		SAFE_ARR_DELETE(m_colors.data);
		SAFE_ARR_DELETE(m_texture.data);
		SAFE_ARR_DELETE(m_normals.data);
		SAFE_ARR_DELETE(m_indices.data);
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

		BK_GL_ASSERT( glBindVertexArray(m_vao) );
		BK_GL_ASSERT( glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_eabo) );
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
		BK_GL_ASSERT(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));

		m_active = false;
	}

	void render(const u32 count, const u32 offset)
	{
		auto type = _bk_toGLType(m_mesh->primitiveType());

		if ( m_drawIndexed ) {
			BK_GL_ASSERT(glDrawElements(type, m_indices.size, GL_UNSIGNED_BYTE, (GLvoid*)0));
		} else {
			BK_GL_ASSERT(glDrawArrays(type, offset, count));
		}
	}

	void setProgram(IProgram* program)
	{
		m_program = program;
		m_program->addRef();
	}

	void setVertices(const f32* data, const u32 size,
			const u32 count)
	{
		setData(0, data, size, count);
	}

	void setColors(const f32* data, const u32 size,
			const u32 count)
	{
		setData(1, data, size, count);
	}

	void setTexture(const f32* data, const u32 size,
			const u32 count)
	{
		setData(2, data, size, count);
	}

	void setNormals(const f32* data, const u32 size,
			const u32 count)
	{
		setData(3, data, size, count);
	}

	void setIndices(const u16* data, const u32 size)
	{
		setData(4, data, size, 0);
	}

private:
	void initBuffer()
	{
		BK_ASSERT(m_program != nullptr, "Shader Program must be set.");

		BK_GL_ASSERT( glBindVertexArray(m_vao) );
		BK_GL_ASSERT( glBindBuffer(GL_ARRAY_BUFFER, m_vbo) );
		BK_GL_ASSERT( glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_eabo));

		// compute the size of data
		u32 size = m_vertices.byteSize() + m_colors.byteSize() +
			m_texture.byteSize() + m_normals.byteSize();

		// reserve memory for all the data that is actually
		// set (VERTICES, NORMALS, TEXTURE, ...)
		f32* data = new f32[size];

		// set everything to 0
		memset(data, 0, size * sizeof(f32));

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
		// have to keep the data around in case any of the fields is set -- therefor the
		// object is dirty -- and the glbuffer has to be repopulated with data again
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

		if (m_indices.data != nullptr) {
			m_drawIndexed = true;
			BK_GL_ASSERT( glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_indices.size,
				m_indices.data, GL_STATIC_DRAW ) );
		}

		m_dirty = false;
	}

	void setData(int type, const f32* data, const u32 size,
			const u32 count)
	{
		switch (type) {
		case 0: // vertices
			SAFE_ARR_DELETE(m_vertices.data);
			m_vertices.data = new f32[size];
			std::copy(data, data + size, m_vertices.data);
			m_vertices.size = size;
			m_vertices.count = count;

			break;
		case 1: // colors
			SAFE_ARR_DELETE(m_colors.data);
			m_colors.data = new f32[size];
			std::copy(data, data + size, m_colors.data);
			m_colors.size = size;
			m_colors.count = count;

			break;
		case 2: // texture
			SAFE_ARR_DELETE(m_texture.data);
			m_texture.data = new f32[size];
			std::copy(data, data + size, m_texture.data);
			m_texture.size = size;
			m_texture.count = count;

			break;
		case 3: // normals
			SAFE_ARR_DELETE(m_normals.data);
			m_normals.data = new f32[size];
			std::copy(data, data + size, m_normals.data);
			m_normals.size = size;
			m_normals.count = count;

			break;
		}

		m_dirty = true;
	}

	void setData(int type, const u16* data, const u32 size, const u32 count)
	{
		switch (type) {
		case 4: // indices
			SAFE_ARR_DELETE(m_indices.data);
			m_indices.data = new u16[size];
			std::copy(data, data + size, m_indices.data);
			m_indices.size = size;

			break;
		}

		m_dirty = true;
	}

	GLuint m_vbo, m_vao, m_eabo;
	int m_size;
	mutable bool m_active;
	Data<f32> m_vertices;
	Data<f32> m_colors;
	Data<f32> m_texture;
	Data<f32> m_normals;
	Data<u16> m_indices;
	bool m_dirty;
	IProgram* m_program;
	IMesh* m_mesh;
	bool m_drawIndexed;
};

MeshOpenGL::MeshOpenGL(const string& name) :
	IMesh(name), m_impl(new MeshOpenGLPrivate(this))
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
MeshOpenGL::render(const u32 count, const u32 offset)
{
	m_impl->render(count, offset);
}

void
MeshOpenGL::render()
{
	m_impl->render(count(), 0);
}

void
MeshOpenGL::setProgram(IProgram* program)
{
	m_impl->setProgram(program);
}

void
MeshOpenGL::setVertices(const u32 size, const u32 count,
		const f32* data)
{
	m_impl->setVertices(data, size, count);
}

void
MeshOpenGL::setVertices(const u32 size, const u32 count,
		std::initializer_list<f32> data)
{
	m_impl->setVertices(data.begin(), size, count);
}

void
MeshOpenGL::setColors(const u32 size, const u32 count,
		const f32* data)
{
	m_impl->setColors(data, size, count);
}

void
MeshOpenGL::setColors(const u32 size, const u32 count,
		std::initializer_list<f32> data)
{
	m_impl->setColors(data.begin(), size, count);
}

void
MeshOpenGL::setTexture(const u32 size, const u32 count,
		const f32* data)
{
	m_impl->setTexture(data, size, count);
}

void
MeshOpenGL::setTexture(const u32 size, const u32 count,
		std::initializer_list<f32> data)
{
	m_impl->setTexture(data.begin(), size, count);
}

void
MeshOpenGL::setNormals(const u32 size, const u32 count,
		const f32* data)
{
	m_impl->setNormals(data, size, count);
}

void
MeshOpenGL::setNormals(const u32 size, const u32 count,
		std::initializer_list<f32> data)
{
	m_impl->setNormals(data.begin(), size, count);
}

void
MeshOpenGL::setIndices(const u32 size, const u16* data)
{
	m_impl->setIndices(data, size);
}

void
MeshOpenGL::setIndices(const u32 size, std::initializer_list<u16> data)
{
	m_impl->setIndices(data.begin(), size);
}

}

