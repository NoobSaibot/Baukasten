#include "input/inc/opengl/input_opengl.h"

#include <GL/glfw.h>

namespace bk {

class InputOpenGLPrivate {
public:
	bool keyPressed(const char key)
	{
		return glfwGetKey(key);
	}
};

InputOpenGL::InputOpenGL() :
	m_impl(new InputOpenGLPrivate())
{
}

InputOpenGL::~InputOpenGL()
{
	SAFE_DELETE(m_impl);
}

bool
InputOpenGL::keyPressed(const char key)
{
	return m_impl->keyPressed(key);
}

} /*  bk */
