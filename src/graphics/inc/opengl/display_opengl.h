#ifndef DISPLAY_OPENGL_H_7KWBLMCJ
#define DISPLAY_OPENGL_H_7KWBLMCJ

#include "graphics/Global"
#include "graphics/IDisplay"

namespace bk {

class DisplayOpenGL : public IDisplay {
public:
	DisplayOpenGL();
	virtual ~DisplayOpenGL();

	void clear();
	void display();
	void exit();
	void init(const u16, const u16);
	void setBackgroundColor(const float, const float, const float);
	u16  width() const override;
	u16 height() const override;

private:
	BK_IMPL(DisplayOpenGL);
};

} /*  bk */

#endif /* end of include guard: DISPLAY_OPENGL_H_7KWBLMCJ */

