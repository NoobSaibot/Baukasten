#include "input/inc/opengl/keyboard_opengl.h"

#include <GL/glfw.h>

namespace bk {

class KeyboardOpenGLPrivate {
public:
	KeyboardOpenGLPrivate()
	{
	}

	~KeyboardOpenGLPrivate()
	{
	}

	bool keyPressed(const char key) const
	{
		return glfwGetKey(key);
	}
};

KeyboardOpenGL::KeyboardOpenGL() :
	m_impl(new KeyboardOpenGLPrivate())
{
}

KeyboardOpenGL::~KeyboardOpenGL()
{
	SAFE_DELETE(m_impl);
}

bool
KeyboardOpenGL::keyPressed(const char key) const
{
	return m_impl->keyPressed(key);
}

} /* bk */
