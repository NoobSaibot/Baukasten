#include "model/Action"

namespace bk {

class ActionPrivate {
public:
	ActionPrivate(Action* action, Actor* owner, Action::RunFunc run) :
		m_action(action), m_owner(owner), m_run(run), m_done(0)
	{
	}

	~ActionPrivate()
	{
	}

	Actor* owner() const
	{
		return m_owner;
	}

	void run()
	{
		m_run(m_action, m_targets);
	}

	bool done() const
	{
		if (!m_done) {
			return true;
		}
		return m_done(m_action);
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
	Action::DoneFunc m_done;
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
Action::done() const
{
	return m_impl->done();
}

void
Action::run()
{
	m_impl->run();
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
