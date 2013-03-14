#ifndef CONTEXT_OPENGL_H_HXZNBYG8
#define CONTEXT_OPENGL_H_HXZNBYG8

#include "graphics/Global"
#include "graphics/IContext"

namespace bk {

/*!
	* \brief ContextOpenGL class declaration.
	*/
class ContextOpenGL : public IContext {
public:
	ContextOpenGL(const string&);
	virtual ~ContextOpenGL();

	void activate();

private:
	BK_IMPL(ContextOpenGL);
};

} /* bk */

#endif /* end of include guard: CONTEXT_OPENGL_H_HXZNBYG8 */

