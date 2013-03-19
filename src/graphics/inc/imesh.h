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

	virtual void activate() const = 0;
	virtual bool isActive() const = 0;
	virtual int count() const = 0;
	virtual void deactivate() const = 0;
	virtual VertexFormat format() const = 0;
	virtual void init(const IProgram&, const float*, const MeshUsageHint,
			const VertexFormat, const int) = 0;
};

}

#endif /* end of include guard: IMESH_H_W4FDKTY7 */

