#ifndef FILESYSTEM_H_Q9APEMHS
#define FILESYSTEM_H_Q9APEMHS

#include "core/Global"

namespace bk {

/*!
 * \brief Filesystem class declaration.
 */
class Filesystem {
public:
	virtual ~Filesystem();

	static bool  exists( const string& );
	static char* readAll( const string& path, int* size = 0 );
};

} /* bk */

#endif /* end of include guard: FILESYSTEM_H_Q9APEMHS */

