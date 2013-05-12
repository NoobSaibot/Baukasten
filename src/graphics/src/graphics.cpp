#include "graphics/Graphics"

#include "core/Assert"
#include "core/Debug"
#include "graphics/Bitmap"
#include "graphics/Camera"
#include "graphics/Context"
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

static IProgram* s_mBasicRed     = nullptr;
static IProgram* s_mvpBasicCol   = nullptr;
static IProgram* s_mvpBasicTex   = nullptr;
static IProgram* s_mvpBasicRed   = nullptr;
static IProgram* s_skyBox        = nullptr;

static IProgram*
createStockProgram(const string& name, const string& vShader, const string& fShader)
{
	ShaderList shader;
	shader.push_back( Graphics::createShaderFromSource("v."+name, vShader, ShaderType::VERTEX) );
	shader.push_back( Graphics::createShaderFromSource("f."+name, fShader, ShaderType::FRAGMENT) );

	return Graphics::createProgram("program." + name, shader);
}

IDisplay*
Graphics::init(const u16 width, const u16 height, const bool fullScreen, const string&)
{
	IDisplay* display = new DisplayImpl();
	display->init(width, height, fullScreen);

	// m_basic_red {{{
	s_mBasicRed = createStockProgram("shader.mvp_basic", R"(
		#version 130

		uniform mat4 projection;
		uniform mat4 camera;
		uniform mat4 transformation;

		in vec4 bk_vertex;
		in vec2 bk_texture0;
		in vec3 bk_color;
		in vec3 bk_normal;

		out vec2 bk_fragTex0;
		out vec3 bk_Color;

		void main() {
			bk_fragTex0 = bk_texture0;
			bk_Color = bk_color;
			gl_Position = transformation * bk_vertex;
		}
	)", R"(
		#version 130

		uniform sampler2D tex;
		uniform vec2 bk_texOffset0;
		uniform vec2 bk_texSize0;
		in vec2 bk_fragTex0;
		in vec3 bk_Color;

		out vec4 bk_FragColor;

		void main() {
			bk_FragColor = vec4(1, 1, 1, texture(tex, bk_fragTex0).r) * vec4(bk_Color, 1.0);
		}
	)");
	// }}}

	// mvp_basic_col {{{
	s_mvpBasicCol = createStockProgram("shader.mvp_basic_col", R"(
		#version 130

		uniform mat4 projection;
		uniform mat4 camera;
		uniform mat4 transformation;

		in vec4 bk_vertex;
		in vec2 bk_texture0;
		in vec3 bk_color;
		in vec3 bk_normal;

		out vec2 bk_fragTex0;
		out vec3 bk_Color;
		out vec3 bk_Normal;

		void main() {
			bk_fragTex0 = bk_texture0;
			bk_Color = bk_color;
			bk_Normal = bk_normal;
			gl_Position = camera * transformation * bk_vertex;
		}
	)", R"(
		#version 130

		in vec2 bk_fragTex0;
		in vec3 bk_Color;
		in vec3 bk_Normal;

		out vec4 bk_FragColor;

		void main() {
			bk_FragColor = vec4(bk_Color, 1.0);
		}
	)");
	// }}}

	// mvp_basic_tex {{{
	s_mvpBasicTex = createStockProgram("shader.mvp_basic_tex", R"(
		#version 130

		uniform mat4 projection;
		uniform mat4 camera;
		uniform mat4 transformation;

		in vec4 bk_vertex;
		in vec2 bk_texture0;
		in vec3 bk_color;
		in vec3 bk_normal;

		out vec2 bk_fragTex0;
		out vec3 bk_Color;
		out vec3 bk_Normal;

		void main() {
			bk_fragTex0 = bk_texture0;
			bk_Color = bk_color;
			bk_Normal = bk_normal;
			gl_Position = camera * transformation * bk_vertex;
		}
	)", R"(
		#version 130

		uniform sampler2D tex;
		uniform vec2 bk_texOffset0;
		uniform vec2 bk_texSize0;
		in vec2 bk_fragTex0;
		in vec3 bk_Color;
		in vec3 bk_Normal;

		out vec4 bk_FragColor;

		void main() {
			bk_FragColor = texture(tex,  (bk_texSize0 * bk_fragTex0) + bk_texOffset0);
		}
	)");
	// }}}

	// mvb_basic_red {{{
	s_mvpBasicRed = createStockProgram("shader.mvp_basic", R"(
		#version 130

		uniform mat4 projection;
		uniform mat4 camera;
		uniform mat4 transformation;

		in vec4 bk_vertex;
		in vec2 bk_texture0;
		in vec3 bk_color;
		in vec3 bk_normal;

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

		out vec4 bk_FragColor;

		void main() {
			bk_FragColor = vec4(1, 1, 1, texture(tex, bk_fragTex0).r) * vec4(bk_Color, 1.0);
		}
	)");
	// }}}

	// skyBox {{{
	s_skyBox = createStockProgram("shader.skybox", R"(
		#version 130

		uniform mat4 projection;
		uniform mat4 camera;
		uniform mat4 transformation;

		in vec4 bk_vertex;
		in vec2 bk_texture0;

		out vec3 bk_fragTex0;

		void main() {
			bk_fragTex0 = normalize(bk_vertex.xyz);
			gl_Position = camera * bk_vertex;
		}
	)", R"(
		#version 130

		uniform samplerCube tex;
		in vec3 bk_fragTex0;

		out vec4 bk_FragColor;

		void main() {
			bk_FragColor = texture(tex,  bk_fragTex0);
		}
	)");
	// }}}

	return display;
}

