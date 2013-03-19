#include "model/ActorType"

#include <map>

#include "model/IState"

namespace bk {

class ActorTypePrivate {
public:
	ActorTypePrivate() : m_parent(0)
	{
	}

	void addState(IState* state)
	{
		m_states[state->name()] = state;
	}

	IState* state(const string& name) const
	{
		IState* state = 0;

		auto it = m_states.find(name);
		if ( it != m_states.end() )
			state = it->second;
		if ( !state && m_parent )
			state = m_parent->state(name);

		return state;
	}

	void addAction(Action* action)
	{
		// TODO implementieren
	}

	Action* action(const string& name) const
	{
		// TODO implementieren
		//return m_actions[name];
	}

private:
	ActorType* m_parent;
	std::map<string, IState*> m_states;
	std::map<string, Action*> m_actions;
};

ActorType::ActorType(const string& name) :
	Managed(name, "ActorType"), m_impl(new ActorTypePrivate())
{
}

ActorType::~ActorType()
{
	SAFE_DELETE(m_impl);
}

void
ActorType::addState(IState* state)
{
	m_impl->addState(state);
}

IState*
ActorType::state(const string& name) const
{
	return m_impl->state(name);
}

void
ActorType::addAction(Action* action)
{
	m_impl->addAction(action);
}

Action*
ActorType::action(const string& name) const
{
	return m_impl->action(name);
}

} /* bk */
