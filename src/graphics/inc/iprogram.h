#ifndef IPROGRAM_H_R9MJXBZH
#define IPROGRAM_H_R9MJXBZH

#include "base.h"
#include "core/Identity"

namespace bk {

class IProgram : public Identity {
public:
	IProgram(const string& name) : Identity(name, "Program") {}

	virtual int attrib(const string&) const = 0;
	virtual void setAttrib(const string&, const mat4&) = 0;

	virtual int constant(const string&) const = 0;
	virtual void setConstant(const string&, const mat4&) = 0;

	virtual void activate() const = 0;
	virtual void deactivate() const = 0;
};

}

#endif /* end of include guard: IPROGRAM_H_R9MJXBZH */

