#include "graphics/Animation"

#include "core/Debug"

namespace bk {

class AnimationPrivate {
public:
	AnimationPrivate(initializer_list<Animation::Frame> frames) :
		m_frames(frames), m_currFrame(0), m_counter(0)
	{
	}

	~AnimationPrivate()
	{
	}

	void update(int timeDelta)
	{
		Animation::Frame frame = m_frames[m_currFrame];

		if (m_counter++ >= frame.duration) {
			if (!frame.final) {
				m_currFrame = (m_currFrame + 1) % m_frames.size();
				m_counter = 0;
			}
		}
	}

	Animation::Frame frame() const
	{
		return m_frames[m_currFrame];
	}

	void reset()
	{
		m_currFrame = 0;
		m_counter = 0;
	}

private:
	vector<Animation::Frame> m_frames;
	int m_currFrame;
	int m_counter;
};

Animation::Animation(const string& name, initializer_list<Animation::Frame> frames) :
	Managed(name, "Animation"), m_impl(new AnimationPrivate(frames))
{
}

Animation::~Animation()
{
	SAFE_DELETE(m_impl);
}

void
Animation::update(const int timeDelta)
{
	m_impl->update(timeDelta);
}

Animation::Frame
Animation::frame() const
{
	return m_impl->frame();
}

void
Animation::reset()
{
	m_impl->reset();
}

} /* bk */
