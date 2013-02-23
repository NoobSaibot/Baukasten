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

} // bk

