#ifndef ISHADER_H_CGG0R9RZ
#define ISHADER_H_CGG0R9RZ

#include "base.h"
#include "core/Identity"

namespace bk {

class IShader : public Identity {
public:
	IShader(const string& name) : Identity(name, "Shader") {}

	virtual ShaderType type() const = 0;
	virtual int handler() const = 0;
};

}

#endif /* end of include guard: ISHADER_H_CGG0R9RZ */

