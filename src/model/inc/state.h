#ifndef STATE_H_AKMCYL2T
#define STATE_H_AKMCYL2T

#include "core/Assert"
#include "core/Managed"
#include "model/IState"

namespace bk {

template<class T>
class State : public IState {
public:
	template<class U>
	class StateWrapper : public Managed {
	public:
		StateWrapper(const string& name) :
			Managed(name, "StateWrapper"), m_value((void*)NULL)
		{
		}

		explicit StateWrapper(const string& name, const U& value) :
			Managed(name, "StateWrapper"), m_value(value)
		{
		}

		~StateWrapper()
		{
		}

		U value() const { return m_value; }
		void setValue(const U& value) { m_value = value; }
	private:
		U m_value;
	};

	explicit State(const string& name, const T& value) :
		IState(name), m_state(new StateWrapper<T>(name, value))
	{
	}

	virtual ~State()
	{
		m_state->release();
	}

	void setValue(const T& value)
	{
		if (m_shared) {
			m_state->release();
			m_state = new StateWrapper<T>(value);
			m_shared = false;
		}

		m_state->setValue(value);
	}

	T value() const
	{
		return m_state->value();
	}

	bool shared() const
	{
		return m_shared;
	}

private:
	friend class Actor;
	StateWrapper<T>* m_state;
	bool m_shared;
};

}

#endif /* end of include guard: STATE_H_AKMCYL2T */

