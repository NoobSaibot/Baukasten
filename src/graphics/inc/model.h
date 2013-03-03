#ifndef MODEL_H_IZNSJVOY
#define MODEL_H_IZNSJVOY

#include "base.h"
#include "core/Identity"

namespace bk {

class Camera;
class IMesh;
class IProgram;
class ITexture;

class Model : public Identity {
public:
	static Model* create(const string&, shared_ptr<IMesh>,
			shared_ptr<IProgram>, shared_ptr<ITexture>);

	void render(const Camera*, const float) const;
	void setTranslation(const mat4&);
	mat4 translation() const;
	void translate(const mat4&);
	void translate(const float, const float, const float);
	void scale(const mat4&);
	void scale(const float, const float, const float);

	virtual ~Model();

private:
	Model(const string&, shared_ptr<IMesh>, shared_ptr<IProgram>,
			shared_ptr<ITexture>);
	BK_IMPL(Model);
};

}

#endif /* end of include guard: MODEL_H_IZNSJVOY */

