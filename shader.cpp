#include "shader.h"

#include "filesystem.h"
#include "ShaderImpl"

IShader*
Shader::fromFile( const string& path, const IShader::Type type )
{
	return Shader::fromSource( Filesystem::readAll( path ), type );
}

IShader*
Shader::fromSource( const string& source, const IShader::Type type )
{
	return new ShaderImpl( source, type );
}

