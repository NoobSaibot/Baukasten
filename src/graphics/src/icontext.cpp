#include "graphics/IContext"

#include "core/Assert"
#include "graphics/Camera"

#include <map>

namespace bk {

class IContextPrivate {
public:
	IContextPrivate() :
		m_enableDepth(true), m_enableBlend(false), m_enableCulling(false),
		m_activeCam(0)
	{
	}

	~IContextPrivate()
	{
		for ( auto pair: m_cams ) {
			pair.second->release();
		}
	}

	void setOption(GraphicsOption option, bool value)
	{
		switch( option ) {
		case GraphicsOption::DEPTH:
			m_enableDepth = value; break;
		case GraphicsOption::BLEND:
			m_enableBlend = value; break;
		case GraphicsOption::CULLING:
			m_enableCulling = value; break;
		}
	}

	bool option(GraphicsOption option)
	{
		switch( option ) {
		case GraphicsOption::DEPTH:   return m_enableDepth;
		case GraphicsOption::BLEND:   return m_enableBlend;
		case GraphicsOption::CULLING: return m_enableCulling;
		default:
			return false;
		}
	}

	void addCamera(Camera* cam, bool setActive)
	{
		cam->addRef();
		m_cams[cam->name()] = cam;
		if (setActive)
			m_activeCam = cam;
	}

	void setActiveCamera(const string& name)
	{
		m_activeCam = m_cams[name];
	}

	Camera* camera() const
	{
		return m_activeCam;
	}

	Camera* camera(const string& name)
	{
		auto cam = m_cams[name];
		return cam;
	}

private:
	bool m_enableDepth;
	bool m_enableBlend;
	bool m_enableCulling;
	map<string, Camera*> m_cams;
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
IContext::setOption(const GraphicsOption option, bool value)
{
	m_impl->setOption(option, value);
}

bool
IContext::option(const GraphicsOption option) const
{
	return m_impl->option(option);
}

void
IContext::addCamera(Camera* cam, bool setActive)
{
	m_impl->addCamera(cam, setActive);
}

void
IContext::setActiveCamera(const string& name)
{
	m_impl->setActiveCamera(name);
}

Camera*
IContext::camera() const
{
	return m_impl->camera();
}

Camera*
IContext::camera(const string& name)
{
	return m_impl->camera(name);
}

} /* bk */
