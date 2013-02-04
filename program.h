#ifndef PROGRAM_H_CYWMYDXG
#define PROGRAM_H_CYWMYDXG

#include "base.h"

class IProgram;
class Shader;

/*!
 * \brief Program class declaration.
 */
class Program {
public:
	static IProgram* createProgram(const Shaders&);
};

#endif /* end of include guard: PROGRAM_H_CYWMYDXG */

