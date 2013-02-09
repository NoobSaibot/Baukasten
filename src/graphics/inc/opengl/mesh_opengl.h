#ifndef MESH_OPENGL_H_K4YSTC7O
#define MESH_OPENGL_H_K4YSTC7O

#include "base.h"
#include "graphics/IMesh"

class MeshOpenGLPrivate;

/*!
 * \brief MeshOpengl class declaration.
 */
class MeshOpenGL : public IMesh {
public:
	MeshOpenGL();
	virtual ~MeshOpenGL();

	void init(const IProgram&, const float*, const UsageHint, const VertexFormat, const int);
	VertexFormat format() const;
	int count() const;
	void activate() const;
	bool isActive() const;
	void deactivate() const;

private:
	friend class MeshOpenGLPrivate;
	MeshOpenGLPrivate* m_impl;
};

#endif /* end of include guard: MESH_OPENGL_H_K4YSTC7O */

