#include "graphics/Program"

#include "graphics/ProgramImpl"

shared_ptr<IProgram>
Program::create(const string& name, const ShaderList& shader)
{
	return shared_ptr<IProgram>(new ProgramImpl(name, shader));
}

