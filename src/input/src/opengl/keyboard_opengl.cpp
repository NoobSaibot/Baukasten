#include "input/inc/opengl/keyboard_opengl.h"

#include "core/Debug"
#include "io/Event"
#include "io/EventManager"
#include "io/InputEvent"

#include <GL/glfw.h>

#include <sstream>

namespace {
static bk::Key _bk_toKey(u32 key)
{
	switch ( key ) {
	case GLFW_KEY_ESC: return bk::KEY_ESC;
	}
	return bk::Key( key );
}
}

#define EMIT_EVENT(CHAR) \
	if (glfwGetKey(CHAR)) {\
		EventManager::instance().emit(\
			"event.keyPressed", new InputEvent("event.keyPressed", 0.0, _bk_toKey( CHAR ) )\
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
		for ( u32 i = 32; i < 265; ++i ) {
			EMIT_EVENT(i);
		}
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
