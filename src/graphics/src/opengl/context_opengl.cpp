#include "graphics/inc/opengl/context_opengl.h"

#include "core/Assert"

#include "graphics/inc/opengl/assert_opengl.h"

namespace bk {

class ContextOpenGLPrivate {
public:
	ContextOpenGLPrivate(ContextOpenGL* object) :
		m_object(object)
	{
	}

	void activate()
	{
		if (m_object->option(ContextOption::ENABLE_3D)) {
			BK_GL_ASSERT(glEnable(GL_DEPTH_TEST));
			BK_GL_ASSERT(glDepthFunc(GL_LESS));
		} else {
			BK_GL_ASSERT(glDisable(GL_DEPTH_TEST));
		}

		if (m_object->option(ContextOption::ENABLE_BLEND)) {
			BK_GL_ASSERT(glEnable(GL_BLEND));
			BK_GL_ASSERT(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));
		} else {
			BK_GL_ASSERT(glDisable(GL_BLEND));
		}
	}

private:
	ContextOpenGL* m_object;
};

ContextOpenGL::ContextOpenGL(const string& name) :
	IContext(name), m_impl(new ContextOpenGLPrivate(this))
{
}

ContextOpenGL::~ContextOpenGL()
{
	SAFE_DELETE(m_impl);
}

void
ContextOpenGL::activate()
{
	m_impl->activate();
}

}

