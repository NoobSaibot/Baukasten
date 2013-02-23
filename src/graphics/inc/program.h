#ifndef PROGRAM_H_CYWMYDXG
#define PROGRAM_H_CYWMYDXG

#include "base.h"
#include "ishader.h"

namespace bk {

class IProgram;

class Program {
public:
	static shared_ptr<IProgram> create(const string&, const ShaderList&);
};

}

#endif /* end of include guard: PROGRAM_H_CYWMYDXG */

