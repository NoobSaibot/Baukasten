#include "core/Managed"

Managed::Managed() :
	m_refCount(1)
{
}

Managed::Managed(const Managed& other) :
	m_refCount(1)
{
}

Managed::~Managed()
{
}

void Managed::addRef()
{
	++m_refCount;
}

int Managed::count() const
{
	return m_refCount;
}

void Managed::release()
{
	if (--m_refCount <= 0) {
		delete this;
	}
}

