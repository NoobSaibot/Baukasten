#ifndef FILESYSTEM_H_Q9APEMHS
#define FILESYSTEM_H_Q9APEMHS


#include "base.h"

/*!
 * \brief Filesystem class declaration.
 */
class Filesystem {
public:
	virtual ~Filesystem();
	static char* readAll( const string& path, int* size = 0 );
};

#endif /* end of include guard: FILESYSTEM_H_Q9APEMHS */

