#include "model/Model"

#include "graphics/Form"
#include "model/Action"
#include "model/Actor"
#include "model/ActorType"

namespace bk {

Action*
Model::createAction(const string& name, Actor* actor, RunFunc run)
{
	return new Action(name, actor, run);
}

Actor*
Model::createActor(const string& name, Form* form)
{
	return new Actor(name, form);
}

ActorType*
Model::createActorType(const string& name)
{
	return new ActorType(name);
}

} /* bk */
