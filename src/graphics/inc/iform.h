#ifndef IFORM_H_1BIYYXLL
#define IFORM_H_1BIYYXLL

#include "core/Managed"
#include "graphics/Global"

namespace bk {

class Animation;
class Camera;
class IDisplay;
class IMesh;
class IProgram;
class ITexture;

/*!
 * \brief IForm class declaration.
 */
class IForm : public Managed {
public:
	IForm(const string&, IDisplay*);
	virtual ~IForm();

	void           addAnimation(Animation*);
	void           addTexture(ITexture*);
	Animation*     animation() const;
	IDisplay*      display()  const;
	DisplayMode    displayMode() const;
	bool           option(const GraphicsOption) const;
	IProgram*      program() const;
	pair<f32, f32> polygonOffset() const;
	void           scale(const float, const float, const float);
	void           scale(const vec3&);
	void           setDisplayMode(DisplayMode);
	void           setOption(const GraphicsOption, const bool);
	void           setPolygonOffset(const f32, const f32);
	void           setProgram(IProgram*);
	void           setTranslation(const mat4&);
	void           startAnimation(const string&);
	void           stopAnimation();
	ITexture*      texture(const string&) const;
	ITexture*      texture() const;
	void           translate(const float, const float, const float);
	void           translate(const mat4&);
	mat4           translation() const;
	void           update(const int);

	virtual void render(const Camera*, const f32) = 0;

private:
	BK_IMPL(IForm);
};

} /* iform */

#endif /* end of include guard: IFORM_H_1BIYYXLL */

