#include "model.h"

#include "camera.h"
#include "mesh.h"
#include "program.h"
#include "texture.h"
#include "vertex_format.h"

static void
_set_attrib(Program* program, VertexFormat::Data d, VertexFormat f, const string& attrib)
{
	GLint pos;
	pos = program->attrib(attrib.c_str());
	BK_GL_ASSERT(glVertexAttribPointer(
		pos, d.size, GL_FLOAT, GL_FALSE, f.size()*sizeof(GLfloat), (const GLvoid*)(d.padding * sizeof(GLfloat))
	));
	BK_GL_ASSERT(glEnableVertexAttribArray(pos));
}

Model::Model(Mesh* mesh, Program* program, Texture* texture) :
	Drawable(), m_mesh(mesh), m_program(program), m_texture(texture)
{
}

Model::~Model()
{
	//m_mesh->release();
	//m_program->release();
	//m_texture->release();
}

Model* Model::createModel(Mesh* mesh, Program* program, Texture* texture )
{
	return new Model(mesh, program, texture);
}

void Model::render(const Camera* cam, const float timeInterval) const
{
	m_program->activate();
	m_mesh->activate();
	VertexFormat f = m_mesh->format();

	BK_ASSERT(cam != 0);

	// set camera matrix
	m_program->setConstant("camera", cam->matrix());
	m_program->setConstant("translation", m_translation);

	for ( VertexFormat::Data d: f.elements() ) {
		switch ( d.type ) {
		case VertexFormat::COLOR:
		case VertexFormat::NORMAL:
		case VertexFormat::TANGENT:
		case VertexFormat::BINORMAL:
		case VertexFormat::BLENDWEIGHTS:
		case VertexFormat::BLENDINDICES:
		case VertexFormat::TEXCOORD1:
		case VertexFormat::TEXCOORD2:
		case VertexFormat::TEXCOORD3:
		case VertexFormat::TEXCOORD4:
		case VertexFormat::TEXCOORD5:
		case VertexFormat::TEXCOORD6:
		case VertexFormat::TEXCOORD7:
			break;
		case VertexFormat::POSITION:
			_set_attrib(m_program, d, f, "vert");
			break;
		case VertexFormat::TEXCOORD0:
			_set_attrib(m_program, d, f, "vertTexCoord");
			break;
		}
	}

	if ( m_texture ) {
		GLint location = m_program->constant("tex");
		BK_GL_ASSERT(glActiveTexture(GL_TEXTURE0));
		BK_GL_ASSERT(glBindTexture(GL_TEXTURE_2D, m_texture->id()));
		BK_GL_ASSERT(glUniform1i(location, 0));
	}

	// draw the mesh
	BK_GL_ASSERT(glDrawArrays(GL_TRIANGLES, 0, m_mesh->count()));

	// clean up
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

