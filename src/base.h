#ifndef BASE_H_FIQRYC3F
#define BASE_H_FIQRYC3F

#define GLEW_STATIC
#include <GL/glew.h>
#include <GL/gl.h>
#include <GL/glfw.h>
#include <cassert>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>
#include <list>
#include <memory>
#include <sstream>
#include <string>
#include <vector>

using namespace std;
using namespace glm;

namespace bk {

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

class IShader;
typedef vector<shared_ptr<IShader>> ShaderList;

}

#define BK_IMPL(X) class X##Private* m_impl; friend class X##Private
#define BK_STRINGIFY(X) #X

#define SAFE_DELETE(X) { if(X) { delete X; X = NULL; } }

#include "core/Debug"

#endif /* end of include guard: BASE_H_FIQRYC3F */

