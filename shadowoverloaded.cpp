#include "shadowoverloaded.h"

using namespace std;
namespace binaire
{
std::ostream &operator << (std::ostream &os, const __EscapeCmd &Mode)
{
    os << Mode.s_CODE;
    return os;
}

ostream &operator<<(ostream &os, const CCharColor &Val)
{
    os << Val.second.s_CODE << Val.first << Val.second.s_postCODE;
    return os;
}

bool operator ==(const CCharColor &PX, const char &Val)
{
    return PX.first == Val;
}

bool operator ==(const char &Val, const CCharColor &PX)
{
    return PX.first == Val;
}

bool operator !=(const CCharColor &PX, const char &Val)
{
    return PX.first != Val;
}

bool operator !=(const char &Val, const CCharColor &PX)
{
    return PX.first != Val;
}

bool operator ==(const __EscapeCmd &, const __EscapeCmd &)
{return true;}
}
