#include "io/EventManager"

#include "core/Assert"
#include "core/Debug"
#include "io/Event"
#include "io/IObserver"
#include "model/Actor"

#include <list>
#include <map>

namespace bk {

/*!
 * \brief EventManagerPrivate class declaration.
 */
class EventManagerPrivate {
public:
	EventManagerPrivate()
	{
	}

	~EventManagerPrivate()
	{
	}

	void subscribe(const string& name, IObserver* observer)
	{
		if (m_events.find(name) == m_events.end()) {
			m_events[name] = vector<IObserver*>();
		}
		m_events[name].push_back(observer);
	}

	void unsubscribe(const string& name, IObserver* observer)
	{
	}

	void registerEvent(const string& name)
	{
		if (m_events.find(name) == m_events.end()) {
			m_events[name] = vector<IObserver*>();
		}
	}

	void unregisterEvent(const string& name)
	{
	}

	void emit(const string& name, Event* event)
	{
		BK_ASSERT(event, "Event must not be null");
		for (IObserver* o: m_events[name]) {
			if (o->handleEvent(event)) {
				SAFE_DELETE(event);
				break;
			}
		}
		SAFE_DELETE(event);
	}

	void queue(Event* event)
	{
		m_queue.push_back(event);
	}

	void dequeue(const string& name)
	{
	}

	void tick()
	{
		if (!m_queue.empty()) {
			auto e = m_queue.front();
			emit(e->name(), e);
			m_queue.pop_front();
		}
	}

private:
	std::map<string, vector<IObserver*>> m_events;
	std::list<Event*> m_queue;
};

EventManager* EventManager::s_instance = nullptr;

EventManager&
EventManager::instance()
{
	if (s_instance == nullptr) {
		s_instance = new EventManager();
	}

	return *s_instance;
}

EventManager::EventManager() :
	m_impl(new EventManagerPrivate())
{
}

EventManager::~EventManager()
{
	SAFE_DELETE(m_impl);
}

void
EventManager::subscribe(const string& name, IObserver* observer)
{
	m_impl->subscribe(name, observer);
}

void
EventManager::unsubscribe(const string& name, IObserver* observer)
{
	m_impl->unsubscribe(name, observer);
}

void
EventManager::registerEvent(const string& name)
{
	m_impl->registerEvent(name);
}

void
EventManager::unregisterEvent(const string& name)
{
	m_impl->unregisterEvent(name);
}

void
EventManager::emit(const string& name, Event* event)
{
	m_impl->emit(name, event);
}

void
EventManager::queue(Event* event)
{
	m_impl->queue(event);
}

void
EventManager::dequeue(const string& name)
{
	m_impl->dequeue(name);
}

void
EventManager::tick()
{
	m_impl->tick();
}

}
