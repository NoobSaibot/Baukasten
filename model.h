#ifndef MODEL_H_IZNSJVOY
#define MODEL_H_IZNSJVOY

#include "base.h"
#include "drawable.h"

class Camera;
class Mesh;
class Program;
class Texture;

/*!
 * \brief Model class declaration.
 */
class Model : public Drawable {
public:
	static Model* createModel(Mesh*, Program*, Texture*);

	void render(const Camera*, const float) const;
	void setTranslation(const mat4&);
	mat4 translation() const;
	void translate(const mat4&);

private:
	Model(Mesh*, Program*, Texture*);
	virtual ~Model();

	Mesh*    m_mesh;
	Program* m_program;
	Texture* m_texture;
	mat4     m_translation;
};

#endif /* end of include guard: MODEL_H_IZNSJVOY */

