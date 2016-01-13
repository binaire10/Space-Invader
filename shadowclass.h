#pragma once
#include <string>

namespace binaire
{
    /**
     * @struct __EscapeCmd
     * \brief The __EscapeCmd struct
     * special stucture to make escape code Command.
     */
    struct __EscapeCmd
    {
        /**
         * \brief __EscapeCmd
         * Constructor
         * @param Code
         * Escape Sequence
         */
        __EscapeCmd(const std::string &Code);
        /**
         * \brief __EscapeCmd
         * Constructor
         * @param Code
         * Escape Code
         */
        __EscapeCmd(const char *Code);
        /**
         * \brief operator ==
         * Creat bool operator
         * @return
         */
        bool operator ==(const __EscapeCmd &);
        /**
         * @var s_CODE
         * \brief s_CODE
         * Code Escape
         */
         std::string s_CODE;
        /**
         * @var s_postCODE
         * \brief s_postCODE
         * Code Escape post flux
         */
         std::string s_postCODE;
    };
}
