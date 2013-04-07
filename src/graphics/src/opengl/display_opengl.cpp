#include "graphics/inc/opengl/display_opengl.h"

#include "core/Assert"

#include "graphics/inc/opengl/assert_opengl.h"

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
		glfwSwapBuffers();
	}

	void setBGColor(f32 r, f32 g, f32 b)
	{
		m_r = r; m_g = g; m_b = b;
	}

	void exit()
	{
		glfwCloseWindow();
	}

	u16 width() const
	{
		return m_width;
	}

	u16 height() const
	{
		return m_height;
	}

private:
	u16 m_width, m_height;
	f32 m_r, m_g, m_b;
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
DisplayOpenGL::exit()
{
	m_impl->exit();
}

void
DisplayOpenGL::init(const u16 width, const u16 height)
{
	m_impl->init(width, height);
}

void
DisplayOpenGL::setBackgroundColor(const f32 r, const f32 g, const f32 b)
{
	m_impl->setBGColor(r, g, b);
}

u16
DisplayOpenGL::width() const
{
	return m_impl->width();
}

u16
DisplayOpenGL::height() const
{
	return m_impl->height();
}

} /* bk */
