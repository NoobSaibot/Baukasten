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
#include "graphics/TextForm"
#include "graphics/Font"
#include "graphics/ProgramImpl"
#include "graphics/ShaderImpl"
#include "graphics/TextureImpl"
#include "io/Filesystem"

#define STBI_FAILURE_USERMSG
#include "3rdparty/stb_image.c"

namespace bk {

static IGraphics* s_graphics = new GraphicsImpl();

static IProgram* s_mvpBasic      = nullptr;
static IProgram* s_mvpBasicAlpha = nullptr;

static IProgram*
createStockProgram(const string& name, const string& vShader, const string& fShader)
{
	ShaderList shader;
	shader.push_back( Graphics::createShaderFromSource("v."+name, vShader, ShaderType::VERTEX) );
	shader.push_back( Graphics::createShaderFromSource("f."+name, fShader, ShaderType::FRAGMENT) );

	return Graphics::createProgram("program." + name, shader);
}

IDisplay*
Graphics::init(const u16 width, const u16 height, const string&)
{
	IDisplay* display = new DisplayImpl();
	display->init(width, height);

	// mvp_basic {{{
	s_mvpBasic = createStockProgram("shader.mvp_basic", R"(
		#version 130

		uniform mat4 projection;
		uniform mat4 camera;
		uniform mat4 transformation;

		in vec4 bk_vertex;
		in vec2 bk_texture0;
		in vec3 bk_color;

		out vec2 bk_fragTex0;
		out vec3 bk_Color;

		void main() {
			bk_fragTex0 = bk_texture0;
			bk_Color = bk_color;
			gl_Position = camera * transformation * bk_vertex;
		}
	)", R"(
		#version 130

		uniform sampler2D tex;
		uniform vec2 bk_texOffset0;
		uniform vec2 bk_texSize0;
		in vec2 bk_fragTex0;
		in vec3 bk_Color;

		void main() {
			gl_FragColor = texture(tex,  (bk_texSize0 * bk_fragTex0) + bk_texOffset0);
		}
	)");
	// }}}

	// mvb_basic_alpha {{{
	s_mvpBasicAlpha = createStockProgram("shader.mvp_basic", R"(
		#version 130

		uniform mat4 projection;
		uniform mat4 camera;
		uniform mat4 transformation;

		in vec4 bk_vertex;
		in vec2 bk_texture0;
		in vec3 bk_color;

		out vec2 bk_fragTex0;
		out vec3 bk_Color;

		void main() {
			bk_fragTex0 = bk_texture0;
			bk_Color = bk_color;
			gl_Position = camera * transformation * bk_vertex;
		}
	)", R"(
		#version 130

		uniform sampler2D tex;
		uniform vec2 bk_texOffset0;
		uniform vec2 bk_texSize0;
		in vec2 bk_fragTex0;
		in vec3 bk_Color;

		void main() {
			gl_FragColor = vec4(1, 1, 1, texture(tex, bk_fragTex0).r) * vec4(bk_Color, 1.0);
		}
	)");
	// }}}

	return display;
}

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

IForm*
Graphics::createTextForm(const string& name, const string& text,
		Font* font, IProgram* program, IDisplay* display)
{
	return new TextForm(name, text, font, program, display);
}

IForm*
Graphics::createTextForm(const string& name, const string& text,
		Font* font, IDisplay* display)
{
	return new TextForm(name, text, font, display);
}

Font*
Graphics::createFont(const string& name, const u32 pixelSize)
{
	return new Font(name, pixelSize);
}

IProgram*
Graphics::createProgram(const string& name, const ShaderList& shader)
{
	return new ProgramImpl(name, shader);
}

IProgram*
Graphics::stockProgram(const StockProgramName progName)
{
	BK_ASSERT(s_mvpBasicAlpha != nullptr, "Graphics has not been initialized properly! Did you forget to run Graphics::init()?");

	switch ( progName ) {
	case StockProgramName::MVP_BASIC:       return s_mvpBasic;
	case StockProgramName::MVP_BASIC_ALPHA: return s_mvpBasicAlpha;
	}
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
