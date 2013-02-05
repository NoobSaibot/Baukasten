#ifndef SHADER_H_UEZJIHHF
#define SHADER_H_UEZJIHHF

#include "base.h"
#include "ishader.h"

class Shader {
public:
	static IShader* fromFile( const string&, const IShader::Type );
	static IShader* fromSource( const string&, const IShader::Type );
};

#endif /* end of include guard: SHADER_H_UEZJIHHF */

