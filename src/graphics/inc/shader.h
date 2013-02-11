#ifndef SHADER_H_UEZJIHHF
#define SHADER_H_UEZJIHHF

#include "base.h"

class IShader;

class Shader {
public:
	static IShader* fromFile( const string&, const ShaderType );
	static IShader* fromSource( const string&, const ShaderType );
};

#endif /* end of include guard: SHADER_H_UEZJIHHF */

