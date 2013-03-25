#ifndef GLOBAL_H_ZQZMTLT6
#define GLOBAL_H_ZQZMTLT6

#include "core/Global"

#include <memory>

namespace bk {

class Action;
class Actor;
class Event;

typedef std::function<bool ( Action*, vector<Actor*> )> RunFunc;
typedef std::function<bool ( Event* )> HandlerFunc;

}

#endif /* end of include guard: GLOBAL_H_ZQZMTLT6 */

