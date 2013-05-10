#include "graphics/IContext"

#include "core/Assert"
#include "graphics/Camera"

#include <map>

namespace bk {

class IContextPrivate {
public:
	IContextPrivate() :
		m_activeCam(0)
	{
	}

	~IContextPrivate()
	{
		for ( auto pair: m_cams ) {
			pair.second->release();
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
