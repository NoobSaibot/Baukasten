#ifndef SHADER_OPENGL_H_UDEPWQPA
#define SHADER_OPENGL_H_UDEPWQPA

#include "../base.h"
#include "../ishader.h"

class ShaderOpenGLPrivate;

/*!
 * \brief ShaderOpenGL class declaration.
 */
class ShaderOpenGL : public IShader {
public:
	ShaderOpenGL(const string&, const IShader::Type);
	virtual ~ShaderOpenGL();

	IShader::Type type() const;
	int handler() const;

private:
	friend class ShaderOpenGLPrivate;
	ShaderOpenGLPrivate* m_impl;
};

#endif /* end of include guard: SHADER_OPENGL_H_UDEPWQPA */