Bitmap*
Graphics::createBitmapFromFile(const string& path)
{
	BK_ASSERT(Filesystem::exists(path), "File " << path << " must be present.");
	u32 width, height, channels;
	u8* pixels = stbi_load(path.c_str(), &width, &height, &channels, 0);

	auto bitmap = new Bitmap(path, pixels, (BitmapFormat)channels, width, height);
	bitmap->flip(BitmapFlipMode::VERTICALLY);
	return bitmap;
}

Camera*
Graphics::createCamera(const string& name)
{
	return new Camera(name);
}

Camera*
Graphics::createCamera(const string& name, const f32 fieldOfView,
		const f32 aspectRatio, const f32 nearPlane, const f32 farPlane,
		const f32 horizontalAngle, const f32 verticalAngle,
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

IMesh*
Graphics::createMesh(const string& name)
{
	IMesh* impl = new MeshImpl(name);
	return impl;
}

IMesh*
Graphics::createQuad(const string& name, IProgram* program,
		const f32 x, const f32 y, const f32 width)
{
	return createRect(name, program, x, y, width, width);
}

IMesh*
Graphics::createRect(const string& name, IProgram* program, const f32 x,
		const f32 y, const f32 width, const f32 height)
{
	IMesh* mesh = new MeshImpl(name);

	mesh->setProgram(program);

	mesh->setVertices(18, 3, {
		x + width, y, 0.0f, x + width, y + height, 0.0f, x, y,  0.0f,
		x + width, y + height, 0.0f, x, y + height, 0.0f, x, y, 0.0f,
	});

	mesh->setTexture(12, 2, {
		1.0f, 0.0f,
		1.0f, 1.0f,
		0.0f, 0.0f,
		1.0f, 1.0f,
		0.0f, 1.0f,
		0.0f, 0.0f
	});

	return mesh;
}

IMesh*
Graphics::createCube(const string& name, IProgram* program, const u32 size,
	const Vector3& color)
{
	IMesh *mesh = new MeshImpl(name);
	mesh->setProgram(program);

	vector<f32> vertices;
	vector<f32> colors;
	vector<f32> normals;
	vector<f32> texture;
	vector<u16> indices;

	auto maxX =  1.0f * size / 2;
	auto minX = -1.0f * size / 2;
	auto maxY =  1.0f * size / 2;
	auto minY = -1.0f * size / 2;
	auto maxZ =  1.0f * size / 2;
	auto minZ = -1.0f * size / 2;

	BK_ASSERT(size > 0, "The size must be greater than 0.");

	vertices.resize(8 * 3);
	colors.resize(8 * 3);
	indices.resize(6 * 3 * 2);
	texture.resize(8 * 2);

	mesh->setVertices(108, 3, {
		// bottom
		minX,minY,minZ,
		maxX,minY,minZ,
		minX,minY,maxZ,
		maxX,minY,minZ,
		maxX,minY,maxZ,
		minX,minY,maxZ,

		// top
		minX,maxY,minZ,
		minX,maxY,maxZ,
		maxX,maxY,minZ,
		maxX,maxY,minZ,
		minX,maxY,maxZ,
		maxX,maxY,maxZ,

		// front
		minX,minY,maxZ,
		maxX,minY,maxZ,
		minX,maxY,maxZ,
		maxX,minY,maxZ,
		maxX,maxY,maxZ,
		minX,maxY,maxZ,

		minX,minY,minZ,
		minX,maxY,minZ,
		maxX,minY,minZ,
		maxX,minY,minZ,
		minX,maxY,minZ,
		maxX,maxY,minZ,

		minX,minY,maxZ,
		minX,maxY,minZ,
		minX,minY,minZ,
		minX,minY,maxZ,
		minX,maxY,maxZ,
		minX,maxY,minZ,

		maxX,minY,maxZ,
		maxX,minY,minZ,
		maxX,maxY,minZ,
		maxX,minY,maxZ,
		maxX,maxY,minZ,
		maxX,maxY,maxZ
	});

	mesh->setColors(108, 3, {
		color.r, color.g, color.b,
		color.r, color.g, color.b,
		color.r, color.g, color.b,
		color.r, color.g, color.b,
		color.r, color.g, color.b,
		color.r, color.g, color.b,
		color.r, color.g, color.b,
		color.r, color.g, color.b,
		color.r, color.g, color.b,
		color.r, color.g, color.b,
		color.r, color.g, color.b,
		color.r, color.g, color.b,
		color.r, color.g, color.b,
		color.r, color.g, color.b,
		color.r, color.g, color.b,
		color.r, color.g, color.b,
		color.r, color.g, color.b,
		color.r, color.g, color.b,
		color.r, color.g, color.b,
		color.r, color.g, color.b,
		color.r, color.g, color.b,
		color.r, color.g, color.b,
		color.r, color.g, color.b,
		color.r, color.g, color.b,
		color.r, color.g, color.b,
		color.r, color.g, color.b,
		color.r, color.g, color.b,
		color.r, color.g, color.b,
		color.r, color.g, color.b,
		color.r, color.g, color.b,
		color.r, color.g, color.b,
		color.r, color.g, color.b,
		color.r, color.g, color.b,
		color.r, color.g, color.b,
		color.r, color.g, color.b,
		color.r, color.g, color.b
	});

	mesh->setTexture(72, 2, {
		0.0f, 0.0f,
		1.0f, 0.0f,
		0.0f, 1.0f,
		1.0f, 0.0f,
		1.0f, 1.0f,
		0.0f, 1.0f,
		0.0f, 0.0f,
		0.0f, 1.0f,
		1.0f, 0.0f,
		1.0f, 0.0f,
		0.0f, 1.0f,
		1.0f, 1.0f,
		1.0f, 0.0f,
		0.0f, 0.0f,
		1.0f, 1.0f,
		0.0f, 0.0f,
		0.0f, 1.0f,
		1.0f, 1.0f,
		0.0f, 0.0f,
		0.0f, 1.0f,
		1.0f, 0.0f,
		1.0f, 0.0f,
		0.0f, 1.0f,
		1.0f, 1.0f,
		0.0f, 1.0f,
		1.0f, 0.0f,
		0.0f, 0.0f,
		0.0f, 1.0f,
		1.0f, 1.0f,
		1.0f, 0.0f,
		1.0f, 1.0f,
		1.0f, 0.0f,
		0.0f, 0.0f,
		1.0f, 1.0f,
		0.0f, 0.0f,
		0.0f, 1.0f
	});

	return mesh;
}

IMesh*
Graphics::createSphere(const string& name, IProgram* program, const u32 radius,
	const u32 rings, const u32 segments, const Vector3& color)
{
	IMesh *mesh = new MeshImpl(name);
	mesh->setProgram(program);

	vector<f32> vertices;
	vector<f32> colors;
	vector<f32> normals;
	vector<f32> texture;
	vector<u16> indices;

	BK_ASSERT(rings > 1, "The amount of rings must be greater than 1.");
	BK_ASSERT(segments > 1, "The amount of segments must be greater than 1.");

	vertices.resize((rings + 1) * (segments    ) * 3 );
	colors.resize(  (rings + 1) * (segments    ) * 3 );
	indices.resize( (rings + 1) * (segments    ) * 6 );
	texture.resize( (rings + 1) * (segments + 1) * 2 );

	auto v = vertices.begin();
	auto c = colors.begin();
	auto i = indices.begin();
	auto t = texture.begin();

	auto dTheta = M_PI / (f32)rings;
	auto dPhi   = 2 * M_PI / (f32)segments;

	// loop has to go from 0 to rings (not rings-1) so that the
	// dTheta goes "full" half circle to close the sphere at the bottom
	for ( u32 ring = 0; ring <= rings; ++ring ) {
		auto r0 = radius * sinf(ring * dTheta);
		auto y0 = radius * cosf(ring * dTheta);
		for ( u32 segment = 0; segment < segments; ++segment ) {
			auto x0 = r0 * sinf(segment * dPhi);
			auto z0 = r0 * cosf(segment * dPhi);

			*v++ = x0;  *c++ = color.r;
			*v++ = y0;  *c++ = color.g;
			*v++ = z0;  *c++ = color.b;

			*t++ = (f32)segment / (f32)segments;
			*t++ = (f32)ring / (f32)rings;

			if (ring < rings) {
				*i++ = ( (ring  ) * segments ) + segment;
				*i++ = ( (ring+1) * segments ) + segment;
				*i++ = ( (ring+1) * segments ) + (segment + 1) % segments;
				*i++ = ( (ring+1) * segments ) + (segment + 1) % segments;
				*i++ = ( (ring  ) * segments ) + (segment + 1) % segments;
				*i++ = ( (ring  ) * segments ) + segment;
			}
		}
	}

	mesh->setVertices(vertices.size(), 3, vertices.data());
	mesh->setColors(colors.size(), 3, colors.data());
	mesh->setIndices(indices.size(), indices.data());
	mesh->setTexture(texture.size(), 2, texture.data());

	return mesh;
}

IMesh*
Graphics::createTorus(const string& name, IProgram* program, const f32 oRadius,
	const f32 iRadius, const u32 rings, const u32 segments, const Vector3& color)
{
	IMesh *mesh = new MeshImpl(name);
	mesh->setProgram(program);

	vector<f32> vertices;
	vector<f32> colors;
	vector<f32> normals;
	vector<f32> texture;
	vector<u16> indices;

	vertices.resize( (rings + 1) * segments * 3 );
	indices.resize(  (rings + 1) * segments * 6 );
	colors.resize(   (rings + 1) * segments * 3 );
	texture.resize(  (rings + 1) * (segments + 1) * 2 );

	auto dTheta = 2 * M_PI / rings;
	auto dPhi   = 2 * M_PI / segments;

	auto r  = oRadius - iRadius;

	auto v = vertices.begin();
	auto i = indices.begin();
	auto c = colors.begin();
	auto t = texture.begin();

	for ( u32 ring = 0; ring <= rings; ++ring ) {
		auto theta = ring * dTheta;

		for ( u32 segment = 0; segment < segments; ++segment ) {
			auto phi = segment * dPhi;

			auto x0 = ( ( iRadius + r * cosf(phi) ) * cosf(theta) );
			auto y0 = ( ( iRadius + r * cosf(phi) ) * sinf(theta) );
			auto z0 = r * sinf(phi);

			*v++ = x0; *c++ = color.r;
			*v++ = y0; *c++ = color.g;
			*v++ = z0; *c++ = color.b;

			*t++ = (f32)segment / (f32)segments;
			*t++ = (f32)ring / (f32)rings;

			if (ring < rings) {
				*i++ = ( (ring  ) * segments ) + segment;
				*i++ = ( (ring+1) * segments ) + segment;
				*i++ = ( (ring+1) * segments ) + (segment + 1) % segments;
				*i++ = ( (ring+1) * segments ) + (segment + 1) % segments;
				*i++ = ( (ring  ) * segments ) + (segment + 1) % segments;
				*i++ = ( (ring  ) * segments ) + segment;
			}
		}
	}

	mesh->setVertices(vertices.size(), 3, vertices.data());
	mesh->setIndices(indices.size(), indices.data());
	mesh->setColors(colors.size(), 3, colors.data());
	mesh->setTexture(texture.size(), 2, texture.data());

	return mesh;
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
	BK_ASSERT(s_mBasicRed != nullptr, "Graphics has not been initialized properly! Did you forget to run Graphics::init()?");

	switch ( progName ) {
	case StockProgramName::M_BASIC_RED:   return s_mBasicRed;
	case StockProgramName::MVP_BASIC_TEX: return s_mvpBasicTex;
	case StockProgramName::MVP_BASIC_COL: return s_mvpBasicCol;
	case StockProgramName::MVP_BASIC_RED: return s_mvpBasicRed;
	case StockProgramName::SKYBOX:        return s_skyBox;
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
Graphics::createSkyBox(const string& name, const string& posX, const string& negX,
	const string& posY, const string& negY, const string& posZ, const string& negZ )
{
	auto bPosX = Graphics::createBitmapFromFile(posX);
	auto bNegX = Graphics::createBitmapFromFile(negX);
	auto bPosY = Graphics::createBitmapFromFile(posY);
	auto bNegY = Graphics::createBitmapFromFile(negY);
	auto bPosZ = Graphics::createBitmapFromFile(posZ);
	auto bNegZ = Graphics::createBitmapFromFile(negZ);

	ITexture* t = new TextureImpl(name, TextureTarget::TEXTURE_CUBE_MAP, 0);
	t->init(*bPosX, *bNegX, *bPosY, *bNegY, *bPosZ, *bNegZ);

	bPosX->release();
	bNegX->release();
	bPosY->release();
	bNegY->release();
	bPosZ->release();
	bNegZ->release();

	return t;
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
	ITexture* t = new TextureImpl(name, TextureTarget::TEXTURE_2D, 0);
	t->init(width, height, data, type);
	return t;
}

ITexture*
Graphics::createTextureFromBitmap(const string& name, const Bitmap& bitmap)
{
	ITexture* t = new TextureImpl(name, TextureTarget::TEXTURE_2D, 0);
	t->init(bitmap);
	return t;
}

IGraphics*
Graphics::graphics()
{
	return s_graphics;
}

} /* bk */
