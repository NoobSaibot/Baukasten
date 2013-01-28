#ifndef MESH_H_1SNIHXRL
#define MESH_H_1SNIHXRL

#include "base.h"
#include "drawable.h"
#include "imesh.h"
#include "vertex_format.h"

/*!
 * \brief Mesh class declaration.
 */
class Mesh : public Drawable {
public:
	static IMesh* create(const float*, const IMesh::UsageHint, const VertexFormat, const int);

private:
	Mesh();
	virtual ~Mesh();
};

#endif /* end of include guard: MESH_H_1SNIHXRL */

