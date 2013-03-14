#include "graphics/IContext"

#include "core/Assert"
#include "graphics/Camera"

#include <map>

namespace bk {

class IContextPrivate {
public:
	IContextPrivate() :
		m_enable3d(true), m_enableBlend(false), m_activeCam(0)
	{
	}

	~IContextPrivate()
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

	bool option(ContextOption option)
	{
		switch( option ) {
		case ContextOption::ENABLE_3D:    return m_enable3d;
		case ContextOption::ENABLE_BLEND: return m_enableBlend;
		}
	}

	void addCamera(Camera* cam, bool setActive)
	{
		cam->addRef();
		m_cams[cam->id()] = cam;
		if (setActive)
			m_activeCam = cam;
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

IContext::IContext(const string& name) :
	Managed(name, "Context"),
	m_impl(new IContextPrivate())
{
}

IContext::~IContext()
{
	delete m_impl;
}

void
IContext::setOption(const ContextOption option, bool value)
{
	m_impl->setOption(option, value);
}

bool
IContext::option(const ContextOption option) const
{
	return m_impl->option(option);
}

void
IContext::addCamera(Camera* cam, bool setActive)
{
	m_impl->addCamera(cam, setActive);
}

void
IContext::setActiveCamera(const int id)
{
	m_impl->setActiveCamera(id);
}

Camera*
IContext::camera() const
{
	return m_impl->camera();
}

} /* bk */
