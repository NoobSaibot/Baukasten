#include "graphics/inc/opengl/texture_opengl.h"

#include "core/Assert"
#include "graphics/Bitmap"
#include "graphics/IProgram"

#include "graphics/inc/opengl/assert_opengl.h"

namespace {
static bk::VertexDataType _bk_format(bk::BitmapFormat format)
{
	switch (format) {
	case bk::BitmapFormat::Grayscale: return bk::VertexDataType::LUMINANCE;
	case bk::BitmapFormat::GrayscaleAlpha: return bk::VertexDataType::LUMINANCE_ALPHA;
	case bk::BitmapFormat::RGB: return bk::VertexDataType::RGB;
	case bk::BitmapFormat::RGBA: return bk::VertexDataType::RGBA;
	default: return bk::VertexDataType::RGB;
	}
}

static GLenum _opengl_format(bk::VertexDataType type)
{
	switch ( type ) {
	case bk::VertexDataType::LUMINANCE: return GL_LUMINANCE;
	case bk::VertexDataType::LUMINANCE_ALPHA: return GL_LUMINANCE_ALPHA;
	case bk::VertexDataType::ALPHA: return GL_ALPHA;
	case bk::VertexDataType::RGB: return GL_RGB;
	case bk::VertexDataType::RGBA: return GL_RGBA;
	default: return GL_RGB;
	}
}
}

namespace bk {

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
		init(bitmap.width(), bitmap.height(), bitmap.pixels(), _bk_format(bitmap.format()));
	}

	void init(const u32 width, const u32 height, u8* data, const VertexDataType type)
	{
		m_width  = width;
		m_height = height;

		BK_GL_ASSERT(glGenTextures(1, &m_txt));
		BK_GL_ASSERT(glBindTexture(GL_TEXTURE_2D, m_txt));
		BK_GL_ASSERT(glPixelStorei(GL_UNPACK_ALIGNMENT, 1));
		//BK_GL_ASSERT(glPixelStorei(GL_UNPACK_ROW_LENGTH, 0));
		//BK_GL_ASSERT(glPixelStorei(GL_UNPACK_SKIP_PIXELS, 0));
		//BK_GL_ASSERT(glPixelStorei(GL_UNPACK_SKIP_ROWS, 0));
		//BK_GL_ASSERT(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
		//BK_GL_ASSERT(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
		//BK_GL_ASSERT(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE));
		//BK_GL_ASSERT(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE));
		BK_GL_ASSERT(glTexImage2D(
			GL_TEXTURE_2D, 0, _opengl_format(type), (GLsizei)width, (GLsizei)height,
			0, _opengl_format(type), GL_UNSIGNED_BYTE, data
		));
		BK_GL_ASSERT(glGenerateMipmap(GL_TEXTURE_2D));
		BK_GL_ASSERT(glBindTexture(GL_TEXTURE_2D, 0));
		BK_ASSERT(m_txt != 0, "OpenGL handler couldn't be acquired.");
	}

	void bind()
	{
		BK_GL_ASSERT(glActiveTexture(GL_TEXTURE0));
		BK_GL_ASSERT(glBindTexture(GL_TEXTURE_2D, m_txt));
		m_bound = true;
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

	void setData(const u32 xOffset, const u32 yOffset, const u32 width,
			const u32 height, u8* data)
	{
		BK_ASSERT(m_bound, "Texture must be bound first.");
		BK_GL_ASSERT(glTexSubImage2D(GL_TEXTURE_2D, 0, xOffset, yOffset,
			width, height, GL_ALPHA, GL_UNSIGNED_BYTE, data));
	}

	void generateMipmaps() const
	{
		BK_GL_ASSERT(glGenerateMipmap(GL_TEXTURE_2D));
	}

	u32 width() const
	{
		return m_width;
	}

	u32 height() const
	{
		return m_height;
	}

private:
	GLuint m_txt;
	bool m_bound;
	u32 m_width, m_height;
};

TextureOpenGL::TextureOpenGL(const string& name) :
	ITexture(name), m_impl(new TextureOpenGLPrivate())
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

void
TextureOpenGL::init(const u32 width, const u32 height, u8* data,
	const VertexDataType type)
{
	m_impl->init(width, height, data, type);
}

void
TextureOpenGL::bind() const
{
	m_impl->bind();
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

void
TextureOpenGL::setData(const u32 xOffset, const u32 yOffset,
		const u32 width, const u32 height, u8* data)
{
	m_impl->setData(xOffset, yOffset, width, height, data);
}

void
TextureOpenGL::generateMipmaps() const
{
	m_impl->generateMipmaps();
}

u32
TextureOpenGL::width() const
{
	return m_impl->width();
}

u32
TextureOpenGL::height() const
{
	return m_impl->height();
}

}

