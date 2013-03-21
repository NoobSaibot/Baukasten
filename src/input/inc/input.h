#ifndef INPUT_H_GMSS6XEP
#define INPUT_H_GMSS6XEP

#include "input/Global"

namespace bk {

class IInput;

/*!
 * \brief Input class declaration.
 */
class Input {
public:
	static IInput* createInputSource(const string&);
};

} /* bk */

#endif /* end of include guard: INPUT_H_GMSS6XEP */

