#ifndef MODEL_H_IZNSJVOY
#define MODEL_H_IZNSJVOY

#include "base.h"
#include "drawable.h"

class Camera;
class IMesh;
class Program;
class ITexture;

/*!
 * \brief Model class declaration.
 */
class Model : public Drawable {
public:
	static Model* createModel(IMesh*, Program*, ITexture*);

	void render(const Camera*, const float) const;
	void setTranslation(const mat4&);
	mat4 translation() const;
	void translate(const mat4&);

private:
	Model(IMesh*, Program*, ITexture*);
	virtual ~Model();

	IMesh*   m_mesh;
	Program* m_program;
	Texture* m_texture;
	mat4     m_translation;
};

#endif /* end of include guard: MODEL_H_IZNSJVOY */

