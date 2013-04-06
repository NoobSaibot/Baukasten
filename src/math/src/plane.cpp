#include "math/Plane"

namespace bk {

Plane::Plane()
{
}

Plane::Plane( const f32 x, const f32 y, const f32 z, const f32 d ) :
	m_normal({ x, y, z }),
	m_distance( d )
{
}

Plane::~Plane()
{
}

f32
Plane::distance() const
{
	return m_distance;
}

Vector3
Plane::normal() const
{
	return m_normal;
}

void
Plane::setDistance( const f32 distance )
{
	m_distance = distance;
}

void
Plane::setNormal( const Vector3 &normal )
{
	BK_ASSERT( normal.mag() == 1.0, "vector has to be normalised." );
	m_normal = normal;
}

}

