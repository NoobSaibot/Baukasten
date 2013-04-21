#include "graphics/inc/opengl/graphics_opengl.h"

#include "graphics/IMesh"

#include "graphics/inc/opengl/assert_opengl.h"

namespace bk {

/*!
 * \brief GraphicsOpenGLPrivate class declaration.
 */
class GraphicsOpenGLPrivate {
public:
	GraphicsOpenGLPrivate() : m_mode(DisplayMode::FULL)
	{
	}

	~GraphicsOpenGLPrivate()
	{
	}

	void setDisplayMode(DisplayMode mode)
	{
		m_mode = mode;

		switch ( m_mode ) {
		case DisplayMode::WIREFRAME:
			BK_GL_ASSERT(glPolygonMode(GL_FRONT_AND_BACK, GL_LINE));
			break;
		case DisplayMode::FULL:
			BK_GL_ASSERT(glPolygonMode(GL_FRONT_AND_BACK, GL_FILL));
			break;
		case DisplayMode::POINT:
			BK_GL_ASSERT(glPolygonMode(GL_FRONT_AND_BACK, GL_POINT));
			break;
		}
	}

	void setPolygonOffset(const f32 factor, const f32 units)
	{
		BK_GL_ASSERT(glPolygonOffset(factor, units));
	}

	DisplayMode displayMode() const
	{
		return m_mode;
	}

private:
	DisplayMode m_mode;
};

GraphicsOpenGL::GraphicsOpenGL() :
	m_impl(new GraphicsOpenGLPrivate())
{
}

GraphicsOpenGL::~GraphicsOpenGL()
{
	SAFE_DELETE(m_impl);
}

void
GraphicsOpenGL::init(const u16 width, const u16 height, const string& name)
{
	// TODO fenster und so
}

void
GraphicsOpenGL::enable(GraphicsOption option)
{
	switch ( option ) {
	case GraphicsOption::DEPTH:
		BK_GL_ASSERT(glEnable(GL_DEPTH_TEST));
		BK_GL_ASSERT(glDepthFunc(GL_LESS));
		break;
	case GraphicsOption::BLEND:
		BK_GL_ASSERT(glEnable(GL_BLEND));
		BK_GL_ASSERT(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));
		break;
	case GraphicsOption::CULLING:
		BK_GL_ASSERT(glEnable(GL_CULL_FACE));
		BK_GL_ASSERT(glCullFace(GL_BACK));
		break;
	case GraphicsOption::POLYGON_OFFSET:
		BK_GL_ASSERT(glEnable(GL_POLYGON_OFFSET_FILL));
		BK_GL_ASSERT(glEnable(GL_POLYGON_OFFSET_LINE));
		BK_GL_ASSERT(glEnable(GL_POLYGON_OFFSET_POINT));
		break;
	}
}

bool
GraphicsOpenGL::isEnabled(GraphicsOption option) const
{
	switch ( option ) {
	case GraphicsOption::DEPTH:
		BK_GL_ASSERT(return glIsEnabled(GL_DEPTH_TEST));
	case GraphicsOption::BLEND:
		BK_GL_ASSERT(return glIsEnabled(GL_BLEND));
	case GraphicsOption::CULLING:
		BK_GL_ASSERT(return glIsEnabled(GL_CULL_FACE));
	case GraphicsOption::POLYGON_OFFSET:
		BK_GL_ASSERT(return glIsEnabled(GL_POLYGON_OFFSET_LINE));
	}
	return false;
}

void
GraphicsOpenGL::disable(GraphicsOption option)
{
	switch ( option ) {
	case GraphicsOption::DEPTH:
		BK_GL_ASSERT(glDisable(GL_DEPTH_TEST));
		break;
	case GraphicsOption::BLEND:
		BK_GL_ASSERT(glDisable(GL_BLEND));
		break;
	case GraphicsOption::CULLING:
		BK_GL_ASSERT(glDisable(GL_CULL_FACE));
		break;
	case GraphicsOption::POLYGON_OFFSET:
		BK_GL_ASSERT(glDisable(GL_POLYGON_OFFSET_FILL));
		BK_GL_ASSERT(glDisable(GL_POLYGON_OFFSET_LINE));
		BK_GL_ASSERT(glDisable(GL_POLYGON_OFFSET_POINT));
		break;
	}
}

DisplayMode
GraphicsOpenGL::displayMode() const
{
	return m_impl->displayMode();
}

void
GraphicsOpenGL::setDisplayMode(DisplayMode mode)
{
	m_impl->setDisplayMode(mode);
}

void
GraphicsOpenGL::setPolygonOffset(const f32 factor, const f32 units)
{
	m_impl->setPolygonOffset(factor, units);
}

} /* bk */
