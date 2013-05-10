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
	case bk::VertexDataType::DEPTH_COMPONENT: return GL_DEPTH_COMPONENT;
	case bk::VertexDataType::DEPTH_STENCIL:   return GL_DEPTH_STENCIL;
	case bk::VertexDataType::INTENSITY:       return GL_INTENSITY;
	case bk::VertexDataType::RED:             return GL_RED;
	case bk::VertexDataType::RG:              return GL_RG;
	case bk::VertexDataType::RGB:             return GL_RGB;
	case bk::VertexDataType::RGBA:            return GL_RGBA;
	case bk::VertexDataType::COMPRESSED_RED:  return GL_COMPRESSED_RED;
	case bk::VertexDataType::COMPRESSED_RG:   return GL_COMPRESSED_RG;

	/* DEPRECATED */
	case bk::VertexDataType::LUMINANCE:       return GL_LUMINANCE;
	case bk::VertexDataType::LUMINANCE_ALPHA: return GL_LUMINANCE_ALPHA;
	case bk::VertexDataType::ALPHA:           return GL_ALPHA;
	default: return GL_RGB;
	}
}

static GLenum _opengl_filter(bk::ITexture::Filtering filter)
{
	switch ( filter ) {
	case bk::ITexture::Filtering::NEAREST: return GL_NEAREST;
	case bk::ITexture::Filtering::LINEAR:  return GL_LINEAR;
	case bk::ITexture::Filtering::NEAREST_MIPMAP_NEAREST: return GL_NEAREST_MIPMAP_NEAREST;
	case bk::ITexture::Filtering::LINEAR_MIPMAP_NEAREST: return GL_LINEAR_MIPMAP_NEAREST;
	case bk::ITexture::Filtering::NEAREST_MIPMAP_LINEAR: return GL_NEAREST_MIPMAP_LINEAR;
	case bk::ITexture::Filtering::LINEAR_MIPMAP_LINEAR: return GL_LINEAR_MIPMAP_LINEAR;
	}
}

static GLenum _opengl_target(bk::TextureTarget target)
{
	switch (target) {
	case bk::TextureTarget::TEXTURE_2D: return GL_TEXTURE_2D;
	case bk::TextureTarget::TEXTURE_CUBE_MAP: return GL_TEXTURE_CUBE_MAP;
	}
}

}

namespace bk {

class TextureOpenGLPrivate {
public:
	TextureOpenGLPrivate(const TextureTarget target, const u32 level) :
		m_initialised( false ), m_target(target), m_level(level)
	{
	}

	~TextureOpenGLPrivate()
	{
		BK_GL_ASSERT(glDeleteTextures(1, &m_txt));
	}

	void init(const Bitmap& bitmap)
	{
		init(bitmap.width(), bitmap.height(), bitmap.pixels(), _bk_format(bitmap.format()));
	}

	void init(const u32 width, const u32 height, u8* data, const VertexDataType type)
	{
		m_width  = width;
		m_height = height;

		auto target = _opengl_target(m_target);
		BK_GL_ASSERT(glGenTextures(1, &m_txt));
		BK_GL_ASSERT(glBindTexture(target, m_txt));
		BK_GL_ASSERT(glPixelStorei(GL_UNPACK_ALIGNMENT, 1));
		BK_GL_ASSERT(glTexImage2D(
			GL_TEXTURE_2D, 0, _opengl_format(type), (GLsizei)width, (GLsizei)height,
			0, _opengl_format(type), GL_UNSIGNED_BYTE, data
		));
		BK_GL_ASSERT(glGenerateMipmap(target));
		BK_GL_ASSERT(glBindTexture(target, 0));
		BK_ASSERT(m_txt != 0, "OpenGL handler couldn't be acquired.");
	}

	void bind() const
	{
		auto target = _opengl_target(m_target);
		BK_GL_ASSERT(glEnable(target));
		BK_GL_ASSERT(glActiveTexture(GL_TEXTURE0));
		BK_GL_ASSERT(glBindTexture(target, m_txt));
	}

	bool bound() const
	{
		u32 id;
		BK_GL_ASSERT(glGetIntegerv(_opengl_target(m_target), &id));
		return id == m_txt;
	}

	void activate(const IProgram& program) const
	{
		bind();
	}

	void deactivate() const
	{
		auto target = _opengl_target(m_target);
		BK_GL_ASSERT(glBindTexture(target, 0));
	}

	void setData(const u32 xOffset, const u32 yOffset, const u32 width,
			const u32 height, u8* data)
	{
		auto target = _opengl_target(m_target);
		BK_ASSERT(m_bound, "Texture must be bound first.");
		BK_GL_ASSERT(glTexSubImage2D(target, 0, xOffset, yOffset,
			width, height, GL_ALPHA, GL_UNSIGNED_BYTE, data));
	}

	void setFiltering(ITexture::Filtering filter, bool min)
	{
		u32 id = 0;
		if (!bound()) {
			// store the currently bound texture
			BK_GL_ASSERT(glGetIntegerv(GL_TEXTURE_BINDING_2D, &id));
		}

		// bind our texture
		bind();

		// set parameter
		if (min) {
			BK_GL_ASSERT(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, _opengl_filter(filter)));
		} else {
			BK_GL_ASSERT(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, _opengl_filter(filter)));
		}

		// restore the previous texture
		if (id) {
			BK_GL_ASSERT(glBindTexture(GL_TEXTURE_2D, id));
		}
	}

	void setWrapping(ITexture::Wrapping wrapping)
	{
		u32 id;
		// store the currently bound texture
		BK_GL_ASSERT(glGetIntegerv(GL_TEXTURE_BINDING_2D, &id));
		// bind our texture
		bind();
	}

	void generateMipmaps() const
	{
		auto target = _opengl_target(m_target);
		BK_GL_ASSERT(glGenerateMipmap(target));
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
	bool m_initialised;
	TextureTarget m_target;
	u32 m_level;
};

TextureOpenGL::TextureOpenGL(const string& name, const TextureTarget target,
	const u32 level) :
	ITexture(name), m_impl(new TextureOpenGLPrivate(target, level))
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
	m_impl->setWrapping(wrapping);
}

void TextureOpenGL::setFiltering(const ITexture::Filtering filtering, bool min)
{
	m_impl->setFiltering(filtering, min);
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

