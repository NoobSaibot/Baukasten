#ifndef DEBUG_H_G18WJCD2
#define DEBUG_H_G18WJCD2

#ifdef NDEBUG

#define BK_ASSERT( X )
#define BK_GL_ASSERT( X ) X
#define BK_DEBUG( X )
#define BK_PRINT( X )
#define BK_ERROR( X )

#else

enum _bk_debug_verbosity {
	DEBUG,
	INFO,
	WARN,
	CRITICAL
};

inline static void
_bk_debug_print( const string &msg, _bk_debug_verbosity v )
{
	cout << msg;
}

#define BK_DEBUG_PRINT( X, LEVEL ) {\
	std::stringstream _bk_debug_string; \
	_bk_debug_string << __FILE__ << " " << __LINE__ << ": " << X << std::endl; \
	_bk_debug_print( _bk_debug_string.str(), LEVEL ); \
}
#define BK_DEBUG( X ) BK_DEBUG_PRINT( X, DEBUG )

#define BK_PRINT( X ) std::cout << X << std::endl;
#define BK_ERROR( X ) { std::cerr << __FILE__ << " " << __LINE__ \
	<< ": " << X << std::endl; abort(); }
#define BK_ASSERT(X) assert(X)
#define BK_GL_ASSERT( X ) do \
	{\
		X;\
		GLenum __gl_error_code = glGetError();\
		BK_ASSERT(__gl_error_code == GL_NO_ERROR);\
	} while(0)

#endif

#endif /* end of include guard: DEBUG_H_G18WJCD2 */

