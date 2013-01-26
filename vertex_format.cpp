#include "vertex_format.h"

VertexFormat::VertexFormat(initializer_list<VertexFormat::Data> list) :
	m_size(0)
{
	m_elements = list;
	for (Data d: list) {
		m_size += d.size;
	}
}

VertexFormat::~VertexFormat()
{
}

int VertexFormat::size() const
{
	return m_size;
}

vector<VertexFormat::Data> VertexFormat::elements() const
{
	return m_elements;
}

