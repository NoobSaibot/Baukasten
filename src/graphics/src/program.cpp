#include "graphics/Program"

#include "graphics/ProgramImpl"

IProgram* Program::create(const ShaderList& shader)
{
	return new ProgramImpl(shader);
}

