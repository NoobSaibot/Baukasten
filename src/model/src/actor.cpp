#include "model/Actor"

#include <map>

#include "graphics/IContext"
#include "graphics/Graphics"
#include "graphics/Model"
#include "model/ActorType"
#include "model/State"

namespace bk {

typedef std::map<string, IState*> StateMap;

class ActorPrivate {
public:
	ActorPrivate(Actor *object, Model* model) :
		m_actorType(0), m_context(0), m_object(object), m_model(model)
	{
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

		if (m_model) {
			m_model->release();
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

	void setModel(Model* model)
	{
		m_model = model;
	}

	Model* model() const
	{
		return m_model;
	}

	void setContext(IContext* context)
	{
		m_context = context;
		context->addRef();
	}

	IContext* context() const
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
			state->setShared( true );
		}

		return state;
	}

	void removeState(const string& name)
	{
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

	void render()
	{
		context()->activate();

		if (m_model)
			m_model->render(context()->camera(), 1.0);

		for ( auto m: m_children ) {
			m->render();
		}
	}

	void update(const int timeDelta)
	{
		for ( auto m: m_children ) {
			m->update(timeDelta);
		}
	}

private:
	vector<Actor*> m_children;
	Actor*   m_parent;
	ActorType* m_actorType;
	mutable IContext* m_context;
	Actor*   m_object;
	Model*   m_model;
	std::map<string, IState*> m_states;
};

Actor::Actor( const string& id, Model* model ) :
	Managed(id, "Actor"), m_impl(new ActorPrivate(this, model))
{
}

Actor::~Actor()
{
	delete m_impl;
}

Actor*
Actor::create(const string& id, Model* model)
{
	return new Actor(id, model);
}

Model*
Actor::model() const
{
	return m_impl->model();
}

void
Actor::setModel(Model* model)
{
	m_impl->setModel(model);
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
Actor::setContext(IContext* context)
{
	m_impl->setContext(context);
}

IContext*
Actor::context() const
{
	return m_impl->context();
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
Actor::render()
{
	m_impl->render();
}

void
Actor::update(const int timeDelta)
{
	m_impl->update(timeDelta);
}

}

