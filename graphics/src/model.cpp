#include "graphics/Model"

#include "graphics/Camera"
#include "graphics/IMesh"
#include "graphics/IProgram"
#include "graphics/ITexture"
#include "graphics/VertexFormat"

Model::Model(IMesh* mesh, IProgram* program, ITexture* texture) :
	m_mesh(mesh), m_program(program), m_texture(texture)
{
}

Model::~Model()
{
	m_mesh->release();
	m_program->release();
	m_texture->release();
}

Model* Model::createModel(IMesh* mesh, IProgram* program, ITexture* texture )
{
	return new Model(mesh, program, texture);
}

void Model::render(const Camera* cam, const float timeInterval) const
{
	BK_ASSERT(cam != 0);

	m_program->activate();

	if ( m_mesh ) {
		m_mesh->activate(*m_program);
	}

	if ( m_texture ) {
		m_texture->activate(*m_program);
	}

	// set camera matrix
	m_program->setConstant("camera", cam->matrix());
	m_program->setConstant("translation", m_translation);

	// draw the mesh
	BK_GL_ASSERT(glDrawArrays(GL_TRIANGLES, 0, m_mesh->count()));

	// clean up
	m_texture->deactivate();
	m_mesh->deactivate();
	m_program->deactivate();
}

void Model::setTranslation(const mat4& translation)
{
	m_translation = translation;
}

mat4 Model::translation() const
{
	return m_translation;
}

void Model::translate(const mat4& translationOffset)
{
	m_translation *= translationOffset;
}

