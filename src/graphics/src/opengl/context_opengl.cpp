#include "graphics/inc/opengl/context_opengl.h"

#include "core/Assert"
#include "graphics/IGraphics"
#include "graphics/Graphics"

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

