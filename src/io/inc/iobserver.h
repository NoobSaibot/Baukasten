#ifndef IOBSERVER_H_PR7XVEUG
#define IOBSERVER_H_PR7XVEUG

#include "io/Global"

namespace bk {

class Event;

/*!
 * \brief IObserver class declaration.
 */
class IObserver {
public:
	virtual bool handleEvent(Event*) = 0;
};

} /* bk */

#endif /* end of include guard: IOBSERVER_H_PR7XVEUG */

