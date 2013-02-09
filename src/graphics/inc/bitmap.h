#ifndef BITMAP_H_QOEYDWMJ
#define BITMAP_H_QOEYDWMJ

#include "base.h"

#include "core/Managed"

/*!
 * \brief Bitmap class declaration.
 */
class Bitmap : public Managed {
public:
	static Bitmap* fromFile(const string&);

	BitmapFormat format() const;
	int height() const;
	int width() const;
	unsigned char* pixels() const;
	void flip(const BitmapFlipMode);

private:
	Bitmap(unsigned char*, const BitmapFormat, const int, const int);
	virtual ~Bitmap();

	unsigned char* m_pixels;
	BitmapFormat m_format;
	int m_width;
	int m_height;
};

#endif /* end of include guard: BITMAP_H_QOEYDWMJ */

