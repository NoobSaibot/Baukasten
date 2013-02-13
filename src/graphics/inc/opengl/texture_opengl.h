#ifndef TEXTURE_OPENGL_H_XXM5JMKA
#define TEXTURE_OPENGL_H_XXM5JMKA

#include "base.h"
#include "graphics/ITexture"

class TextureOpenGLPrivate;
class Bitmap;

/*!
 * \brief TextureOpenGL class declaration.
 */
class TextureOpenGL : public ITexture {
public:
	virtual ~TextureOpenGL();

	void activate(const IProgram&) const;
	void deactivate() const;
	void setWrapping(const ITexture::Wrapping);
	void setFiltering(const ITexture::Filtering);
	void init(const Bitmap&);

private:
	TextureOpenGL(const string&);
	friend class Texture;
	BK_PIMPL(TextureOpenGL);
};

#endif /* end of include guard: TEXTURE_OPENGL_H_XXM5JMKA */

