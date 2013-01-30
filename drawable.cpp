#include "drawable.h"

int Drawable::m_nextId = 0;

Drawable::Drawable() :
	m_id(m_nextId++)
{
}

Drawable::~Drawable()
{
	--m_nextId;
}

void Drawable::setId(const int id)
{
	m_id = id;
}

int Drawable::id() const
{
	return m_id;
}
