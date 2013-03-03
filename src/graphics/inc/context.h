#ifndef CONTEXT_H_DS6NWYGQ
#define CONTEXT_H_DS6NWYGQ

#include "graphics/Global"

namespace bk {

class Camera;

/*!
 * \brief Context class declaration.
 */
class Context {
public:
	virtual ~Context();
	static Context* create();

	void setOption(const ContextOption, const bool);
	void setOption(const ContextOption, const int);
	void setOption(const ContextOption, const float);
	void setOption(const ContextOption, const string&);

	void addCamera(Camera*, bool setActive = true);
	void setActiveCamera(const int);
	Camera* camera() const;

	void setTransformation(const mat4&);

private:
	Context();
	BK_IMPL(Context);
};

} /*  bk */

#endif /* end of include guard: CONTEXT_H_DS6NWYGQ */

