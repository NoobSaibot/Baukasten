#ifndef GRAPHICS_H_06HZXMTV
#define GRAPHICS_H_06HZXMTV

#include "core/Global"

#define GLEW_STATIC
#include <GL/glew.h>
#include <GL/gl.h>
#include <GL/glfw.h>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace bk {

using namespace std;
using namespace glm;

enum class BitmapFormat {
	Grayscale = 1,
	GrayscaleAlpha = 2,
	RGB = 3,
	RGBA = 4
};

enum class BitmapFlipMode {
	HORIZONTALLY, VERTICALLY
};

enum class DisplayMode {
	POINT, WIREFRAME, FULL
};

enum class GraphicsOption {
	DEPTH, BLEND, CULLING
};

enum class ShaderType {
	VERTEX, FRAGMENT
};

enum class MeshUsageHint {
	DYNAMIC, STATIC, STREAM
};

enum class PrimitiveType {
	POINTS, LINE_STRIP, LINE_LOOP, LINES,
	TRIANGLE_STRIP, TRIANGLE_FAN, TRIANGLES, PATCH
};

enum class ProgramVariableType {
	VERTEX, COLOR, TEXTURE0, TEXTURE1, TEXTURE2, TEXTURE3, TEXTURE4,
	TEXTURE5, TEXTURE6, TEXTURE7, CAMERA, TRANSFORMATION, NORMAL
};

enum class StockProgramName {
	MVP_BASIC, MVP_BASIC_ALPHA
};

enum class VertexDataType {
	DEPTH_COMPONENT, DEPTH_STENCIL, INTENSITY, RED, RG, RGB, RGBA,
	COMPRESSED_RED, COMPRESSED_RG,

	ALPHA, LUMINANCE, LUMINANCE_ALPHA
};

enum class VertexDataFormat {
	DEPTH_COMPONENT, DEPTH_STENCIL, RED, GREEN, BLUE, RG, RGB, RGBA, BGR,
	BGRA, RED_INTEGER, GREEN_INTEGER, BLUE_INTEGER, RG_INTEGER, RGB_INEGER,
	RGBA_INTEGER, BGR_INTEGER, BGRA_INTEGER
};

enum class CharInfoType {
	WIDTH, HEIGHT, LEFT, TOP, X, Y, OFFSET
};

class IShader;
typedef std::vector<IShader*> ShaderList;

class IMesh;
typedef std::shared_ptr<IMesh> IMeshPtr;

class ITexture;
typedef std::shared_ptr<ITexture> ITexturePtr;

} /* bk */

#endif /* end of include guard: GRAPHICS_H_06HZXMTV */

