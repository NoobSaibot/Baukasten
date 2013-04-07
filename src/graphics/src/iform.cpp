#include "graphics/IForm"

#include "core/Assert"
#include "graphics/Animation"
#include "graphics/Camera"
#include "graphics/IMesh"
#include "graphics/IProgram"
#include "graphics/ITexture"

#include "graphics/inc/opengl/assert_opengl.h"

#include <map>

namespace bk {

class IFormPrivate {
public:
	IFormPrivate(IDisplay* display) :
		m_currAnimation(nullptr), m_display(display), m_mode(DisplayMode::FULL)
	{
	}

	~IFormPrivate()
	{
		// TODO cleanup
	}

	void addTexture(ITexture* texture)
	{
		m_textures.push_back(texture);
	}

	DisplayMode displayMode() const
	{
		return m_mode;
	}

	ITexture* texture(const string& name) const
	{
		for ( ITexture* t: m_textures ) {
			if ( t->name() == name ) {
				return t;
			}
		}

		return nullptr;
	}

	ITexture* texture() const
	{
		return m_textures[0];
	}

	void setTranslation(const mat4& translation)
	{
		m_translation = translation;
	}

	mat4 translation() const
	{
		return m_translation;
	}

	void translate(const mat4& offset)
	{
		m_translation *= offset;
	}

	void translate(const float x, const float y, const float z)
	{
		m_translation *= glm::translate(mat4(), vec3(x,y,z));
	}

	void scale(const float x, const float y, const float z)
	{
		m_translation *= glm::scale(mat4(), vec3(x,y,z));
	}

	void scale(const vec3& m)
	{
		m_translation *= glm::scale(mat4(), m);
	}

	void addAnimation(Animation* animation)
	{
		m_animations[animation->name()] = animation;
	}

	void startAnimation(const string& name)
	{
		if (m_currAnimation) {
			m_currAnimation->reset();
			if (m_currAnimation->name() == name) return;
		}

		m_currAnimation = m_animations[name];
	}

	void stopAnimation()
	{
		m_currAnimation = 0;
	}

	Animation* animation()
	{
		return m_currAnimation;
	}

	IDisplay* display() const
	{
		return m_display;
	}

	void setDisplayMode(DisplayMode mode)
	{
		m_mode = mode;
	}

	void update(const int timeDelta)
	{
		if (m_currAnimation) {
			m_currAnimation->update(timeDelta);
		}
	}

private:
	IMesh*    m_mesh;
	IProgram* m_program;
	ITexture* m_texture;
	std::map<string, Animation*> m_animations;
	Animation* m_currAnimation;
	IDisplay* m_display;
	std::vector<ITexture*> m_textures;

	mat4 m_translation;

	// options
	bool m_enable3d, m_enableBlend, m_enableDepth;
	DisplayMode m_mode;
};

IForm::IForm(const string& name, IDisplay* display) :
	Managed(name, "IForm"), m_impl(new IFormPrivate(display))
{
}

IForm::~IForm()
{
	SAFE_DELETE(m_impl);
}

void
IForm::addTexture(ITexture* texture)
{
	m_impl->addTexture(texture);
}

void
IForm::setTranslation(const mat4& translation)
{
	m_impl->setTranslation(translation);
}

mat4
IForm::translation() const
{
	return m_impl->translation();
}

void
IForm::translate(const mat4& translationOffset)
{
	m_impl->translate(translationOffset);
}

void
IForm::translate(const float x, const float y, const float z)
{
	m_impl->translate(x, y, z);
}

void
IForm::scale(const vec3& scale)
{
	m_impl->scale(scale);
}

void
IForm::scale(const float x, const float y, const float z)
{
	m_impl->scale(x, y, z);
}

void
IForm::addAnimation(Animation* animation)
{
	m_impl->addAnimation(animation);
}

void
IForm::startAnimation(const string& name)
{
	m_impl->startAnimation(name);
}

void
IForm::stopAnimation()
{
	m_impl->stopAnimation();
}

Animation*
IForm::animation() const
{
	return m_impl->animation();
}

void
IForm::setDisplayMode(DisplayMode mode)
{
	m_impl->setDisplayMode(mode);
}

ITexture*
IForm::texture(const string& name) const
{
	return m_impl->texture(name);
}

ITexture*
IForm::texture() const
{
	return m_impl->texture();
}

void
IForm::update(const int timeDelta)
{
	m_impl->update(timeDelta);
}

IDisplay*
IForm::display() const
{
	return m_impl->display();
}

DisplayMode
IForm::displayMode() const
{
	return m_impl->displayMode();
}

} /* bk */