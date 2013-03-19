#include "io/Filesystem"

#include "core/Assert"

#include <sys/stat.h>
#include <fstream>

namespace bk {

bool
Filesystem::exists( const string& path )
{
	struct stat buf;
	if (stat(path.c_str(), &buf) != -1) {
		return true;
	}
	return false;
}

char*
Filesystem::readAll( const string& path, int* size )
{
	ifstream file(path.c_str(), ios::in|ios::binary|ios::ate);
	BK_ASSERT(file.is_open(), "File " << path << " couldn't be opened.");

	int _size = file.tellg();
	char* buffer = new char[_size + 1];
	file.seekg(0, ios::beg);
	file.read(buffer, _size);
	file.close();

	buffer[_size] = '\0';
	if ( size )
		*size = _size;
	return buffer;
}

}

