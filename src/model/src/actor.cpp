#include "model/Actor"

#include "graphics/Context"
#include "graphics/Model"

namespace bk {

class ActorPrivate {
public:
	ActorPrivate(Model* model) :
		m_context(0), m_model(model)
	{
	}

	~ActorPrivate()
	{
	}

	void addChild(Actor* actor)
	{
		m_children.push_back(actor);
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

	void setContext(Context* context)
	{
		m_context = context;
	}

	Context* context() const
	{
		if (m_context) {
			return m_context;
		}

		if (m_parent) {
			return m_parent->context();
		}

		return Context::create();
	}

	void render()
	{
		if (m_model)
			m_model->render(context()->camera(), 1.0);

		for ( auto m: m_children ) {
			m->render();
		}
	}

	void update(const int timeDelta)
	{
	}

private:
	vector<Actor*> m_children;
	Actor*   m_parent;
	Context* m_context;
	Model*   m_model;
};

Actor::Actor( const string& id, Model* model ) :
	Identity(id), m_impl(new ActorPrivate(model))
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
	child->setParent(this);
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

