#ifndef MANAGED_H_V6R2GJOK
#define MANAGED_H_V6R2GJOK

#include "base.h"
#include "core/Identity"

/*!
 * \brief Managed class declaration.
 */
class Managed : public Identity {
public:
	void addRef();
	void release();
	int  refCount() const;

protected:
	Managed();
	Managed(const Managed& other);
	virtual ~Managed();

private:
	int m_refCount;
};

#endif /* end of include guard: MANAGED_H_V6R2GJOK */

