#ifndef BASE_H_FIQRYC3F
#define BASE_H_FIQRYC3F

#define GLEW_STATIC
#include <GL/glew.h>
#include <GL/gl.h>
#include <GL/glfw.h>
#include <cassert>
#include <iostream>
#include <list>
#include <string>
#include <sstream>
#include <vector>

using namespace std;

class Shader;
typedef vector<Shader*> Shaders;

class Vertex;
typedef vector<Vertex*> Vertices;

#include "debug.h"

#endif /* end of include guard: BASE_H_FIQRYC3F */

