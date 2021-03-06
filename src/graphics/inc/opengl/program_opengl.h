#ifndef PROGRAM_OPENGL_H_8QTPJICH
#define PROGRAM_OPENGL_H_8QTPJICH

#include "graphics/Global"
#include "graphics/IProgram"

namespace bk {

class ProgramOpenGL : public IProgram {
public:
	virtual ~ProgramOpenGL();

	int attrib(const string&) const;
	void setAttrib(const string&, const mat4&);

	int constant(const string&) const;
	void setConstant(const string&, const mat4&);
	void setConstant(const string&, const vec2&);

	void activate() const;
	void deactivate() const;

private:
	ProgramOpenGL(const string&, const ShaderList&);
	friend class Graphics;
	BK_IMPL(ProgramOpenGL);
};

} /* bk */

#endif /* end of include guard: PROGRAM_OPENGL_H_8QTPJICH */

