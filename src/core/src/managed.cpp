#include "core/Managed"

namespace bk {

class ManagedPrivate {
public:
	ManagedPrivate(Managed* this_) :
		m_refCount(1), m_this(this_)
	{
	}

	~ManagedPrivate()
	{
	}

	void addRef()
	{
		m_refCount++;
	}

	void release()
	{
		BK_DEBUG("id: " << m_this->id() << " type: " << m_this->type() << " name: " << m_this->name() << " - refs: " << m_refCount);
		--m_refCount;
		if (m_refCount <= 0) {
			BK_DEBUG("\tdeleting " << m_this->id());
			SAFE_DELETE(m_this);
		}
	}

	int refCount() const
	{
		return m_refCount;
	}

private:
	int m_refCount;
	Managed* m_this;
};

Managed::Managed(const string& name) :
	Identity(name),
	m_impl(new ManagedPrivate(this))
{
}

Managed::Managed(const string& name, const string& type) :
	Identity(name, type),
	m_impl(new ManagedPrivate(this))
{
}

Managed::Managed(const Managed& other) :
	Identity(other.name())
{
	if (this == &other) return;
	delete m_impl;
	m_impl = other.m_impl;
}

Managed::~Managed()
{
	SAFE_DELETE(m_impl);
}

void Managed::addRef()
{
	m_impl->addRef();
}

int Managed::refCount() const
{
	return m_impl->refCount();
}

void Managed::release()
{
	m_impl->release();
}

}

