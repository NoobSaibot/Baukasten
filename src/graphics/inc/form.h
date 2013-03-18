#ifndef FORM_H_IZNSJVOY
#define FORM_H_IZNSJVOY

#include "base.h"
#include "core/Managed"

namespace bk {

class Animation;
class Camera;
class IMesh;
class IProgram;
class ITexture;

class Form : public Managed {
public:
	void render(const Camera*, const float) const;
	void setTranslation(const mat4&);
	mat4 translation() const;
	void translate(const mat4&);
	void translate(const float, const float, const float);
	void scale(const mat4&);
	void scale(const float, const float, const float);

	void addAnimation(Animation*);
	void startAnimation(const string&);
	void stopAnimation();

	void update(const int);

	virtual ~Form();

private:
	Form(const string&, IMesh*, IProgram*, ITexture*);
	friend class Graphics;
	BK_IMPL(Form);
};

}

#endif /* end of include guard: FORM_H_IZNSJVOY */

