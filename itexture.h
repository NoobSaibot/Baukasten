#ifndef ITEXTURE_H_CPT5FEFW
#define ITEXTURE_H_CPT5FEFW

#include "base.h"

class Program;

/*!
 * \brief ITexture class declaration.
 */
class ITexture {
public:
	enum Wrapping {
		CLAMP_TO_EDGE, CLAMP_TO_BORDER,
		REPEAT, MIRRORED_REPEAT
	};

	enum Filtering {
		NEAREST, LINEAR, NEAREST_MIPMAP_NEAREST,
		LINEAR_MIPMAP_NEAREST, NEAREST_MIPMAP_LINEAR,
		LINEAR_MIPMAP_LINEAR
	};

	virtual void activate(const Program&) const = 0;
	virtual void deactivate() const = 0;
	virtual void setFiltering(const Filtering) = 0;
	virtual void setWrapping(const Wrapping) = 0;
};

#endif /* end of include guard: ITEXTURE_H_CPT5FEFW */

