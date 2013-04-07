#ifndef FORM_H_IZNSJVOY
#define FORM_H_IZNSJVOY

#include "graphics/Global"
#include "graphics/IForm"

namespace bk {

class Animation;
class Camera;
class IDisplay;
class IMesh;
class IProgram;
class ITexture;

class Form : public IForm {
public:
	virtual ~Form();

	void render(const Camera*, const f32) override;

private:
	BK_IMPL(Form);
	Form(const string&, IMesh*, IProgram*, ITexture*, IDisplay*);
	friend class Graphics;
};

}

#endif /* end of include guard: FORM_H_IZNSJVOY */

