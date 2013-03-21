#ifndef INPUT_OPENGL_H_AYMGN0Q6
#define INPUT_OPENGL_H_AYMGN0Q6

#include "input/Global"
#include "input/IInput"

namespace bk {

/*!
 * \brief InputOpenGL class declaration.
 */
class InputOpenGL : public IInput {
public:
	InputOpenGL();
	virtual ~InputOpenGL();

	bool keyPressed(const char);

private:
	BK_IMPL(InputOpenGL);
};
} /* bk */

#endif /* end of include guard: INPUT_OPENGL_H_AYMGN0Q6 */

