#ifndef DEBUG_H_G18WJCD2
#define DEBUG_H_G18WJCD2

#include "core/Global"

#ifdef NDEBUG

#define BK_DEBUG( X )
#define BK_PRINT( X )
#define BK_ERROR( X )

#else

#include <iostream>
#include <sstream>

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
#endif

#endif /* end of include guard: DEBUG_H_G18WJCD2 */

