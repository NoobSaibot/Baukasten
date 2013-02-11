#include "graphics/Program"

#include "graphics/ProgramImpl"

shared_ptr<IProgram>
Program::create(const ShaderList& shader)
{
	return shared_ptr<ProgramImpl>(new ProgramImpl(shader));
}

