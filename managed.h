#ifndef MANAGED_H_V6R2GJOK
#define MANAGED_H_V6R2GJOK

#include "base.h"
#include "identity.h"

/*!
 * \brief Managed class declaration.
 */
class Managed : public Identity {
public:
	void add();
	void release();
	int  count() const;

protected:
	Managed();
	Managed(const Managed& other);
	virtual ~Managed();

private:
	int m_refCount;
};

#endif /* end of include guard: MANAGED_H_V6R2GJOK */

