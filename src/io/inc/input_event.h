#ifndef INPUT_EVENT_H_JQQKZP4V
#define INPUT_EVENT_H_JQQKZP4V

#include "input/Global"
#include "io/Event"
#include "io/Global"

namespace bk {

/*!
 * \brief InputEvent class declaration.
 */
class InputEvent : public Event {
public:
	InputEvent(const string&, const f32, const Key);
	virtual ~InputEvent();

	Key key() const;

private:
	BK_IMPL(InputEvent);
};

} /*  bk */

#endif /* end of include guard: INPUT_EVENT_H_JQQKZP4V */

