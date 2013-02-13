#ifndef MANAGED_H_V6R2GJOK
#define MANAGED_H_V6R2GJOK

#include "base.h"
#include "core/Identity"

class ManagedPrivate;

/*!
 * \brief Managed class declaration.
 */
class Managed : public Identity {
public:
	void addRef();
	void release();
	int  refCount() const;

	Managed(const string&);
	Managed(const Managed& other);
	virtual ~Managed();

private:
	friend class ManagedPrivate;
	ManagedPrivate* m_impl;
};

#endif /* end of include guard: MANAGED_H_V6R2GJOK */

