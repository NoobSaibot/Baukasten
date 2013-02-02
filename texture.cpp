#include "texture.h"

#include "bitmap.h"
#include "itexture.h"
#include "TextureImpl"

ITexture* Texture::fromFile(const string& name)
{
	Bitmap *b = Bitmap::fromFile(name);
	ITexture *t = new TextureImpl(*b);
	return t;
}

ITexture* Texture::fromBitmap(Bitmap* bitmap)
{
	BK_ASSERT(bitmap);
	return new TextureImpl(*bitmap);
}

