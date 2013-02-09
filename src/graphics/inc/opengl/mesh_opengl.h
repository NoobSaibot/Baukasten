#ifndef MESH_OPENGL_H_K4YSTC7O
#define MESH_OPENGL_H_K4YSTC7O

#include "base.h"
#include "graphics/IMesh"

class MeshOpenglPrivate;

/*!
 * \brief MeshOpengl class declaration.
 */
class MeshOpengl : public IMesh {
public:
	MeshOpengl();
	virtual ~MeshOpengl();

	void init(const IProgram&, const float*, const UsageHint, const VertexFormat, const int);
	VertexFormat format() const;
	int count() const;
	void activate() const;
	void deactivate() const;

private:
	friend class MeshOpenglPrivate;
	MeshOpenglPrivate* m_impl;
};

#endif /* end of include guard: MESH_OPENGL_H_K4YSTC7O */

