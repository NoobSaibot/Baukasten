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
	void render(const u32, const u32 offset = 0);
	void setProgram(IProgram*);
	void addVertices(const u32, const f32*);
	void setVertices(const u32, const u32, const f32*);
	void addVertices(const u32, std::initializer_list<f32>);
	void setVertices(const u32, const u32, std::initializer_list<f32>);
	void setColors(const u32, const u32, const f32*);
	void setColors(const u32, const u32, std::initializer_list<f32>);
	void setTexture(const u32, const u32, const f32*);
	void setTexture(const u32, const u32, std::initializer_list<f32>);
	void setNormals(const u32, const u32, const f32*);
	void setNormals(const u32, const u32, std::initializer_list<f32>);
	void setIndices(const u32, const u16*);
	void setIndices(const u32, std::initializer_list<u16>);

private:
	MeshOpenGL(const string&);
	friend class Graphics;
	BK_IMPL(MeshOpenGL);
};

}

#endif /* end of include guard: MESH_OPENGL_H_K4YSTC7O */

