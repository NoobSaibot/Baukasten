#include "graphics/Texture"

#include "graphics/Bitmap"
#include "graphics/ITexture"
#include "graphics/TextureImpl"

shared_ptr<ITexture>
Texture::fromFile(const string& name)
{
	auto b = Bitmap::fromFile(name);
	return Texture::fromBitmap(*b);
}

shared_ptr<ITexture>
Texture::fromBitmap(const Bitmap& bitmap)
{
	shared_ptr<ITexture> t(new TextureImpl());
	t->init(bitmap);
	return t;
}

