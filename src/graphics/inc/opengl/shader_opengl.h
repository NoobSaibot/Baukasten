#ifndef SHADER_OPENGL_H_UDEPWQPA
#define SHADER_OPENGL_H_UDEPWQPA

#include "base.h"
#include "graphics/IShader"

namespace bk {

class ShaderOpenGL : public IShader {
public:
	virtual ~ShaderOpenGL();

	ShaderType type() const;
	int handler() const;

private:
	ShaderOpenGL(const string&, const string&, const ShaderType);
	friend class Graphics;
	BK_IMPL(ShaderOpenGL);
};

}

#endif /* end of include guard: SHADER_OPENGL_H_UDEPWQPA */

