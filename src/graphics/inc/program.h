#ifndef PROGRAM_H_CYWMYDXG
#define PROGRAM_H_CYWMYDXG

#include "base.h"
#include "ishader.h"

class IProgram;

/*!
 * \brief Program class declaration.
 */
class Program {
public:
	static IProgram* create(const ShaderList&);
};

#endif /* end of include guard: PROGRAM_H_CYWMYDXG */

