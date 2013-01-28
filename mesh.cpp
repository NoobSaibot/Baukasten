#include "mesh.h"

#include "MeshImpl"

Mesh::Mesh()
{
}

Mesh::~Mesh()
{
}

IMesh* Mesh::create(const float* data, const IMesh::UsageHint hint,
		const VertexFormat format, const int size)
{
	BK_ASSERT(data != 0);
		( (hint == DYNAMIC) ? GL_DYNAMIC_DRAW : GL_STREAM_DRAW );

	MeshImpl* impl = new MeshImpl();
	impl->init(data, hint, format, size);
	return impl;
}
