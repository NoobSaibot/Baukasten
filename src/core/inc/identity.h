#ifndef OBJECT_H_DPFT5OLZ
#define OBJECT_H_DPFT5OLZ

#include "base.h"

namespace bk {

class Identity {
public:
	Identity(const string&, const string& type = "Unknown");
	virtual ~Identity();

	int id() const;
	string name() const;
	string type() const;

private:
	int m_id;
	string m_name;
	string m_type;
	static int m_nextId;
};

}

#endif /* end of include guard: OBJECT_H_DPFT5OLZ */

