#include "input/Input"

#include "input/IInput"
#include "input/InputImpl"

namespace bk {

IInput*
Input::createInputSource(const string&)
{
	return new InputImpl();
}

} /* bk */
