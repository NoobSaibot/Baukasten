#ifndef TEXT_FORM_H_RYCU1SE0
#define TEXT_FORM_H_RYCU1SE0

#include "graphics/Global"
#include "graphics/IForm"

namespace bk {

class Camera;
class Font;
class IDisplay;
class IProgram;

/*!
 * \brief TextForm class declaration.
 */
class TextForm : public IForm {
public:
	virtual ~TextForm();

	void setText(const string&);
	void setFont(Font&);
	void setColor(const vec3&);

	void render(const Camera*, const f32) override;
private:
	friend class Graphics;
	TextForm(const string&, const string&, Font*, IProgram*, IDisplay*);
	TextForm(const string&, const string&, Font*, IDisplay*);
	BK_IMPL(TextForm);
};

} /* bk */

#endif /* end of include guard: TEXT_FORM_H_RYCU1SE0 */

