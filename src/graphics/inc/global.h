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

enum class ContextOption {
	ENABLE_3D, ENABLE_BLEND
};

enum class BitmapFormat {
	Grayscale = 1,
	GrayscaleAlpha = 2,
	RGB = 3,
	RGBA = 4
};

enum class BitmapFlipMode {
	HORIZONTALLY, VERTICALLY
};

enum class ShaderType {
	VERTEX, FRAGMENT
};

enum class MeshUsageHint {
	DYNAMIC, STATIC, STREAM
};

enum class ProgramVariableType {
	VERTEX, COLOR, TEXTURE0, TEXTURE1, TEXTURE2, TEXTURE3, TEXTURE4,
	TEXTURE5, TEXTURE6, TEXTURE7, CAMERA, TRANSFORMATION, NORMAL
};

class IShader;
typedef std::vector<IShader*> ShaderList;

} /* bk */

#endif /* end of include guard: GRAPHICS_H_06HZXMTV */

