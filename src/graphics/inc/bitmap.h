#ifndef BITMAP_H_QOEYDWMJ
#define BITMAP_H_QOEYDWMJ

#include "base.h"
#include "core/Identity"

namespace bk {

class Bitmap : public Identity {
public:
	static shared_ptr<Bitmap> fromFile(const string&);

	BitmapFormat format() const;
	int height() const;
	int width() const;
	unsigned char* pixels() const;
	void flip(const BitmapFlipMode);

	virtual ~Bitmap();

private:
	Bitmap(const string&, unsigned char*, const BitmapFormat,
			const int, const int);

	unsigned char* m_pixels;
	BitmapFormat m_format;
	int m_width;
	int m_height;
};

}

#endif /* end of include guard: BITMAP_H_QOEYDWMJ */

