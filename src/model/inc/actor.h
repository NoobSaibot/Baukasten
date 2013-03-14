#ifndef ACTOR_H_DEFKVZDF
#define ACTOR_H_DEFKVZDF

#include "graphics/Global"
#include "core/Managed"

namespace bk {

class ActorType;
class IContext;
class IState;
class Model;

/*!
 * \brief Actor class declaration.
 */
class Actor : public Managed {
public:

	static Actor* create(const string&, Model*);

	Model* model() const;
	void setModel(Model*);

	Actor* parent() const;
	void setParent(Actor*);

	vector<Actor*> children() const;
	Actor* child(const string&) const;
	void addChild(Actor*);

	void setActorType(ActorType*);
	ActorType* actorType() const;

	void setContext(IContext*);
	IContext* context() const;

	void addState(IState*);
	IState* state(const string&);
	void removeState(const string&);

	void render();
	void update(const int);

	virtual ~Actor();

private:
	explicit Actor(const string&, Model*);

	BK_IMPL(Actor);
};

}

#endif /* end of include guard: ACTOR_H_DEFKVZDF */

