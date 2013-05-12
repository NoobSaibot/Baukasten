#ifndef CONTEXT_H_DS6NWYGQ
#define CONTEXT_H_DS6NWYGQ

#include "core/Managed"
#include "graphics/Global"

namespace bk {

class Camera;

/*!
 * \brief Context class declaration.
 */
class Context : public Managed {
public:
	Context(const string&);
	virtual ~Context();

	void addCamera(Camera*, bool setActive = true);
	void setActiveCamera(const string&);
	Camera* camera() const;
	Camera* camera(const string&);

	void setTransformation(const mat4&);

private:
	friend class Graphics;
	BK_IMPL(Context);
};

} /*  bk */

#endif /* end of include guard: CONTEXT_H_DS6NWYGQ */

