#ifndef SHADER_H_UEZJIHHF
#define SHADER_H_UEZJIHHF

#include "base.h"

class IShader;

class Shader {
public:
	static shared_ptr<IShader> fromFile( const string&, const string&,
			const ShaderType );

	static shared_ptr<IShader> fromSource( const string&, const string&,
			const ShaderType );
};

#endif /* end of include guard: SHADER_H_UEZJIHHF */

