#ifndef OBJECT_H_DPFT5OLZ
#define OBJECT_H_DPFT5OLZ

#include "base.h"

class Drawable {
public:
	Drawable();
	virtual ~Drawable();

	void setId(const int id);
	int id() const;
private:
	int m_id;
	static int m_nextId;
};

#endif /* end of include guard: OBJECT_H_DPFT5OLZ */

