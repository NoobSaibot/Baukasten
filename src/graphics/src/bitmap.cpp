#include "graphics/Bitmap"

namespace {
inline unsigned _pixelOffset(unsigned col, unsigned row, unsigned width,
		unsigned height, bk::BitmapFormat format) {
	return (row*width + col)* static_cast<int>(format);
}
}

namespace bk {

Bitmap::Bitmap(const string& path, unsigned char* pixels,
		const BitmapFormat format, const int width, const int height) :
	Managed(path, "Bitmap"),
	m_pixels(pixels), m_format(format), m_width(width), m_height(height)
{
}

Bitmap::~Bitmap()
{
	SAFE_ARR_DELETE( m_pixels );
}

BitmapFormat Bitmap::format() const
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

void
Bitmap::flip(const BitmapFlipMode mode)
{
	// TODO mind the mode
	u32 rowSize = (u32)m_format * m_width;
	u8* rowBuffer = new u8[rowSize];
	u32 halfRows = m_height / 2;

	for (u32 rowIdx = 0; rowIdx < halfRows; ++rowIdx) {
		u8* row = m_pixels + _pixelOffset(0, rowIdx, m_width, m_height, m_format);
		u8* oppositeRow = m_pixels + _pixelOffset(0, m_height - rowIdx - 1, m_width, m_height, m_format);

		memcpy(rowBuffer, row, rowSize);
		memcpy(row, oppositeRow, rowSize);
		memcpy(oppositeRow, rowBuffer, rowSize);
	}

	SAFE_DELETE( rowBuffer );
}

}

