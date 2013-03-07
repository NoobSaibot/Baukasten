#ifndef MESH_OPENGL_H_K4YSTC7O
#define MESH_OPENGL_H_K4YSTC7O

#include "base.h"
#include "graphics/IMesh"

namespace bk {

class MeshOpenGL : public IMesh {
public:
	virtual ~MeshOpenGL();

	void init(const IProgram&, const float*, const MeshUsageHint,
			const VertexFormat, const int);
	VertexFormat format() const;
	int count() const;
	void activate() const;
	bool isActive() const;
	void deactivate() const;

private:
	MeshOpenGL(const string&);
	friend class Mesh;
	BK_IMPL(MeshOpenGL);
};

}

#endif /* end of include guard: MESH_OPENGL_H_K4YSTC7O */

