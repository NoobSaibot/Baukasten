#include "io/Event"

namespace bk {

class EventPrivate {
public:
	EventPrivate(float timeStamp, StreamFunc f) :
		m_timeStamp(timeStamp), m_streamFunc(f)
	{
	}

	~EventPrivate()
	{
	}

	float timeStamp() const
	{
		return m_timeStamp;
	}

	void serialize(std::ostream& stream) const
	{
		m_streamFunc(stream);
	}

private:
	float m_timeStamp;
	StreamFunc m_streamFunc;
};

Event::Event(const string& name, float timeStamp, StreamFunc f) :
	Identity(name, "Event"), m_impl(new EventPrivate(timeStamp, f))
{
}

Event::~Event()
{
	SAFE_DELETE(m_impl);
}

float
Event::timeStamp() const
{
	return m_impl->timeStamp();
}

void
Event::serialize(std::ostream& stream) const
{
	m_impl->serialize(stream);
}

} /* bk */
