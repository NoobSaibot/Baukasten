#include "input/inc/opengl/keyboard_opengl.h"

#include "core/Debug"
#include "io/Event"
#include "io/EventManager"

#include <GL/glfw.h>

#include <sstream>

#define EMIT_EVENT(CHAR) \
	if (glfwGetKey(CHAR)) {\
		EventManager::instance().emit(\
			"event.keyPressed", new Event("event.keyPressed", 0.0, [](std::ostream& s) {\
				s << CHAR;\
			})\
		);\
	}

namespace bk {

class KeyboardOpenGLPrivate {
public:
	KeyboardOpenGLPrivate()
	{
		EventManager::instance().registerEvent("event.keyPressed");
	}

	~KeyboardOpenGLPrivate()
	{
	}

	void update()
	{
		EMIT_EVENT('A');
		EMIT_EVENT('B');
		EMIT_EVENT('C');
		EMIT_EVENT('D');
		EMIT_EVENT('E');
		EMIT_EVENT('F');
		EMIT_EVENT('G');
		EMIT_EVENT('H');
		EMIT_EVENT('I');
		EMIT_EVENT('J');
		EMIT_EVENT('K');
		EMIT_EVENT('L');
		EMIT_EVENT('M');
		EMIT_EVENT('N');
		EMIT_EVENT('O');
		EMIT_EVENT('P');
		EMIT_EVENT('Q');
		EMIT_EVENT('R');
		EMIT_EVENT('S');
		EMIT_EVENT('T');
		EMIT_EVENT('U');
		EMIT_EVENT('V');
		EMIT_EVENT('W');
		EMIT_EVENT('X');
		EMIT_EVENT('Y');
		EMIT_EVENT('Z');
		EMIT_EVENT(GLFW_KEY_ESC);
	}
};

KeyboardOpenGL::KeyboardOpenGL() :
	m_impl(new KeyboardOpenGLPrivate())
{
}

KeyboardOpenGL::~KeyboardOpenGL()
{
	SAFE_DELETE(m_impl);
}

void
KeyboardOpenGL::update()
{
	m_impl->update();
}

} /* bk */
