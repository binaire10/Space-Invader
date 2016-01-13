#pragma once
#include <ostream>
#include "mytype.h"
#include "myscreentype.h"

namespace binaire
{
    /**
     * \brief operator <<
     * do comptible CCharColor with flux
     * @param os
     * @param Val
     * @return
     */
    std::ostream &operator << (std::ostream &os, const CCharColor &Val);
    /**
     * \brief operator <<
     * do comptible __EscapeCmd with flux
     * @param os
     * @param Mode
     * @return
     */
    std::ostream &operator << (std::ostream &os, const __EscapeCmd &Mode);

    /**
     * \brief operator ==
     * do compatible with char boolean
     * @return
     */
    bool operator ==(const CCharColor &, const char &);
    /**
     * \brief operator ==
     * do compatible with char boolean
     * @return
     */
    bool operator ==(const char &, const CCharColor &);

    /**
     * \brief operator !=
     * do compatible with char boolean
     * @return
     */
    bool operator !=(const CCharColor &, const char &);
    /**
     * \brief operator !=
     * do compatible with char boolean variable type CCharColor
     * @return
     */
    bool operator !=(const char &, const CCharColor &);

    /**
     * \brief operator ==
     * bool operator for __EscapeCmd
     * @return
     */
    bool operator ==(const __EscapeCmd &, const __EscapeCmd &);
}
