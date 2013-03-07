#include "graphics/inc/opengl/display_opengl.h"

namespace bk {

class DisplayOpenGLPrivate {
public:
	void init(const int width, const int height)
	{
		m_width = width;
		m_height = height;

		glfwInit();

		glfwOpenWindowHint(GLFW_OPENGL_VERSION_MAJOR, 3);
		glfwOpenWindowHint(GLFW_OPENGL_VERSION_MINOR, 0);
		glfwOpenWindowHint(GLFW_WINDOW_NO_RESIZE, GL_TRUE);
		glfwOpenWindow(width, height, 8, 8, 8, 8, 16, 0, GLFW_WINDOW);

		glewInit();
		BK_GL_ASSERT(glViewport(0, 0, width, height));

		glfwDisable(GLFW_MOUSE_CURSOR);
		glfwSetMousePos(0, 0);
		glfwSetMouseWheel(0);
	}

	void clear()
	{
		BK_GL_ASSERT(glClearColor(0, 0, 0, 1));
		BK_GL_ASSERT(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));
	}

	void display()
	{
		BK_GL_ASSERT(glfwSwapBuffers());
	}

private:
	int m_width, m_height;
};

DisplayOpenGL::DisplayOpenGL() :
	m_impl(new DisplayOpenGLPrivate())
{
}

DisplayOpenGL::~DisplayOpenGL()
{
	SAFE_DELETE(m_impl);
}

void
DisplayOpenGL::clear()
{
	m_impl->clear();
}

void
DisplayOpenGL::display()
{
	m_impl->display();
}

void
DisplayOpenGL::init(const int width, const int height)
{
	m_impl->init(width, height);
}

void
DisplayOpenGL::setBackgroundColor(const float r, const float g, const float b)
{
}

} /* bk */
