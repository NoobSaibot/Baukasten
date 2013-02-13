#ifndef TEXTURE_H_RIWRFHAD
#define TEXTURE_H_RIWRFHAD

#include "base.h"
#include "core/Identity"

class Bitmap;
class ITexture;

/*!
 * \brief Texture class declaration.
 */
class Texture {
public:
	static shared_ptr<ITexture> fromFile(const string&, const string&);
	static shared_ptr<ITexture> fromBitmap(const string&, const Bitmap&);
};

#endif /* end of include guard: TEXTURE_H_RIWRFHAD */

