#include "shadowclass.h"
#include <string>

using namespace std;
using namespace binaire;

__EscapeCmd::__EscapeCmd(const string &Code) : s_CODE(Code)
{}

__EscapeCmd::__EscapeCmd(const char *Code) : __EscapeCmd(std::string(Code))
{}

bool __EscapeCmd::operator ==(const __EscapeCmd &Val)
{
    return Val.s_CODE==s_CODE && Val.s_postCODE==s_postCODE;
}
