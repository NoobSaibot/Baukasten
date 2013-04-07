#include "graphics/Graphics"

#include "core/Assert"
#include "core/Debug"
#include "graphics/Bitmap"
#include "graphics/Camera"
#include "graphics/ContextImpl"
#include "graphics/DisplayImpl"
#include "graphics/GraphicsImpl"
#include "graphics/MeshImpl"
#include "graphics/Form"
#include "graphics/ProgramImpl"
#include "graphics/ShaderImpl"
#include "graphics/TextureImpl"
#include "io/Filesystem"

#define STBI_FAILURE_USERMSG
#include "3rdparty/stb_image.c"

namespace bk {

static IGraphics* s_graphics = new GraphicsImpl();

Bitmap*
Graphics::createBitmapFromFile(const string& path)
{
	BK_ASSERT(Filesystem::exists(path), "File " << path << " must be present.");
	int width, height, channels;
	unsigned char* pixels = stbi_load(path.c_str(), &width, &height, &channels, 0);

	return new Bitmap(path, pixels, (BitmapFormat)channels, width, height);
}

Camera*
Graphics::createCamera(const string& name)
{
	return new Camera(name);
}

Camera*
Graphics::createCamera(const string& name, const float fieldOfView,
		const float aspectRatio, const float nearPlane, const float farPlane,
		const float horizontalAngle, const float verticalAngle,
		const vec3 position)
{
	return new Camera(name, fieldOfView, aspectRatio, nearPlane, farPlane,
			horizontalAngle, verticalAngle, position);
}

IContext*
Graphics::createContext(const string& name)
{
	return new ContextImpl(name);
}

IDisplay*
Graphics::createDisplay()
{
	return new DisplayImpl();
}

IMesh*
Graphics::createMesh(const string& name)
{
	IMesh* impl = new MeshImpl(name);
	return impl;
}

IMesh*
Graphics::createQuad(const string& name, IProgram* program,
		const float x, const float y, const float width)
{
	return createRect(name, program, x, y, width, width);
}

IMesh*
Graphics::createRect(const string& name, IProgram* program, const float x,
		const float y, const float width, const float height)
{
	IMesh* impl = new MeshImpl(name);

	impl->setProgram(program);

	impl->setVertices(18, 3, {
		x + width, y, 0.0f, x + width, y + height, 0.0f, x, y,  0.0f,
		x + width, y + height, 0.0f, x, y + height, 0.0f, x, y, 0.0f,
	});

	impl->setTexture(12, 2, {
		1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f
	});

	return impl;
}

IForm*
Graphics::createForm(const string& name, IMesh* mesh, IProgram* program,
		ITexture* texture, IDisplay* display)
{
	return new Form(name, mesh, program, texture, display);
}

IProgram*
Graphics::createProgram(const string& name, const ShaderList& shader)
{
	return new ProgramImpl(name, shader);
}

IShader*
Graphics::createShaderFromFile( const string& name, const string& path, const ShaderType type )
{
	return Graphics::createShaderFromSource( name, Filesystem::readAll( path ), type );
}

IShader*
Graphics::createShaderFromSource( const string& name, const string& source, const ShaderType type )
{
	return new ShaderImpl(name, source, type);
}

ITexture*
Graphics::createTextureFromFile(const string& name, const string& path)
{
	auto b = Graphics::createBitmapFromFile(path);
	return Graphics::createTextureFromBitmap(name, *b);
}

ITexture*
Graphics::createTextureFromData(const string& name, const unsigned int width,
		const unsigned int height, unsigned char* data, const VertexDataType type)
{
	ITexture* t = new TextureImpl(name);
	t->init(width, height, data, type);
	return t;
}

ITexture*
Graphics::createTextureFromBitmap(const string& name, const Bitmap& bitmap)
{
	ITexture* t = new TextureImpl(name);
	t->init(bitmap);
	return t;
}

IGraphics*
Graphics::graphics()
{
	return s_graphics;
}

} /* bk */
