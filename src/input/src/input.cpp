#include "input/Input"

#include "input/KeyboardImpl"
#include "input/MouseImpl"

namespace bk {

class InputPrivate {
public:
	InputPrivate() :
		m_keyboard(new KeyboardImpl()), m_mouse(nullptr)
	{
	}

	~InputPrivate()
	{
	}

	IKeyboard* keyboard() const
	{
		return m_keyboard;
	}

	IMouse* mouse() const
	{
		return m_mouse;
	}

private:
	IKeyboard* m_keyboard;
	IMouse* m_mouse;
};

Input*
Input::createInput(const string& name)
{
	return new Input(name);
}

Input::Input(const string& name) :
	Managed(name), m_impl(new InputPrivate())
{
}

Input::~Input()
{
	SAFE_DELETE(m_impl);
}

IKeyboard*
Input::keyboard() const
{
	return m_impl->keyboard();
}

IMouse*
Input::mouse() const
{
	return m_impl->mouse();
}

} /* bk */
