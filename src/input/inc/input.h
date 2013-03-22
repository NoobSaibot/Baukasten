#ifndef INPUT_H_ETONQS2B
#define INPUT_H_ETONQS2B

#include "core/Managed"
#include "input/Global"

namespace bk {

class IKeyboard;
class IMouse;

/*!
 * \brief Input class declaration.
 */
class Input : public Managed {
public:
	IKeyboard* keyboard() const;
	IMouse* mouse() const;

	static Input* createInput(const string&);

	virtual ~Input();

private:
	Input(const string&);
	BK_IMPL(Input);
};

} /* bk */

#endif /* end of include guard: INPUT_H_ETONQS2B */

