#include "bitmap.h"

#define STBI_FAILURE_USERMSG
#include "stb_image.c"

inline unsigned _pixelOffset(unsigned col, unsigned row, unsigned width, unsigned height, Bitmap::Format format) {
	return (row*width + col)*format;
}

Bitmap::Bitmap(unsigned char* pixels, const Bitmap::Format format, const int width, const int height) :
	m_pixels(pixels), m_format(format), m_width(width), m_height(height)
{
}

Bitmap::~Bitmap()
{
	//delete[] m_pixels;
}

Bitmap* Bitmap::fromFile(const string& path)
{
	int width, height, channels;
	unsigned char* pixels = stbi_load(path.c_str(), &width, &height, &channels, 0);
	Bitmap *bmp = new Bitmap(pixels, (Bitmap::Format)channels, width, height);
	return bmp;
}

Bitmap::Format Bitmap::format() const
{
	return m_format;
}

int Bitmap::height() const
{
	return m_height;
}

int Bitmap::width() const
{
	return m_width;
}

unsigned char* Bitmap::pixels() const
{
	return m_pixels;
}

void Bitmap::flip(const Bitmap::FlipMode mode)
{
	// flip vertikal für den anfang
	//unsigned long rowSize = m_format * m_width;
	//BK_PRINT("rowSize: " << rowSize);
	//unsigned char* rowBuffer = new unsigned char[rowSize];
	//unsigned halfRows = m_height / 2;
	//BK_PRINT("halfRows: " << halfRows);

	//for (unsigned rowIdx = 0; rowIdx < halfRows; ++rowIdx) {
		//BK_PRINT(1);
		//unsigned char* row = m_pixels + _pixelOffset(0, rowIdx, m_width, m_height, m_format);
		//BK_PRINT(2);
		//unsigned char* oppositeRow = m_pixels + _pixelOffset(0, m_height - rowIdx - 1, m_width, m_height, m_format);
		//BK_PRINT(3);

		//memcpy(rowBuffer, row, rowSize);
		//BK_PRINT(4);
		//memcpy(row, oppositeRow, rowSize);
		//BK_PRINT(5);
		//memcpy(oppositeRow, rowBuffer, rowSize);
		//BK_PRINT(6);
	//}

	//delete rowBuffer;
}

