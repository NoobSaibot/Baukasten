#ifndef ANIMATION_H_PDSNXOTR
#define ANIMATION_H_PDSNXOTR

#include "core/Global"
#include "core/Managed"

namespace bk {

/*!
 * \brief Animation class declaration.
 */
class Animation : public Managed {
public:
	struct Frame {
		Frame(float _x, float _y, float _width, float _height,
				unsigned int _duration, bool _final = false) :
			x(_x), y(_y), width(_width), height(_height), duration(_duration),
			final(_final)
		{
		}

		float x, y, width, height;
		int duration;
		bool final;
	};

	Animation(const string&, std::initializer_list<Frame>);
	virtual ~Animation();

	void update(const int);
	Frame frame() const;
	void reset();

private:
	BK_IMPL(Animation);
};

} /* bk */

#endif /* end of include guard: ANIMATION_H_PDSNXOTR */

