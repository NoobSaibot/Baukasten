#ifndef BITMAP_H_QOEYDWMJ
#define BITMAP_H_QOEYDWMJ

#include "base.h"

/*!
 * \brief Bitmap class declaration.
 */
class Bitmap {
public:
	enum Format {
		Format_Grayscale = 1,
		Format_GrayscaleAlpha = 2,
		Format_RGB = 3,
		Format_RGBA = 4
	};

	enum FlipMode {
		HORIZONTALLY, VERTICALLY
	};

	static Bitmap* fromFile(const string&);

	Format format() const;
	int height() const;
	int width() const;
	unsigned char* pixels() const;
	void flip(const FlipMode);

private:
	Bitmap(unsigned char*, const Format, const int, const int);
	virtual ~Bitmap();

	unsigned char* m_pixels;
	Format m_format;
	int m_width;
	int m_height;
};

#endif /* end of include guard: BITMAP_H_QOEYDWMJ */

