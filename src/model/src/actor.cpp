#include "model/Actor"

#include <map>

#include "graphics/Context"
#include "graphics/Graphics"
#include "graphics/IForm"
#include "input/Input"
#include "input/IKeyboard"
#include "model/Action"
#include "model/ActorType"
#include "model/State"

namespace bk {

typedef std::map<string, IState*> StateMap;

class ActorPrivate {
public:
	ActorPrivate(Actor *object, IForm* form) :
		m_actorType(nullptr), m_context(nullptr), m_object(object), m_form(form),
		m_input(nullptr)
	{
		m_eventHandler = [](Event* e) {
			return false;
		};
	}

	~ActorPrivate()
	{
		for ( Actor* a: m_children ) {
			a->release();
		}

		for ( auto s: m_states ) {
			s.second->release();
		}

		if (m_context) {
			m_context->release();
		}

		if (m_form) {
			m_form->release();
		}

		if (m_actorType) {
			m_actorType->release();
		}
	}

	void addChild(Actor* actor)
	{
		m_children.push_back(actor);
		actor->setParent(m_object);
	}

	vector<Actor*> children() const
	{
		return m_children;
	}

	void setParent(Actor* parent)
	{
		m_parent = parent;
	}

	Actor* parent()
	{
		return m_parent;
	}

	void setForm(IForm* form)
	{
		m_form = form;
	}

	IForm* form() const
	{
		return m_form;
	}

	void setContext(Context* context)
	{
		m_context = context;
		context->addRef();
	}

	Context* context() const
	{
		if (m_context) {
			return m_context;
		}

		if (m_parent) {
			return m_parent->context();
		}

		m_context = Graphics::createContext("context.auto");
		return m_context;
	}

	void setInput(Input* input)
	{
		m_input = input;
	}

	Input* input() const
	{
		Input *input = nullptr;

		if (m_input) {
			input = m_input;
		} else if (m_parent) {
			input = m_parent->input();
		}

		BK_ASSERT(input != nullptr, "Inputsource must be set.");
		return input;
	}

	void addState(IState* state)
	{
		m_states[state->name()] = state;
	}

	IState* state(const string& name)
	{
		IState* state = 0;

		auto it = m_states.find(name);
		if (it != m_states.end()) {
			state = it->second;
		}

		if (!state && m_actorType) {
			state = m_actorType->state(name);
			if (state) {
				state = state->clone();
				addState(state);
			}
		}

		BK_ASSERT(state, "No state with the given name found: " << name);
		return state;
	}

	void removeState(const string& name)
	{
		auto it = m_states.find(name);
		if ( it != m_states.end() ) {
			it->second->release();
			m_states.erase(it);
		}
	}

	void setActorType(ActorType* actorType)
	{
		m_actorType = actorType;
		actorType->addRef();
	}

	ActorType* actorType() const
	{
		return m_actorType;
	}

	void addAction(Action* action)
	{
		BK_ASSERT(action, "Action must not be null");
		BK_ASSERT(m_actions.find(action->name()) == m_actions.end(), "Action " << action->name() << " has already been added.");
		m_actions[action->name()] = action;
	}

	Action* action(const string& name)
	{
		BK_ASSERT(m_actions.find(name) != m_actions.end(), "Action " << name << " couldn't be found.");
		return m_actions[name];
	}

	void invokeAction(const string& name, vector<Actor*> targets)
	{
		auto it = m_actions.find(name);
		BK_ASSERT(it != m_actions.end(), "Action " << name << " couldn't be found.");
		BK_ASSERT(!targets.empty(), "Target Actors must be given.");
		auto action = it->second;

		action->setTargets(targets);
		m_invokedActions.push_back(action);
	}

	vector<Action*> invokedActions() const
	{
		return m_invokedActions;
	}

	void removeAction(const string& name)
	{
		auto it = m_actions.find(name);
		if ( it != m_actions.end() ) {
			it->second->release();
			m_actions.erase(it);
		}
	}

	void runActions()
	{
		for ( unsigned int i = 0; i < m_invokedActions.size(); ++i ) {
			auto a = m_invokedActions[i];
			if (a->run()) {
				m_invokedActions.erase(m_invokedActions.begin() + i);
			}
		}

		for ( Actor* a: m_children ) {
			a->runActions();
		}
	}

	void render()
	{
		if (m_form)
			m_form->render(context()->camera(), 1.0);

		for ( auto m : m_children ) {
			m->render();
		}
	}

	void update(const int timeDelta)
	{
		if (m_form) {
			m_form->update(timeDelta);
		}

		for ( auto m: m_children ) {
			m->update(timeDelta);
		}

		if (m_input) {
			m_input->update();
		}
	}

	bool handleEvent(Event* event)
	{
		return m_eventHandler(event);
	}

	void setEventHandler(HandlerFunc f)
	{
		m_eventHandler = f;
	}

private:
	vector<Actor*> m_children;
	Actor*   m_parent;
	ActorType* m_actorType;
	mutable Context* m_context;
	Actor*   m_object;
	IForm*   m_form;
	Input* m_input;
	std::map<string, IState*> m_states;
	std::map<string, Action*> m_actions;
	vector<Action*> m_invokedActions;
	HandlerFunc m_eventHandler;
};

Actor::Actor( const string& id, IForm* form ) :
	Managed(id, "Actor"), m_impl(new ActorPrivate(this, form))
{
}

Actor::~Actor()
{
	SAFE_DELETE( m_impl );
}

IForm*
Actor::form() const
{
	return m_impl->form();
}

void
Actor::setForm(IForm* form)
{
	m_impl->setForm(form);
}

void
Actor::setParent(Actor* parent)
{
	m_impl->setParent(parent);
}

Actor*
Actor::parent() const
{
	return m_impl->parent();
}

vector<Actor*>
Actor::children() const
{
	return m_impl->children();
}

void
Actor::addChild(Actor* child)
{
	m_impl->addChild(child);
}

void
Actor::setContext(Context* context)
{
	m_impl->setContext(context);
}

Context*
Actor::context() const
{
	return m_impl->context();
}

void
Actor::setInput(Input* input)
{
	m_impl->setInput(input);
}

Input*
Actor::input() const
{
	return m_impl->input();
}

void
Actor::addState(IState* state)
{
	m_impl->addState(state);
}

IState*
Actor::state(const string& name)
{
	return m_impl->state(name);
}

void
Actor::removeState(const string& name)
{
	m_impl->removeState(name);
}

void
Actor::setActorType(ActorType* actorType)
{
	m_impl->setActorType(actorType);
}

ActorType*
Actor::actorType() const
{
	return m_impl->actorType();
}

void
Actor::addAction(Action* action)
{
	m_impl->addAction(action);
}

Action*
Actor::action(const string& name)
{
	return m_impl->action(name);
}

void
Actor::invokeAction(const string& name)
{
	m_impl->invokeAction(name, { this });
}

void
Actor::invokeAction(const string& name, vector<Actor*> targets)
{
	m_impl->invokeAction(name, targets);
}

vector<Action*>
Actor::invokedActions() const
{
	return m_impl->invokedActions();
}

void
Actor::removeAction(const string& name)
{
	m_impl->removeAction(name);
}

void
Actor::render()
{
	m_impl->render();
}

void
Actor::update(const int timeDelta)
{
	m_impl->update(timeDelta);
}

void
Actor::runActions()
{
	m_impl->runActions();
}

bool
Actor::handleEvent(Event* event)
{
	return m_impl->handleEvent(event);
}

void
Actor::setEventHandler(HandlerFunc f)
{
	m_impl->setEventHandler(f);
}

}

