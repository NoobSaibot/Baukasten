#ifndef MESH_H_1SNIHXRL
#define MESH_H_1SNIHXRL

#include "base.h"
#include "imesh.h"
#include "vertex_format.h"

/*!
 * \brief Mesh class declaration.
 */
class Mesh {
public:
	static IMesh* create(const float*, const IMesh::UsageHint, const VertexFormat, const int);
};

#endif /* end of include guard: MESH_H_1SNIHXRL */

