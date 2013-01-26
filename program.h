#ifndef PROGRAM_H_CYWMYDXG
#define PROGRAM_H_CYWMYDXG

#include "base.h"
#include "drawable.h"

class Shader;

/*!
 * \brief Program class declaration.
 */
class Program : public Drawable {
public:
	static Program* createProgram(const Shaders&);

	GLint attrib(const string&) const;
	GLint uniform(const string&) const;

private:
	Program(const Shaders&);
	virtual ~Program();
};

#endif /* end of include guard: PROGRAM_H_CYWMYDXG */

