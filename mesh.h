#ifndef MESH_H_1SNIHXRL
#define MESH_H_1SNIHXRL

#include "base.h"
#include "drawable.h"
#include "vertex_format.h"

/*!
 * \brief Mesh class declaration.
 */
class Mesh : public Drawable {
public:
	enum UsageHint {
		DYNAMIC, STATIC, STREAM
	};

	static Mesh* createMesh(const float*, const UsageHint, const VertexFormat, const int);

	VertexFormat format() const;
	int count() const;

	void activate() const;
	void deactivate() const;

private:
	Mesh(const VertexFormat, const int);
	virtual ~Mesh();

	float* m_data[];
	int m_size;
	VertexFormat m_format;
	GLint m_vao;
};

#endif /* end of include guard: MESH_H_1SNIHXRL */

