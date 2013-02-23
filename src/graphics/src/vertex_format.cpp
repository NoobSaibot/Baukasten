#include "graphics/VertexFormat"

namespace bk {

VertexFormat::VertexFormat() :
	m_size(0)
{
}

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

void VertexFormat::operator=(const VertexFormat& other)
{
	m_elements = other.elements();
	m_size = other.size();
}

}

