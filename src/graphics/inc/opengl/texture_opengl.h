#ifndef TEXTURE_OPENGL_H_XXM5JMKA
#define TEXTURE_OPENGL_H_XXM5JMKA

#include "graphics/Global"
#include "graphics/ITexture"

namespace bk {

class Bitmap;
class Font;

class TextureOpenGL : public ITexture {
public:
	virtual ~TextureOpenGL();

	void bind() const override;
	void activate(const IProgram&) const;
	void deactivate() const;
	void setWrapping(const ITexture::Wrapping);
	void setFiltering(const ITexture::Filtering);
	void generateMipmaps() const override;
	void setData(const u32, const u32, const u32, const u32, u8*);
	void init(const Bitmap&);
	void init(const u32, const u32, u8*, const VertexDataType);

	u32 width() const override;
	u32 height() const override;

private:
	TextureOpenGL(const string&);
	friend class Graphics;
	BK_IMPL(TextureOpenGL);
};

}

#endif /* end of include guard: TEXTURE_OPENGL_H_XXM5JMKA */

