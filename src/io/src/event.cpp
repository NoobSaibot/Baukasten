#include "io/Event"

namespace bk {

class EventPrivate {
public:
	EventPrivate(float timeStamp) :
		m_timeStamp(timeStamp), m_streamFunc(nullptr)
	{
	}

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
		if ( m_streamFunc != nullptr ) {
			m_streamFunc(stream);
		}
	}

	void setStreamFunction(StreamFunc f)
	{
		m_streamFunc = f;
	}

	StreamFunc streamFunction() const
	{
		return m_streamFunc;
	}

private:
	float m_timeStamp;
	StreamFunc m_streamFunc;
};

Event::Event(const string& name, float timeStamp) :
	Identity(name, "Event"), m_impl(new EventPrivate(timeStamp))
{
}

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

void
Event::setStreamFunction(StreamFunc func)
{
	m_impl->setStreamFunction(func);
}

StreamFunc
Event::streamFunction() const
{
	return m_impl->streamFunction();
}

} /* bk */
