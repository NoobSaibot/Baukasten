#ifndef IINPUT_H_ETONQS2B
#define IINPUT_H_ETONQS2B

#include "input/Global"

namespace bk {

/*!
 * \brief IInput class declaration.
 */
class IInput {
public:
	virtual bool keyPressed(const char) = 0;
};

} /* bk */

#endif /* end of include guard: IINPUT_H_ETONQS2B */

