#ifndef ACTOR_TYPE_H_KLG2UIBJ
#define ACTOR_TYPE_H_KLG2UIBJ

#include "core/Managed"
#include "model/Global"

namespace bk {

class Action;
class IState;

/*!
 * \brief ActorType class declaration.
 */
class ActorType : public Managed {
public:
	explicit ActorType(const string&);
	virtual ~ActorType();

	void addState(IState*);
	IState* state(const string&) const;

	void addAction(Action*);
	Action* action(const string&) const;

	void setParent(ActorType*);
	ActorType* parent() const;

private:
	BK_IMPL(ActorType);
};

} /* bk */

#endif /* end of include guard: ACTOR_TYPE_H_KLG2UIBJ */

