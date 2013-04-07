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
		if (m_object->option(GraphicsOption::DEPTH)) {
			Graphics::graphics()->enable(GraphicsOption::DEPTH);
		} else {
			Graphics::graphics()->disable(GraphicsOption::DEPTH);
		}

		if (m_object->option(GraphicsOption::BLEND)) {
			Graphics::graphics()->enable(GraphicsOption::BLEND);
		} else {
			Graphics::graphics()->disable(GraphicsOption::BLEND);
		}

		if (m_object->option(GraphicsOption::CULLING)) {
			Graphics::graphics()->enable(GraphicsOption::CULLING);
		} else {
			Graphics::graphics()->disable(GraphicsOption::CULLING);
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

