#ifndef GRAPHICS_H_2SOCX0AI
#define GRAPHICS_H_2SOCX0AI

#include "graphics/Global"

namespace bk {

class Bitmap;
class Camera;
class IContext;
class IDisplay;
class IMesh;
class Form;
class IProgram;
class IShader;
class ITexture;
class VertexFormat;

class Graphics {
public:
	static Bitmap* createBitmapFromFile(const string&);
	static Camera* createCamera(const string&);
	static Camera* createCamera(const string&, const float,
			const float, const float, const float, const float,
			const float, const vec3);
	static IContext* createContext(const string&);
	static IDisplay* createDisplay();
	static IMesh* createMesh(const string&, const IProgram&,
			const float*, const MeshUsageHint, const VertexFormat, const int);
	static IMesh* createQuad(const string&, const IProgram&,
			const float, const float, const float);
	static IMesh* createRect(const string&, const IProgram&,
			const float, const float, const float, const float);
	static Form* createForm(const string&, IMesh*, IProgram*, ITexture*);
	static IProgram* createProgram(const string&, const ShaderList&);
	static IShader* createShaderFromFile( const string&, const string&,
			const ShaderType );
	static IShader* createShaderFromSource( const string&, const string&,
			const ShaderType );
	static ITexture* createTextureFromFile(const string&, const string&);
	static ITexture* createTextureFromBitmap(const string&, const Bitmap&);
};

} /* bk */

#endif /* end of include guard: GRAPHICS_H_2SOCX0AI */

