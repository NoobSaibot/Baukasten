#include "graphics/Context"

#include <map>

#include "graphics/Camera"

namespace bk {

class ContextPrivate {
public:
	ContextPrivate() :
		m_enable3d(true), m_enableBlend(false), m_activeCam(0)
	{
	}

	~ContextPrivate()
	{
		for ( auto pair: m_cams ) {
			pair.second->release();
		}
	}

	void setOption(ContextOption option, bool value)
	{
		switch( option ) {
		case ContextOption::ENABLE_3D:
			m_enable3d = value;
			break;
		case ContextOption::ENABLE_BLEND:
			m_enableBlend = value;
			break;
		}
	}

	void addCamera(Camera* cam, bool setActive)
	{
		cam->addRef();
		m_cams[cam->id()] = cam;
		if (setActive)
			m_activeCam = cam;
	}

	void activate()
	{
		if (m_enable3d) {
			BK_GL_ASSERT(glEnable(GL_DEPTH_TEST));
			BK_GL_ASSERT(glDepthFunc(GL_LESS));
		} else {
			BK_GL_ASSERT(glDisable(GL_DEPTH_TEST));
		}

		if (m_enableBlend) {
			BK_GL_ASSERT(glEnable(GL_BLEND));
			BK_GL_ASSERT(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));
		} else {
			BK_GL_ASSERT(glDisable(GL_BLEND));
		}
	}

	void setActiveCamera(const int id)
	{
		m_activeCam = m_cams[id];
	}

	Camera* camera() const
	{
		return m_activeCam;
	}

private:
	bool m_enable3d;
	bool m_enableBlend;
	map<int, Camera*> m_cams;
	Camera* m_activeCam;
};

Context::Context(const string& name) :
	Managed(name, "Context"),
	m_impl(new ContextPrivate())
{
}

Context::~Context()
{
	delete m_impl;
}

void
Context::activate()
{
	m_impl->activate();
}

void
Context::setOption(const ContextOption option, bool value)
{
	m_impl->setOption(option, value);
}

void
Context::addCamera(Camera* cam, bool setActive)
{
	m_impl->addCamera(cam, setActive);
}

void
Context::setActiveCamera(const int id)
{
	m_impl->setActiveCamera(id);
}

Camera*
Context::camera() const
{
	return m_impl->camera();
}

} /* bk */
