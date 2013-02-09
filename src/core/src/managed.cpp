#include "core/Managed"

Managed::Managed() :
	m_refCount(0)
{
}

Managed::Managed(const Managed& other) :
	m_refCount(0)
{
}

Managed::~Managed()
{
}

void Managed::addRef()
{
	++m_refCount;
}

int Managed::refCount() const
{
	return m_refCount;
}

void Managed::release()
{
	BK_DEBUG("id: " << id() << " - refs: " << m_refCount);
	if (--m_refCount <= 0) {
		BK_DEBUG("\tdeleting " << id());
		delete this;
	}
}

