#ifndef ITEXTURE_H_CPT5FEFW
#define ITEXTURE_H_CPT5FEFW

#include "core/Managed"
#include "graphics/Global"

namespace bk {

class Bitmap;
class IProgram;

class ITexture : public Managed {
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

	ITexture(const string& name) : Managed(name, "Texture") {}

	virtual void activate(const IProgram&) const = 0;
	virtual void deactivate() const = 0;
	virtual void setFiltering(const Filtering) = 0;
	virtual void setWrapping(const Wrapping) = 0;
	virtual void init(const Bitmap&) = 0;
};

}

#endif /* end of include guard: ITEXTURE_H_CPT5FEFW */

