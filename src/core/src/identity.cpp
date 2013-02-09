#include "core/Identity"

int Identity::m_nextId = 0;

Identity::Identity() :
	m_id(m_nextId++)
{
}

Identity::~Identity()
{
	--m_nextId;
}

void Identity::setId(const int id)
{
	m_id = id;
}

int Identity::id() const
{
	return m_id;
}
