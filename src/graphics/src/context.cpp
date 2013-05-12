#include "graphics/Context"

#include "core/Assert"
#include "graphics/Camera"

#include <map>

namespace bk {

class ContextPrivate {
public:
	ContextPrivate() :
		m_activeCam(0)
	{
	}

	~ContextPrivate()
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
Context::addCamera(Camera* cam, bool setActive)
{
	m_impl->addCamera(cam, setActive);
}

void
Context::setActiveCamera(const string& name)
{
	m_impl->setActiveCamera(name);
}

Camera*
Context::camera() const
{
	return m_impl->camera();
}

Camera*
Context::camera(const string& name)
{
	return m_impl->camera(name);
}

} /* bk */
