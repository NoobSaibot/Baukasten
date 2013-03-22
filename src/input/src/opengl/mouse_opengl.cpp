#include "input/inc/opengl/mouse_opengl.h"

#include <GL/glfw.h>

namespace bk {

class MouseOpenGLPrivate {
public:
	MouseOpenGLPrivate()
	{
	}

	~MouseOpenGLPrivate()
	{
	}

	void position(int* x, int* y) const
	{
		glfwGetMousePos(x, y);
	}

	void setPosition(const int x, const int y)
	{
		glfwSetMousePos(x, y);
	}

private:
	/* data */
};

MouseOpenGL::MouseOpenGL() :
	m_impl(new MouseOpenGLPrivate())
{
}

MouseOpenGL::~MouseOpenGL()
{
	SAFE_DELETE(m_impl);
}

void
MouseOpenGL::position(int* x, int* y) const
{
	m_impl->position(x, y);
}

void
MouseOpenGL::setPosition(const int x, const int y)
{
	m_impl->setPosition(x, y);
}

} /* bk */
