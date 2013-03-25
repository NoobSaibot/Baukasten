#ifndef MOUSE_OPENGL_H_PQCIEWHK
#define MOUSE_OPENGL_H_PQCIEWHK

#include "input/Global"
#include "input/IMouse"

namespace bk {

/*!
 * \brief MouseOpenGL class declaration.
 */
class MouseOpenGL : public IMouse {
public:
	MouseOpenGL();
	virtual ~MouseOpenGL();

	void position(int*, int*) const;
	void setPosition(const int, const int);
	void update();

private:
	BK_IMPL(MouseOpenGL);
};

} /* bk */

#endif /* end of include guard: MOUSE_OPENGL_H_PQCIEWHK */

