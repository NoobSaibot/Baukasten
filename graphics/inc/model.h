#ifndef MODEL_H_IZNSJVOY
#define MODEL_H_IZNSJVOY

#include "base.h"
#include "core/Managed"

class Camera;
class IMesh;
class IProgram;
class ITexture;

/*!
 * \brief Model class declaration.
 */
class Model : public Managed {
public:
	static Model* createModel(IMesh*, IProgram*, ITexture*);

	void render(const Camera&, const float) const;
	void setTranslation(const mat4&);
	mat4 translation() const;
	void translate(const mat4&);

private:
	Model(IMesh*, IProgram*, ITexture*);
	virtual ~Model();

	IMesh*    m_mesh;
	IProgram* m_program;
	ITexture* m_texture;
	mat4      m_translation;
};

#endif /* end of include guard: MODEL_H_IZNSJVOY */

