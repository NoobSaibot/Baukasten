#include "graphics/Shader"

#include "graphics/ShaderImpl"
#include "io/Filesystem"

namespace bk {

shared_ptr<IShader>
Shader::fromFile( const string& name, const string& path,
		const ShaderType type )
{
	return Shader::fromSource( name, Filesystem::readAll( path ), type );
}

shared_ptr<IShader>
Shader::fromSource( const string& name, const string& source,
		const ShaderType type )
{
	return shared_ptr<IShader>(new ShaderImpl(name, source, type));
}

}

