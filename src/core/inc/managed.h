#ifndef MANAGED_H_V6R2GJOK
#define MANAGED_H_V6R2GJOK

#include "core/Global"
#include "core/Identity"

namespace bk {

class Managed : public Identity {
public:
	void addRef();
	void release();
	int  refCount() const;

	Managed(const string&);
	Managed(const string&, const string&);
	Managed(const Managed& other);
	virtual ~Managed();

private:
	BK_IMPL(Managed);
};

}

#endif /* end of include guard: MANAGED_H_V6R2GJOK */

