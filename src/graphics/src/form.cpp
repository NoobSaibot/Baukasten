#include "graphics/Form"

#include "core/Assert"
#include "graphics/Animation"
#include "graphics/Camera"
#include "graphics/Graphics"
#include "graphics/IGraphics"
#include "graphics/IMesh"
#include "graphics/IProgram"
#include "graphics/ITexture"

#include "graphics/inc/opengl/assert_opengl.h"

#include <map>

namespace bk {

class FormPrivate {
public:
	FormPrivate(IMesh* mesh, IProgram* program, ITexture* texture, Form* form) :
		m_mesh(mesh), m_program(program), m_texture(texture), m_form(form)
	{
		BK_ASSERT(program, "Program must not be null.");
		m_program->addRef();

		if ( mesh ) {
			m_mesh->addRef();
		}

		if (texture) {
			m_texture->addRef();
		}
	}

	~FormPrivate()
	{
		if ( m_mesh ) {
			m_mesh->release();
		}

		m_program->release();

		if ( m_texture != nullptr ) {
			m_texture->release();
		}
	}

	void render(const Camera* cam, const f32 timeDelta)
	{
		m_program->activate();

		if ( m_mesh ) {
			m_mesh->activate();
		}

		if ( m_texture ) {
			m_texture->activate(*m_program);
		}

		// set camera matrix
		m_program->setConstant("camera", cam->matrix(
					m_form->option(GraphicsOption::ROTATION_MATRIX)));
		m_program->setConstant("transformation", m_form->translation());

		// set default value if no animation is present
		m_program->setConstant("bk_texOffset0", vec2(0.0, 0.0));
		m_program->setConstant("bk_texSize0", vec2(1.0, 1.0));

		auto animation = m_form->animation();
		if (animation) {
			m_program->setConstant("bk_texOffset0", vec2(
				animation->frame().x, animation->frame().y
			));
			m_program->setConstant("bk_texSize0", vec2(
				animation->frame().width, animation->frame().height
			));
		}

		Graphics::graphics()->setDisplayMode( m_form->displayMode() );
		Graphics::graphics()->set(GraphicsOption::CULLING, m_form->option(GraphicsOption::CULLING));
		Graphics::graphics()->set(GraphicsOption::BLEND, m_form->option(GraphicsOption::BLEND));

		// draw the mesh
		m_mesh->render();

		// clean up
		if ( m_texture != nullptr ) {
			m_texture->deactivate();
		}

		m_mesh->deactivate();
		m_program->deactivate();
	}

private:
	IMesh*    m_mesh;
	IProgram* m_program;
	ITexture* m_texture;
	Form*     m_form;
};

Form::Form(const string& name, IMesh* mesh, IProgram* program,
		ITexture* texture, IDisplay* display) :
	IForm(name, display), m_impl(new FormPrivate(mesh, program, texture, this))
{
}

Form::~Form()
{
	SAFE_DELETE( m_impl );
}

void
Form::render(const Camera* cam, const f32 timeDelta)
{
	m_impl->render(cam, timeDelta);
}

}

