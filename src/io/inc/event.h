#ifndef EVENT_H_9WBX4PAI
#define EVENT_H_9WBX4PAI

#include "io/Global"
#include "core/Identity"

namespace bk {

/*!
 * \brief IEvent class declaration.
 */
class Event : public Identity {
public:
	Event(const string&, float);
	Event(const string&, float, StreamFunc);
	virtual ~Event();

	float timeStamp() const;
	void serialize(std::ostream&) const;
	void setStreamFunction(StreamFunc);
	StreamFunc streamFunction() const;

	/**
	 * TODO
	 * typ implementieren, der einen hash zurückliefert und
	 * konstanten in der globalen include datei dafür anlegen.
	 * als kandidaten käme der InputEvent in frage, mit INPUT als
	 * type konstanten.
	 */
	u32 type() const;

private:
	BK_IMPL(Event);
};

} /* bk */

#endif /* end of include guard: EVENT_H_9WBX4PAI */

