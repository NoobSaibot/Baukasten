#include "graphics/Model"

#include "core/Assert"
#include "graphics/Camera"
#include "graphics/IMesh"
#include "graphics/IProgram"
#include "graphics/ITexture"
#include "graphics/VertexFormat"

#include "graphics/inc/opengl/assert_opengl.h"

namespace bk {

class ModelPrivate {
public:
	ModelPrivate(IMesh* mesh, IProgram* program, ITexture* texture) :
		m_mesh(mesh), m_program(program), m_texture(texture)
	{
		m_mesh->addRef();
		m_program->addRef();
		m_texture->addRef();
	}

	~ModelPrivate()
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

private:
	IMesh*    m_mesh;
	IProgram* m_program;
	ITexture* m_texture;

	mat4 m_translation;
};

Model::Model(const string& name, IMesh* mesh, IProgram* program, ITexture* texture) :
	Managed(name, "Model"), m_impl(new ModelPrivate(mesh, program, texture))
{
}

Model::~Model()
{
	delete m_impl;
}

void Model::render(const Camera* cam, const float timeDelta) const
{
	m_impl->render(cam, timeDelta);
}

void Model::setTranslation(const mat4& translation)
{
	m_impl->setTranslation(translation);
}

mat4 Model::translation() const
{
	return m_impl->translation();
}

void Model::translate(const mat4& translationOffset)
{
	m_impl->translate(translationOffset);
}

void Model::translate(const float x, const float y, const float z)
{
	m_impl->translate(x, y, z);
}

void Model::scale(const float x, const float y, const float z)
{
	m_impl->scale(x, y, z);
}

}

