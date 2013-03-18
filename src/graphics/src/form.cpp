#include "graphics/Form"

#include "core/Assert"
#include "graphics/Animation"
#include "graphics/Camera"
#include "graphics/IMesh"
#include "graphics/IProgram"
#include "graphics/ITexture"
#include "graphics/VertexFormat"

#include "graphics/inc/opengl/assert_opengl.h"

#include <map>

namespace bk {

class FormPrivate {
public:
	FormPrivate(IMesh* mesh, IProgram* program, ITexture* texture) :
		m_mesh(mesh), m_program(program), m_texture(texture), m_currAnimation(0)
	{
		m_mesh->addRef();
		m_program->addRef();
		m_texture->addRef();
	}

	~FormPrivate()
	{
		m_mesh->release();
		m_program->release();
		m_texture->release();
	}

	void render(const Camera* cam, const float timeDelta) const
	{
		m_program->activate();

		if ( m_mesh ) {
			m_mesh->activate();
		}

		if ( m_texture ) {
			m_texture->activate(*m_program);
		}

		// set camera matrix
		m_program->setConstant("camera", cam->matrix());
		m_program->setConstant("transformation", m_translation);

		// set default value if no animation is present
		m_program->setConstant("bk_texOffset0", vec2(0.0, 0.0));
		m_program->setConstant("bk_texSize0", vec2(1.0, 1.0));

		if (m_currAnimation) {
			m_program->setConstant("bk_texOffset0", vec2(
				m_currAnimation->frame().x, m_currAnimation->frame().y
			));
			m_program->setConstant("bk_texSize0", vec2(
				m_currAnimation->frame().width, m_currAnimation->frame().height
			));
		}

		// draw the mesh
		// TODO auslagern
		BK_GL_ASSERT(glDrawArrays(GL_TRIANGLES, 0, m_mesh->count()));

		// clean up
		m_texture->deactivate();
		m_mesh->deactivate();
		m_program->deactivate();
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

	mat4 m_translation;
};

Form::Form(const string& name, IMesh* mesh, IProgram* program, ITexture* texture) :
	Managed(name, "Form"), m_impl(new FormPrivate(mesh, program, texture))
{
}

Form::~Form()
{
	delete m_impl;
}

void
Form::render(const Camera* cam, const float timeDelta) const
{
	m_impl->render(cam, timeDelta);
}

void
Form::setTranslation(const mat4& translation)
{
	m_impl->setTranslation(translation);
}

mat4
Form::translation() const
{
	return m_impl->translation();
}

void
Form::translate(const mat4& translationOffset)
{
	m_impl->translate(translationOffset);
}

void
Form::translate(const float x, const float y, const float z)
{
	m_impl->translate(x, y, z);
}

void
Form::scale(const float x, const float y, const float z)
{
	m_impl->scale(x, y, z);
}

void
Form::addAnimation(Animation* animation)
{
	m_impl->addAnimation(animation);
}

void
Form::startAnimation(const string& name)
{
	m_impl->startAnimation(name);
}

void
Form::stopAnimation()
{
	m_impl->stopAnimation();
}

void
Form::update(const int timeDelta)
{
	m_impl->update(timeDelta);
}

}

