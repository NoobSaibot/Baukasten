#ifndef SHADER_H_UEZJIHHF
#define SHADER_H_UEZJIHHF

#include "managed.h"

#include <string>

class Shader : public Managed {
public:
	static Shader* fromFile( const string&, const GLuint );
	static Shader* fromSource( const string&, const GLuint );

	GLuint type() const;

protected:
	Shader(const string&, const GLuint);
	Shader(const Shader& other);
	virtual ~Shader();

private:
	GLuint m_type;
};

#endif /* end of include guard: SHADER_H_UEZJIHHF */

