#ifndef GLOBAL_H_8PLKMLEZ
#define GLOBAL_H_8PLKMLEZ

#include <string>
#include <vector>

using namespace std;

#define BK_IMPL(X) class X##Private* m_impl; friend class X##Private
#define BK_STRINGIFY(X) #X

#define SAFE_DELETE(X) { if(X) { delete X; X = NULL; } }
#define SAFE_ARR_DELETE(X) { if(X && X != nullptr) { delete[] X; X = nullptr; }}

#endif /* end of include guard: GLOBAL_H_8PLKMLEZ */

