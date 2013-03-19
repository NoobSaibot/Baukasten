#ifndef ACTION_H_VF2CZWNP
#define ACTION_H_VF2CZWNP

#include "core/Managed"
#include "model/Global"

#include <algorithm>

namespace bk {

class Actor;

/*!
 * \brief Action class declaration.
 */
class Action : public Managed {
public:
	virtual ~Action();

	bool run();
	Actor* owner() const;
	vector<Actor*> targets() const;
	void setTargets(const vector<Actor*>);

private:
	friend class Model;
	Action(const string&, Actor*, RunFunc);
	BK_IMPL(Action);
};

} /* bk */

#endif /* end of include guard: ACTION_H_VF2CZWNP */

