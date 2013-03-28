#ifndef IMESH_H_W4FDKTY7
#define IMESH_H_W4FDKTY7

#include "core/Managed"
#include "graphics/Global"

namespace bk {

class IProgram;
class VertexFormat;

class IMesh : public Managed {
public:
	IMesh(const string& name) : Managed(name, "Mesh") {}

	virtual void activate() = 0;
	virtual bool isActive() const = 0;
	virtual int count() const = 0;
	virtual void deactivate() const = 0;

	virtual void setProgram(IProgram*) = 0;
	virtual void setVertices(const unsigned int, const unsigned int, const float*) = 0;
	virtual void setVertices(const unsigned int, const unsigned int, std::initializer_list<float>) = 0;
	virtual void setColors(const unsigned int, const unsigned int, const float*) = 0;
	virtual void setColors(const unsigned int, const unsigned int, std::initializer_list<float>) = 0;
	virtual void setTexture(const unsigned int, const unsigned int, const float*) = 0;
	virtual void setTexture(const unsigned int, const unsigned int, std::initializer_list<float>) = 0;
	virtual void setNormals(const unsigned int, const unsigned int, const float*) = 0;
	virtual void setNormals(const unsigned int, const unsigned int, std::initializer_list<float>) = 0;
};

}

#endif /* end of include guard: IMESH_H_W4FDKTY7 */

