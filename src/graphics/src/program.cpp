#include "graphics/Program"

#include "graphics/ProgramImpl"

IProgram* Program::createProgram(const ShaderList& shader)
{
	return new ProgramImpl(shader);
}

