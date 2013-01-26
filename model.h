#ifndef MODEL_H_IZNSJVOY
#define MODEL_H_IZNSJVOY

#include "base.h"
#include "drawable.h"

class Mesh;
class Program;
class Texture;

/*!
 * \brief Model class declaration.
 */
class Model : public Drawable {
public:
	static Model* createModel(Mesh*, Program*, Texture*);

	void render(const float) const;

private:
	Model(Mesh*, Program*, Texture*);
	virtual ~Model();

	Mesh* m_mesh;
	Program* m_program;
	Texture* m_texture;
};

#endif /* end of include guard: MODEL_H_IZNSJVOY */

