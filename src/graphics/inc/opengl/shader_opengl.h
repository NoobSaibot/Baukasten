#ifndef SHADER_OPENGL_H_UDEPWQPA
#define SHADER_OPENGL_H_UDEPWQPA

#include "base.h"
#include "graphics/IShader"

/*!
 * \brief ShaderOpenGL class declaration.
 */
class ShaderOpenGL : public IShader {
public:
	virtual ~ShaderOpenGL();

	ShaderType type() const;
	int handler() const;

private:
	ShaderOpenGL(const string&, const string&, const ShaderType);
	friend class Shader;
	BK_PIMPL(ShaderOpenGL);
};

#endif /* end of include guard: SHADER_OPENGL_H_UDEPWQPA */

