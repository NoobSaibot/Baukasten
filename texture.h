#ifndef TEXTURE_H_RIWRFHAD
#define TEXTURE_H_RIWRFHAD

#include "base.h"
#include "drawable.h"

class Bitmap;
class ITexture;

/*!
 * \brief Texture class declaration.
 */
class Texture {
public:
	static ITexture* fromFile(const string&);
	static ITexture* fromBitmap(Bitmap*);
};

#endif /* end of include guard: TEXTURE_H_RIWRFHAD */

