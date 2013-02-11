#include "graphics/Mesh"

#include "graphics/MeshImpl"

shared_ptr<IMesh>
Mesh::create(const IProgram& program, const float* data,
		const IMesh::UsageHint hint, const VertexFormat format, const int size)
{
	shared_ptr<MeshImpl> impl(new MeshImpl());
	impl->init(program, data, hint, format, size);
	return impl;
}

