#ifndef BITMAP_H_QOEYDWMJ
#define BITMAP_H_QOEYDWMJ

#include "core/Managed"
#include "graphics/Global"

namespace bk {

class Bitmap : public Managed {
public:
	static Bitmap* fromFile(const string&);

	BitmapFormat format() const;
	u32 height() const;
	u32 width() const;
	u8* pixels() const;
	void flip(const BitmapFlipMode);

	virtual ~Bitmap();

private:
	Bitmap(const string&, u8*, const BitmapFormat, const u32, const u32);

	friend class Graphics;
	unsigned char* m_pixels;
	BitmapFormat m_format;
	int m_width;
	int m_height;
};

}

#endif /* end of include guard: BITMAP_H_QOEYDWMJ */

