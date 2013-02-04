#ifndef PROGRAM_OPENGL_H_8QTPJICH
#define PROGRAM_OPENGL_H_8QTPJICH

#include "../base.h"
#include "../iprogram.h"

class Shader;
class ProgramOpenGLPrivate;

/*!
 * \brief ProgramOpenGL class declaration.
 */
class ProgramOpenGL : public IProgram {
public:
	ProgramOpenGL(const Shaders&);
	virtual ~ProgramOpenGL();

	int attrib(const string&) const;
	void setAttrib(const string&, const mat4&);

	int constant(const string&) const;
	void setConstant(const string&, const mat4&);

	void activate() const;
	void deactivate() const;

private:
	friend class ProgramOpenGLPrivate;
	ProgramOpenGLPrivate* m_impl;
};

#endif /* end of include guard: PROGRAM_OPENGL_H_8QTPJICH */

