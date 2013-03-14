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

	explicit State(const State<T>& other) :
		IState(other.name()), m_state(other.m_state)
	{
		m_state->addRef();
	}

	virtual ~State()
	{
		m_state->release();
	}

	IState* clone() const
	{
		State<T>* t_state = new State<T>(name(), value());
		return t_state;
	}

	void setValue(const T& value)
	{
		m_state->setValue(value);
	}

	T value() const
	{
		return m_state->value();
	}

private:
	friend class Actor;
	StateWrapper<T>* m_state;
};

}

#endif /* end of include guard: STATE_H_AKMCYL2T */

