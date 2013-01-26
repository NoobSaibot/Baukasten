#ifndef TEXTURE_H_RIWRFHAD
#define TEXTURE_H_RIWRFHAD

#include "base.h"
#include "drawable.h"

class Bitmap;

/*!
 * \brief Texture class declaration.
 */
class Texture : public Drawable {
public:
	static Texture* fromFile(const string&);
	static Texture* fromBitmap(Bitmap*);

private:
	Texture(Bitmap&);
	virtual ~Texture();
};

#endif /* end of include guard: TEXTURE_H_RIWRFHAD */

