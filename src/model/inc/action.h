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
	typedef std::function<bool ( const Action* )> DoneFunc;
	typedef std::function<void ( Action*, vector<Actor*> )> RunFunc;

	Action(const string&, Actor*, RunFunc);
	virtual ~Action();

	bool done() const;
	void run();
	Actor* owner() const;
	vector<Actor*> targets() const;
	void setTargets(const vector<Actor*>);

private:
	BK_IMPL(Action);
};

} /* bk */

#endif /* end of include guard: ACTION_H_VF2CZWNP */

