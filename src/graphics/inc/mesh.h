#ifndef MESH_H_1SNIHXRL
#define MESH_H_1SNIHXRL

#include "base.h"
#include "graphics/IMesh"
#include "graphics/VertexFormat"

class IProgram;

/*!
 * \brief Mesh class declaration.
 */
class Mesh {
public:
	static IMesh* create(const IProgram&, const float*, const IMesh::UsageHint,
			const VertexFormat, const int);
};

#endif /* end of include guard: MESH_H_1SNIHXRL */

