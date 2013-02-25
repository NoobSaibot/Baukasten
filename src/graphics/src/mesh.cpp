#include "graphics/Mesh"

#include "graphics/MeshImpl"

namespace bk {

shared_ptr<IMesh>
Mesh::create(const string& name, const IProgram& program, const float* data,
		const IMesh::UsageHint hint, const VertexFormat format, const int size)
{
	shared_ptr<MeshImpl> impl(new MeshImpl(name));
	impl->init(program, data, hint, format, size);
	return impl;
}

shared_ptr<IMesh>
Mesh::createQuad(const string& name, const IProgram& program,
		const float x, const float y, const float width)
{
	return createRect(name, program, x, y, width, width);
}

shared_ptr<IMesh>
Mesh::createRect(const string& name, const IProgram& program, const float x,
		const float y, const float width, const float height)
{
	shared_ptr<MeshImpl> impl(new MeshImpl(name));

	VertexFormat format = {
		VertexFormat::Data(VertexFormat::POSITION, 3, 0),
		VertexFormat::Data(VertexFormat::TEXCOORD0, 2, 3)
	};

	float vertices[] = {
		// x       y            z    tex-x tex-y
		x + width, y,          0.0f, 1.0f, 1.0f,
		x + width, y + height, 0.0f, 1.0f, 0.0f,
		x,         y,          0.0f, 0.0f, 1.0f,
		x + width, y + height, 0.0f, 1.0f, 0.0f,
		x,         y + height, 0.0f, 0.0f, 0.0f,
		x,         y,          0.0f, 0.0f, 1.0f
	};

	impl->init(program, vertices, IMesh::STATIC, format, sizeof(vertices));
	return impl;
}

} // bk

