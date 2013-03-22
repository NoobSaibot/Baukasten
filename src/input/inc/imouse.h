#ifndef IMOUSE_H_U3MKVP5K
#define IMOUSE_H_U3MKVP5K

#include "input/Global"

namespace bk {

/*!
 * \brief IMouse class declaration.
 */
class IMouse {
public:
	virtual void position(int*, int*) const = 0;
	virtual void setPosition(const int, const int) = 0;
};

} /* bk */

#endif /* end of include guard: IMOUSE_H_U3MKVP5K */

