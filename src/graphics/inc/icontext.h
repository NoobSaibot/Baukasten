#ifndef CONTEXT_H_DS6NWYGQ
#define CONTEXT_H_DS6NWYGQ

#include "core/Managed"
#include "graphics/Global"

namespace bk {

class Camera;

/*!
 * \brief Context class declaration.
 */
class IContext : public Managed {
public:
	IContext(const string&);
	virtual ~IContext();

	virtual void activate() = 0;

	void setOption(const GraphicsOption, const bool);
	bool option(const GraphicsOption) const;

	void addCamera(Camera*, bool setActive = true);
	void setActiveCamera(const string&);
	Camera* camera() const;
	Camera* camera(const string&);

	void setTransformation(const mat4&);

private:
	friend class Graphics;
	BK_IMPL(IContext);
};

} /*  bk */

#endif /* end of include guard: CONTEXT_H_DS6NWYGQ */

