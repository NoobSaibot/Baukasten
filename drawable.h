#ifndef OBJECT_H_DPFT5OLZ
#define OBJECT_H_DPFT5OLZ

#include "base.h"

class Drawable {
public:
	Drawable() {}
	virtual ~Drawable() {}

	void setId(const GLuint id) { m_id = id; }
	GLuint id() const { return m_id; }
private:
	GLuint m_id;
};

#endif /* end of include guard: OBJECT_H_DPFT5OLZ */

