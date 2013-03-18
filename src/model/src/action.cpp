#include "model/Action"

namespace bk {

class ActionPrivate {
public:
	ActionPrivate(Action* action, Actor* owner, Action::RunFunc run) :
		m_action(action), m_owner(owner), m_run(run)
	{
	}

	~ActionPrivate()
	{
	}

	Actor* owner() const
	{
		return m_owner;
	}

	bool run()
	{
		return m_run(m_action, m_targets);
	}

	vector<Actor*> targets() const
	{
		return m_targets;
	}

	void setTargets(const vector<Actor*> targets)
	{
		m_targets = targets;
	}

private:
	Action* m_action;
	Actor* m_owner;
	Action::RunFunc m_run;
	vector<Actor*> m_targets;
};

Action::Action(const string& name, Actor* owner, RunFunc run) :
	Managed(name, "Action"), m_impl(new ActionPrivate(this, owner, run))
{
}

Action::~Action()
{
	SAFE_DELETE( m_impl );
}

Actor*
Action::owner() const
{
	return m_impl->owner();
}

bool
Action::run()
{
	return m_impl->run();
}

vector<Actor*>
Action::targets() const
{
	return m_impl->targets();
}

void
Action::setTargets(const vector<Actor*> targets)
{
	m_impl->setTargets(targets);
}

} /* bk */
