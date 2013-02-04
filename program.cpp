#include "program.h"

#include "ProgramImpl"

IProgram* Program::createProgram(const Shaders& shader)
{
	return new ProgramImpl(shader);
}

