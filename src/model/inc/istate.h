#ifndef ISTATE_H_YJ5SOTFY
#define ISTATE_H_YJ5SOTFY

#include "core/Managed"
#include "model/Global"

namespace bk {

/*!
 * \brief IState class declaration.
 */
class IState : public Managed {
public:
	IState(const string& name) : Managed(name, "IState")
	{
	}

	virtual IState* clone() const = 0;
};

} /* bk */

#endif /* end of include guard: ISTATE_H_YJ5SOTFY */

