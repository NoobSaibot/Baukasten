#ifndef IMESH_H_W4FDKTY7
#define IMESH_H_W4FDKTY7

#include "core/Managed"
#include "graphics/Global"

namespace bk {

class IProgram;
class VertexFormat;

class IMesh : public Managed {
public:
	IMesh(const string& name) : Managed(name, "Mesh"),
		m_type( PrimitiveType::TRIANGLES ) {}

	virtual void activate() = 0;
	virtual bool isActive() const = 0;
	virtual int count() const = 0;
	virtual void deactivate() const = 0;

	virtual void render() = 0;
	virtual void render(const u32, const u32 offset = 0) = 0;
	virtual void setProgram(IProgram*) = 0;
	virtual void addVertices(const u32, const f32*) = 0;
	virtual void setVertices(const u32, const u32, const f32*) = 0;
	virtual void addVertices(const u32, std::initializer_list<f32>) = 0;
	virtual void setVertices(const u32, const u32, std::initializer_list<f32>) = 0;
	virtual void setColors(const u32, const u32, const f32*) = 0;
	virtual void setColors(const u32, const u32, std::initializer_list<f32>) = 0;
	virtual void setTexture(const u32, const u32, const f32*) = 0;
	virtual void setTexture(const u32, const u32, std::initializer_list<f32>) = 0;
	virtual void setNormals(const u32, const u32, const f32*) = 0;
	virtual void setNormals(const u32, const u32, std::initializer_list<f32>) = 0;
	virtual void setIndices(const u32, const u16*) = 0;
	virtual void setIndices(const u32, std::initializer_list<u16>) = 0;

	void setPrimitiveType(PrimitiveType type) { m_type = type; }
	PrimitiveType primitiveType() const { return m_type; }
private:
	PrimitiveType m_type;
};

}

#endif /* end of include guard: IMESH_H_W4FDKTY7 */

