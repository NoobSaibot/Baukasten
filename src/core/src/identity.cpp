#include "core/Identity"

int Identity::m_nextId = 0;

Identity::Identity(const string& name, const string& type) :
	m_id(++m_nextId), m_name(name), m_type(type)
{
}

Identity::~Identity()
{
	BK_DEBUG("Identity::deleting (" << id() << "/" << m_nextId << ") - " << type() << " - " << name());
}

int Identity::id() const
{
	return m_id;
}

string
Identity::name() const
{
	return m_name;
}

string
Identity::type() const
{
	return m_type;
}

