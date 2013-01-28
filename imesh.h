#ifndef IMESH_H_W4FDKTY7
#define IMESH_H_W4FDKTY7

#include "base.h"

class VertexFormat;

/*!
 * \brief IMesh class declaration.
 */
class IMesh {
public:
	enum UsageHint {
		DYNAMIC, STATIC, STREAM
	};

	virtual void init(const float*, const UsageHint, const VertexFormat, const int) = 0;
	virtual VertexFormat format() const = 0;
	virtual int count() const = 0;
	virtual void activate() const = 0;
	virtual void deactivate() const = 0;
};

#endif /* end of include guard: IMESH_H_W4FDKTY7 */

