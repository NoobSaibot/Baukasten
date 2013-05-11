#ifndef GRAPHICS_H_2SOCX0AI
#define GRAPHICS_H_2SOCX0AI

#include "graphics/Global"
#include "math/Vector3"

namespace bk {

class Bitmap;
class Camera;
class Context;
class IDisplay;
class IGraphics;
class IMesh;
class IForm;
class Font;
class IProgram;
class IShader;
class ITexture;

class Graphics {
public:
	static Bitmap* createBitmapFromFile(const string&);
	static Camera* createCamera(const string&);
	static Camera* createCamera(const string&, const float,
			const float, const float, const float, const float,
			const float, const vec3);
	static Context* createContext(const string&);
	static IMesh* createMesh(const string&);
	static IMesh* createQuad(const string&, IProgram*,
			const float, const float, const float);
	static IMesh* createRect(const string&, IProgram*,
			const float, const float, const float, const float);
	static IMesh* createCube(const string&, IProgram*, const u32,
			const Vector3& color = Vector3(0.5, 0.5, 0.5));
	static IMesh* createTorus(const string&, IProgram*, const f32, const f32,
		const u32, const u32, const Vector3& color = Vector3(0.5, 0.5, 0.5));
	static IMesh* createSphere(const string&, IProgram*, const u32,
		const u32, const u32, const Vector3& color = Vector3(0.5, 0.5, 0.5));
	static IForm* createForm(const string&, IMesh*,
			IProgram*, ITexture*, IDisplay*);
	static IForm* createTextForm(const string&, const string&, Font*,
			IProgram*, IDisplay*);
	static IForm* createTextForm(const string&, const string&, Font*, IDisplay*);
	static Font* createFont(const string&, const u32);
	static IProgram* createProgram(const string&, const ShaderList&);
	static IProgram* stockProgram(const StockProgramName);
	static IShader* createShaderFromFile( const string&, const string&,
			const ShaderType );
	static IShader* createShaderFromSource( const string&, const string&,
			const ShaderType );
	static ITexture* createSkyBox( const string&, const string&, const string&,
		const string&, const string&, const string&, const string&);
	static ITexture* createTextureFromFile(const string&, const string&);
	static ITexture* createTextureFromData(const string&, const unsigned int,
			const unsigned int, unsigned char*, const VertexDataType);
	static ITexture* createTextureFromBitmap(const string&, const Bitmap&);

	static IGraphics* graphics();

	// erstelle fenster hier
	static IDisplay* init(const u16, const u16, const string&);
};

} /* bk */

#endif /* end of include guard: GRAPHICS_H_2SOCX0AI */

