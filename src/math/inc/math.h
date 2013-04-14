#ifndef MATH_H_DQPIGMC3
#define MATH_H_DQPIGMC3

#include "math/Global"

namespace bk {

/*!
 * \brief Math class declaration.
 */
class Math {
public:
	static Matrix rotate(const f32, const f32, const f32, const f32);
	static Matrix scale(const f32, const f32, const f32);
	static Matrix translate(const f32, const f32, const f32);

	static f32 random(f32*);
	static f32 degToRad(const f32, f32*);
};

} /* bk */

#endif /* end of include guard: MATH_H_DQPIGMC3 */

