#include "graphics/inc/opengl/texture_opengl.h"

#include "graphics/Bitmap"
#include "graphics/IProgram"

static GLenum _opengl_format(BitmapFormat format)
{
	switch (format) {
		case BitmapFormat::Grayscale: return GL_LUMINANCE;
		case BitmapFormat::GrayscaleAlpha: return GL_LUMINANCE_ALPHA;
		case BitmapFormat::RGB: return GL_RGB;
		case BitmapFormat::RGBA: return GL_RGBA;
		default: return GL_RGB;
	}
}

class TextureOpenGLPrivate {
public:
	TextureOpenGLPrivate()
	{
	}

	virtual ~TextureOpenGLPrivate()
	{
		// TODO destroy texture
	}

	void init(const Bitmap& bitmap)
	{
		BK_GL_ASSERT(glGenTextures(1, &m_txt));
		BK_GL_ASSERT(glBindTexture(GL_TEXTURE_2D, m_txt));
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
		BK_GL_ASSERT(glGenerateMipmap(GL_TEXTURE_2D));
		BK_GL_ASSERT(glBindTexture(GL_TEXTURE_2D, 0));
		BK_ASSERT(m_txt != 0);
	}

	void activate(const IProgram& program) const
	{
		GLint location = program.constant("tex");
		BK_GL_ASSERT(glActiveTexture(GL_TEXTURE0));
		BK_GL_ASSERT(glBindTexture(GL_TEXTURE_2D, m_txt));
		BK_GL_ASSERT(glUniform1i(location, 0));
	}

	void deactivate() const
	{
		BK_GL_ASSERT(glBindTexture(GL_TEXTURE_2D, 0));
	}

private:
	GLuint m_txt;
};

TextureOpenGL::TextureOpenGL() :
	m_impl(new TextureOpenGLPrivate())
{
}

TextureOpenGL::~TextureOpenGL()
{
	SAFE_DELETE(m_impl);
}

void TextureOpenGL::init(const Bitmap& bitmap)
{
	m_impl->init(bitmap);
}

void TextureOpenGL::activate(const IProgram& program) const
{
	m_impl->activate(program);
}

void TextureOpenGL::deactivate() const
{
	m_impl->deactivate();
}

void TextureOpenGL::setWrapping(const ITexture::Wrapping wrapping)
{
}

void TextureOpenGL::setFiltering(const ITexture::Filtering filtering)
{
}
