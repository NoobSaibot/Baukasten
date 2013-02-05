#include "program.h"

#include "ProgramImpl"

IProgram* Program::createProgram(const ShaderList& shader)
{
	return new ProgramImpl(shader);
}

