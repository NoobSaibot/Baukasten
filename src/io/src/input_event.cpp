#include "io/InputEvent"

#include "core/Debug"

namespace bk {

/*!
 * \brief InputEventPrivate class declaration.
 */
class InputEventPrivate {
public:
	InputEventPrivate(Key key) :
		m_key(key)
	{
		BK_DEBUG("key: " << (int)key << " esc: " << KEY_ESC);
	}

	~InputEventPrivate()
	{
	}

	Key key() const
	{
		return m_key;
	}

private:
	Key m_key;
};

InputEvent::InputEvent(const string& name, const f32 timeStamp, const Key key ) :
	Event(name, timeStamp), m_impl( new InputEventPrivate(key) )
{
}

InputEvent::~InputEvent()
{
	SAFE_DELETE(m_impl);
}

Key
InputEvent::key() const
{
	return m_impl->key();
}

}

