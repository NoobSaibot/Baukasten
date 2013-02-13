#include "graphics/Texture"

#include "graphics/Bitmap"
#include "graphics/ITexture"
#include "graphics/TextureImpl"

shared_ptr<ITexture>
Texture::fromFile(const string& name, const string& path)
{
	auto b = Bitmap::fromFile(path);
	return Texture::fromBitmap(name, *b);
}

shared_ptr<ITexture>
Texture::fromBitmap(const string& name, const Bitmap& bitmap)
{
	auto t = shared_ptr<ITexture>(new TextureImpl(name));
	t->init(bitmap);
	return t;
}

