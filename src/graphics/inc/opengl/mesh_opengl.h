#ifndef MESH_OPENGL_H_K4YSTC7O
#define MESH_OPENGL_H_K4YSTC7O

#include "graphics/Global"
#include "graphics/IMesh"

namespace bk {

class MeshOpenGL : public IMesh {
public:
	virtual ~MeshOpenGL();

	int count() const;
	void activate();
	bool isActive() const;
	void deactivate() const;

	void render();
	void setProgram(IProgram*);
	void setVertices(const unsigned int, const unsigned int, const float*);
	void setVertices(const unsigned int, const unsigned int, std::initializer_list<float>);
	void setColors(const unsigned int, const unsigned int, const float*);
	void setColors(const unsigned int, const unsigned int, std::initializer_list<float>);
	void setTexture(const unsigned int, const unsigned int, const float*);
	void setTexture(const unsigned int, const unsigned int, std::initializer_list<float>);
	void setNormals(const unsigned int, const unsigned int, const float*);
	void setNormals(const unsigned int, const unsigned int, std::initializer_list<float>);

private:
	MeshOpenGL(const string&);
	friend class Graphics;
	BK_IMPL(MeshOpenGL);
};

}

#endif /* end of include guard: MESH_OPENGL_H_K4YSTC7O */

