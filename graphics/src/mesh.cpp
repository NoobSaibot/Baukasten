#include "graphics/Mesh"

#include "graphics/MeshImpl"

IMesh* Mesh::create(const float* data, const IMesh::UsageHint hint,
		const VertexFormat format, const int size)
{
	MeshImpl* impl = new MeshImpl();
	impl->init(data, hint, format, size);
	return impl;
}
