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
};

}

#endif /* end of include guard: MESH_H_1SNIHXRL */

