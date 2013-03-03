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
	void init();
	void setBackgroundColor(const float, const float, const float);

private:
	BK_IMPL(DisplayOpenGL);
};

} /*  bk */

#endif /* end of include guard: DISPLAY_OPENGL_H_7KWBLMCJ */

