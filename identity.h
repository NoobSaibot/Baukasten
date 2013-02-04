#ifndef OBJECT_H_DPFT5OLZ
#define OBJECT_H_DPFT5OLZ

#include "base.h"

class Identity {
public:
	Identity();
	virtual ~Identity();

	int id() const;
	void setId(const int);
private:
	int m_id;
	static int m_nextId;
};

#endif /* end of include guard: OBJECT_H_DPFT5OLZ */

