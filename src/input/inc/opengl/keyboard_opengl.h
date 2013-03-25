#ifndef KEYBOARD_OPENGL_H_MXXKVODC
#define KEYBOARD_OPENGL_H_MXXKVODC

#include "input/Global"
#include "input/IKeyboard"

namespace bk {

/*!
 * \brief KeyboardOpenGL class declaration.
 */
class KeyboardOpenGL : public IKeyboard {
public:
	KeyboardOpenGL();
	virtual ~KeyboardOpenGL();

	void update();

private:
	BK_IMPL(KeyboardOpenGL);
};

} /* bk */

#endif /* end of include guard: KEYBOARD_OPENGL_H_MXXKVODC */

