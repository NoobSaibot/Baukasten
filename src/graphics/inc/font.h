#ifndef FONT_H_0JALTO9Q
#define FONT_H_0JALTO9Q

#include "graphics/Global"
#include "core/Managed"

namespace bk {

class ITexture;

struct Glyph {
	u32 advance;
	u32 width;
	u32 height;
	u32 leftBearing;
	u32 topBearing;

	f32 texCoordX;
	f32 texCoordY;
	ITexture* tex;
};

/*!
 * \brief Font class declaration.
 */
class Font : public Managed {
public:
	virtual ~Font();

	Glyph glyph(const char) const;
	u32 size() const;

private:
	friend class Graphics;
	explicit Font(const string&, const unsigned int);
	BK_IMPL(Font);
};

} /* bk */

#endif /* end of include guard: FONT_H_0JALTO9Q */

