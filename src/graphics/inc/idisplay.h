#ifndef IDISPLAY_H_WJA7P5ZG
#define IDISPLAY_H_WJA7P5ZG

namespace bk {

class IDisplay {
public:
	virtual void clear() = 0;
	virtual void display() = 0;
	virtual void exit() = 0;
	virtual void init(const u16, const u16) = 0;
	virtual void setBackgroundColor(const f32, const f32, const f32) = 0;
	virtual u16  width() const = 0;
	virtual u16  height() const = 0;
};

}

#endif /* end of include guard: IDISPLAY_H_WJA7P5ZG */

