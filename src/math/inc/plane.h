#ifndef PLANE_H_RJLFB7HP
#define PLANE_H_RJLFB7HP

#include "math/Global"
#include "math/Vector3"

namespace bk {

/*!
 * \brief Plane class declaration.
 */
class Plane {
public:
	Plane();
	Plane( const f32, const f32, const f32, const f32 );
	virtual ~Plane();

	f32      distance() const;
	Vector3  normal() const;
	void     setDistance( const f32 );
	void     setNormal( const Vector3& );

private:
	Vector3 m_normal;
	f32     m_distance;
};

} /* bk */

#endif /* end of include guard: PLANE_H_RJLFB7HP */

