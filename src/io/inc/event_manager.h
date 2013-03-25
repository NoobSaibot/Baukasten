#ifndef EVENT_MANAGER_H_P8VA9ENO
#define EVENT_MANAGER_H_P8VA9ENO

#include "io/Global"

namespace bk {

class Event;
class IObserver;

/*!
 * \brief EventManager class declaration.
 */
class EventManager {
public:
	static EventManager& instance();

	void subscribe(const string&, IObserver*);
	void unsubscribe(const string&, IObserver*);

	void registerEvent(const string&);
	void unregisterEvent(const string&);

	void emit(const string&, Event*);

	void queue(Event*);
	void dequeue(const string&);

	void tick();

private:
	BK_IMPL(EventManager);
	EventManager();
	EventManager(const EventManager&);
	virtual ~EventManager();

	static EventManager* s_instance;
};

} /* bk */

#endif /* end of include guard: EVENT_MANAGER_H_P8VA9ENO */

