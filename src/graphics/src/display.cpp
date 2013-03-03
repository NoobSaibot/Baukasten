#include "graphics/Display"

#include "graphics/DisplayImpl"

namespace bk {

IDisplay*
Display::create()
{
	return new DisplayImpl();
}

} /*  bk */
