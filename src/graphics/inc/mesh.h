#ifndef MESH_H_1SNIHXRL
#define MESH_H_1SNIHXRL

#include "base.h"
#include "graphics/IMesh"
#include "graphics/VertexFormat"

namespace bk {

class IProgram;

class Mesh {
public:
	static shared_ptr<IMesh> create(const string&, const IProgram&,
			const float*, const IMesh::UsageHint, const VertexFormat, const int);
	static shared_ptr<IMesh> createQuad(const string&, const IProgram&,
			const float, const float, const float);
	static shared_ptr<IMesh> createRect(const string&, const IProgram&,
			const float, const float, const float, const float);
};

}

#endif /* end of include guard: MESH_H_1SNIHXRL */

