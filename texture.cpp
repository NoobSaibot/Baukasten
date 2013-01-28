#include "texture.h"

#include "bitmap.h"

static GLenum _opengl_format(Bitmap::Format format)
{
	switch (format) {
		case Bitmap::Format_Grayscale: return GL_LUMINANCE;
		case Bitmap::Format_GrayscaleAlpha: return GL_LUMINANCE_ALPHA;
		case Bitmap::Format_RGB: return GL_RGB;
		case Bitmap::Format_RGBA: return GL_RGBA;
	}
}

Texture::Texture(Bitmap& bitmap) :
	Drawable()
{
	GLuint id;
	BK_GL_ASSERT(glGenTextures(1, &id));
	BK_GL_ASSERT(glBindTexture(GL_TEXTURE_2D, id));
	BK_GL_ASSERT(glPixelStorei(GL_UNPACK_ALIGNMENT, 1));
	BK_GL_ASSERT(glPixelStorei(GL_UNPACK_ROW_LENGTH, 0));
	BK_GL_ASSERT(glPixelStorei(GL_UNPACK_SKIP_PIXELS, 0));
	BK_GL_ASSERT(glPixelStorei(GL_UNPACK_SKIP_ROWS, 0));
	BK_GL_ASSERT(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
	BK_GL_ASSERT(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
	BK_GL_ASSERT(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE));
	BK_GL_ASSERT(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE));
	BK_GL_ASSERT(glTexImage2D(
		GL_TEXTURE_2D, 0, _opengl_format(bitmap.format()),
		(GLsizei)bitmap.width(), (GLsizei)bitmap.height(),
		0, _opengl_format(bitmap.format()), GL_UNSIGNED_BYTE, bitmap.pixels()
	));
	BK_GL_ASSERT(glBindTexture(GL_TEXTURE_2D, 0));
	BK_ASSERT(id != 0);
	setId(id);
}

Texture::~Texture()
{
}

Texture* Texture::fromFile(const string& name)
{
	Bitmap *b = Bitmap::fromFile(name);
	Texture *t = new Texture(*b);
	return t;
}

Texture* Texture::fromBitmap(Bitmap* bitmap)
{
	BK_ASSERT(bitmap);
	return new Texture(*bitmap);
}

