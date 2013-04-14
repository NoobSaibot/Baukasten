#include "graphics/Font"

#include "core/Debug"
#include "graphics/Graphics"
#include "graphics/ITexture"

#include <ft2build.h>
#include FT_FREETYPE_H

namespace {
unsigned long __bk_nextPowerOf2(unsigned long v)
{
	v--;
	v |= v >> 1;
	v |= v >> 2;
	v |= v >> 4;
	v |= v >> 8;
	v |= v >> 16;
	v++;
	return v;
}
}

namespace bk {

/*!
 * \brief FontPrivate class declaration.
 */
class FontPrivate {
public:
	FontPrivate()
	{
	}

	~FontPrivate()
	{
		// TODO alle glyphen durchgehen und ihre texturen freigeben
	}

	void init(const string& path, const u32 size)
	{
		m_size = size;

		if ( FT_Init_FreeType( &m_lib ) ) {
			BK_DEBUG( "Could not init freetype library." );
			return;
		}

		if ( FT_New_Face( m_lib, path.c_str(), 0, &m_face ) ) {
			BK_DEBUG( "Could not open font " << path );
			return;
		}

		FT_Set_Pixel_Sizes(m_face, 0, size);
		FT_GlyphSlot g = m_face->glyph;
		FT_Bitmap* bitmap = &m_face->glyph->bitmap;

		memset(m_glyph, 0, sizeof(m_glyph));

		// TODO alles in ein texture packen
		for ( u32 i = 32; i < 256; i++ ) {
			if ( FT_Load_Char(m_face, i, FT_LOAD_RENDER ) ) {
				BK_DEBUG("Loading character " << (char)i << " failed!");
				continue;
			}

			auto texture = Graphics::createTextureFromData(
				path, bitmap->width, bitmap->rows,
				bitmap->buffer, VertexDataType::RED
			);

			m_glyph[i].advance = g->advance.x >> 6;
			m_glyph[i].width   = bitmap->width;
			m_glyph[i].height  = bitmap->rows;
			m_glyph[i].topBearing = g->bitmap_top;
			m_glyph[i].tex     = texture;
		}
	}

	bk::Glyph glyph(const u8 c)
	{
		return m_glyph[c];
	}

	u32 size() const
	{
		return m_size;
	}

private:
	Glyph m_glyph[256];
	FT_Library m_lib;
	FT_Face m_face;
	u32 m_size;
};

Font::Font(const string& path, const unsigned int size) :
	Managed(path, "Font"), m_impl(new FontPrivate())
{
	m_impl->init(path, size);
}

Font::~Font()
{
	SAFE_DELETE(m_impl);
}

Glyph
Font::glyph(const char c) const
{
	return m_impl->glyph(c);
}

u32
Font::size() const
{
	return m_impl->size();
}

} /* bk */
