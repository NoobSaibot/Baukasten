#include "graphics/Texture"

#include "graphics/Bitmap"
#include "graphics/ITexture"
#include "graphics/TextureImpl"

ITexture* Texture::fromFile(const string& name)
{
	Bitmap *b = Bitmap::fromFile(name);
	return Texture::fromBitmap(*b);
}

ITexture* Texture::fromBitmap(const Bitmap& bitmap)
{
	ITexture *t = new TextureImpl();
	t->init(bitmap);
	return t;
}

