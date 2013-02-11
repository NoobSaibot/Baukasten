#ifndef ISHADER_H_CGG0R9RZ
#define ISHADER_H_CGG0R9RZ

#include "base.h"
#include "core/Managed"

/*!
 * \brief IShader class declaration.
 */
class IShader : public Managed {
public:
	virtual ShaderType type() const = 0;
	virtual int handler() const = 0;
};

typedef vector<IShader*> ShaderList;

#endif /* end of include guard: ISHADER_H_CGG0R9RZ */

