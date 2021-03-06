#ifndef ITEXTURE_H_CPT5FEFW
#define ITEXTURE_H_CPT5FEFW

#include "core/Managed"
#include "graphics/Global"

namespace bk {

class Bitmap;
class Font;
class IProgram;

class ITexture : public Managed {
public:
	enum Wrapping {
		CLAMP_TO_EDGE, CLAMP_TO_BORDER,
		REPEAT, MIRRORED_REPEAT
	};

	enum class Filtering {
		NEAREST, LINEAR, NEAREST_MIPMAP_NEAREST,
		LINEAR_MIPMAP_NEAREST, NEAREST_MIPMAP_LINEAR,
		LINEAR_MIPMAP_LINEAR
	};

	ITexture(const string& name,
		const TextureTarget target = TextureTarget::TEXTURE_2D, const u32 level = 0) :
		Managed(name, "Texture") {}

	virtual void bind() const = 0;
	virtual void activate(const IProgram&) const = 0;
	virtual void deactivate() const = 0;
	virtual void setFiltering(const Filtering, bool min = true) = 0;
	virtual void setWrapping(const Wrapping) = 0;
	virtual void setData(const u32, const u32, const u32, const u32, u8*) = 0;
	virtual void generateMipmaps() const = 0;
	virtual void init(const Bitmap&) = 0;
	virtual void init(const Bitmap&, const Bitmap&, const Bitmap&,
		const Bitmap&, const Bitmap&, const Bitmap&) = 0;
	virtual void init(const u32, const u32, u8*, const VertexDataType) = 0;
	virtual u32 width() const = 0;
	virtual u32 height() const = 0;
};

}

#endif /* end of include guard: ITEXTURE_H_CPT5FEFW */

