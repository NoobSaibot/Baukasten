#ifndef MODEL_H_MOUPJAJH
#define MODEL_H_MOUPJAJH

#include "model/Global"
#include "model/State"

namespace bk {

class Action;
class Actor;
class ActorType;
class IForm;
class IState;

/*!
 * \brief Model class declaration.
 */
class Model {
public:
	static Action*       createAction(const string&, Actor*, RunFunc);
	static Actor*        createActor(const string&, IForm*);
	static ActorType*    createActorType(const string&);
	template<class T>
	static IState*       createState(const string& name, T value)
	{
		return new State<T>(name, value);
	}
};

} /* bk */

#endif /* end of include guard: MODEL_H_MOUPJAJH */

