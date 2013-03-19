#ifndef ISHADER_H_CGG0R9RZ
#define ISHADER_H_CGG0R9RZ

#include "core/Identity"
#include "graphics/Global"

namespace bk {

class IShader : public Identity {
public:
	explicit IShader(const string& name) : Identity(name, "Shader") {}

	virtual ShaderType type() const = 0;
	virtual int handler() const = 0;
};

}

#endif /* end of include guard: ISHADER_H_CGG0R9RZ */

