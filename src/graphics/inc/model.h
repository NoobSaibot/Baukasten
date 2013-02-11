#ifndef MODEL_H_IZNSJVOY
#define MODEL_H_IZNSJVOY

#include "base.h"

class Camera;
class IMesh;
class IProgram;
class ITexture;

/*!
 * \brief Model class declaration.
 */
class Model {
public:
	static shared_ptr<Model> create(shared_ptr<IMesh>,
			shared_ptr<IProgram>, shared_ptr<ITexture>);

	void render(const Camera&, const float) const;
	void setTranslation(const mat4&);
	mat4 translation() const;
	void translate(const mat4&);
	void translate(const float, const float, const float);
	void scale(const mat4&);
	void scale(const float, const float, const float);

	virtual ~Model();

private:
	Model(shared_ptr<IMesh>, shared_ptr<IProgram>, shared_ptr<ITexture>);

	shared_ptr<IMesh>    m_mesh;
	shared_ptr<IProgram> m_program;
	shared_ptr<ITexture> m_texture;

	mat4      m_translation;
};

#endif /* end of include guard: MODEL_H_IZNSJVOY */

