#ifndef TEXTURE_OPENGL_H_XXM5JMKA
#define TEXTURE_OPENGL_H_XXM5JMKA

#include "../base.h"
#include "../itexture.h"

class TextureOpenGLPrivate;
class Bitmap;

/*!
 * \brief TextureOpenGL class declaration.
 */
class TextureOpenGL : public ITexture {
public:
	TextureOpenGL(const Bitmap&);
	virtual ~TextureOpenGL();

	void activate(const Program&) const;
	void deactivate() const;
	void setWrapping(const ITexture::Wrapping);
	void setFiltering(const ITexture::Filtering);

private:

	friend class TextureOpenGLPrivate;
	TextureOpenGLPrivate* m_impl;
};

#endif /* end of include guard: TEXTURE_OPENGL_H_XXM5JMKA */

