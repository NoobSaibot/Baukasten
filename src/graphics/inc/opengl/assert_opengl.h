#ifndef ASSERT_OPENGL_H_A9VNLXP7
#define ASSERT_OPENGL_H_A9VNLXP7

#include "core/Assert"

#ifdef NDEBUG
#define BK_GL_ASSERT( X ) X
#else
static void _bk_glCheck(const char* file, unsigned int line, GLenum errCode)
{
	if (errCode != GL_NO_ERROR)
	{
		std::string fileString(file);
		std::string error = "unknown error";
		std::string description  = "no description";

		switch (errCode) {
		case GL_INVALID_ENUM : {
			error = "GL_INVALID_ENUM";
			description = "an unacceptable value has been specified for an enumerated argument";
			break;
		}

		case GL_INVALID_VALUE : {
			error = "GL_INVALID_VALUE";
			description = "a numeric argument is out of range";
			break;
		}

		case GL_INVALID_OPERATION : {
			error = "GL_INVALID_OPERATION";
			description = "the specified operation is not allowed in the current state";
			break;
		}

		case GL_STACK_OVERFLOW : {
			error = "GL_STACK_OVERFLOW";
			description = "this command would cause a stack overflow";
			break;
		}

		case GL_STACK_UNDERFLOW : {
			error = "GL_STACK_UNDERFLOW";
			description = "this command would cause a stack underflow";
			break;
		}

		case GL_OUT_OF_MEMORY : {
			error = "GL_OUT_OF_MEMORY";
			description = "there is not enough memory left to execute the command";
			break;
		}

		case GL_INVALID_FRAMEBUFFER_OPERATION_EXT : {
			error = "GL_INVALID_FRAMEBUFFER_OPERATION_EXT";
			description = "the object bound to FRAMEBUFFER_BINDING_EXT is not \"framebuffer complete\"";
			break;
		}
		}

		BK_ERROR( "An internal OpenGL call failed in "
			<< fileString.substr(fileString.find_last_of("\\/") + 1) << " (" << line << ") : "
			<< error << ", " << description );
		BK_ABORT();
	}
}

#define BK_GL_ASSERT( X ) do \
{\
	X;\
	GLenum __gl_error_code = glGetError();\
	_bk_glCheck(__FILE__, __LINE__, __gl_error_code);\
} while(0)
#endif

#endif /* end of include guard: ASSERT_OPENGL_H_A9VNLXP7 */

