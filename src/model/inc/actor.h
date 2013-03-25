#ifndef ACTOR_H_DEFKVZDF
#define ACTOR_H_DEFKVZDF

#include "model/Global"
#include "core/Managed"
#include "io/IObserver"

namespace bk {

class Action;
class ActorType;
class Form;
class IContext;
class Event;
class IState;
class Input;

/*!
 * \brief Actor class declaration.
 */
class Actor : public Managed, public IObserver {
public:
	Form* form() const;
	void setForm(Form*);

	Actor* parent() const;
	void setParent(Actor*);

	vector<Actor*> children() const;
	Actor* child(const string&) const;
	void addChild(Actor*);

	void setActorType(ActorType*);
	ActorType* actorType() const;

	void setContext(IContext*);
	IContext* context() const;

	void setInput(Input*);
	Input* input() const;

	void addState(IState*);
	IState* state(const string&);
	void removeState(const string&);

	void addAction(Action*);
	Action* action(const string&);
	void invokeAction(const string&);
	void invokeAction(const string&, vector<Actor*>);
	vector<Action*> invokedActions() const;
	void removeAction(const string&);

	void render();
	void update(const int);
	void runActions();

	bool handleEvent(Event*) override;
	void setEventHandler(HandlerFunc);

	virtual ~Actor();

private:
	friend class Model;
	Actor(const string&, Form*);
	BK_IMPL(Actor);
};

}

#endif /* end of include guard: ACTOR_H_DEFKVZDF */

