#include "graphics/Graphics"

#include "core/Assert"
#include "graphics/Bitmap"
#include "graphics/Camera"
#include "graphics/Context"
#include "graphics/DisplayImpl"
#include "graphics/MeshImpl"
#include "graphics/Model"
#include "graphics/ProgramImpl"
#include "graphics/ShaderImpl"
#include "graphics/TextureImpl"
#include "graphics/VertexFormat"
#include "io/Filesystem"

#define STBI_FAILURE_USERMSG
#include "3rdparty/stb_image.c"

namespace bk {

Bitmap*
Graphics::createBitmapFromFile(const string& path)
{
	BK_ASSERT(Filesystem::exists(path), "File must be present.");
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

Context*
Graphics::createContext(const string& name)
{
	return new Context(name);
}

IDisplay*
Graphics::createDisplay()
{
	return new DisplayImpl();
}

IMesh*
Graphics::createMesh(const string& name, const IProgram& program,
		const float* data, const MeshUsageHint hint,
		const VertexFormat format, const int size)
{
	IMesh* impl = new MeshImpl(name);
	impl->init(program, data, hint, format, size);
	return impl;
}

IMesh*
Graphics::createQuad(const string& name, const IProgram& program,
		const float x, const float y, const float width)
{
	return createRect(name, program, x, y, width, width);
}

IMesh*
Graphics::createRect(const string& name, const IProgram& program, const float x,
		const float y, const float width, const float height)
{
	IMesh* impl = new MeshImpl(name);

	VertexFormat format = {
		VertexFormat::Data(VertexFormat::POSITION, 3, 0),
		VertexFormat::Data(VertexFormat::TEXCOORD0, 2, 3)
	};

	float vertices[] = {
		// x       y            z    tex-x tex-y
		x + width, y,          0.0f, 1.0f, 1.0f,
		x + width, y + height, 0.0f, 1.0f, 0.0f,
		x,         y,          0.0f, 0.0f, 1.0f,
		x + width, y + height, 0.0f, 1.0f, 0.0f,
		x,         y + height, 0.0f, 0.0f, 0.0f,
		x,         y,          0.0f, 0.0f, 1.0f
	};

	impl->init(program, vertices, MeshUsageHint::STATIC, format, sizeof(vertices));
	return impl;
}

Model*
Graphics::createModel(const string& name, IMesh* mesh, IProgram* program, ITexture* texture)
{
	return new Model(name, mesh, program, texture);
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
Graphics::createTextureFromBitmap(const string& name, const Bitmap& bitmap)
{
	ITexture* t = new TextureImpl(name);
	t->init(bitmap);
	return t;
}

} /* bk */
