#ifndef ASSERT_OPENGL_H_A9VNLXP7
#define ASSERT_OPENGL_H_A9VNLXP7

#ifdef NDEBUG
#define BK_GL_ASSERT( X ) X
#else
#define BK_GL_ASSERT( X ) do \
	{\
		X;\
		GLenum __gl_error_code = glGetError();\
		BK_ASSERT(__gl_error_code == GL_NO_ERROR, "");\
	} while(0)
#endif

#endif /* end of include guard: ASSERT_OPENGL_H_A9VNLXP7 */

