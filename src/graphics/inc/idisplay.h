#ifndef IDISPLAY_H_WJA7P5ZG
#define IDISPLAY_H_WJA7P5ZG

namespace bk {

class IDisplay {
public:
	virtual void clear() = 0;
	virtual void display() = 0;
	virtual void init() = 0;
	virtual void setBackgroundColor(const float, const float, const float) = 0;
};

}

#endif /* end of include guard: IDISPLAY_H_WJA7P5ZG */

