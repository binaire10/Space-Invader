#pragma once
#include <string>
#include <utility>
#include "myconst.h"
#include "mytype.h"
#include "myscreentype.h"

namespace binaire
{
    /**
     * \brief setColor
     * creat escape Commande from KColor and KbColor
     * @param coul
     * Texte Color
     * @param back
     * BackGround Color
     * @return
     * escape structure
     */
    inline __EscapeCmd setColor(const std::string &coul, const std::string &back = "0")
    {
        return "\033["+back+";"+coul+"m";
    }

    /**
     * \brief creatPix
     * Creat an CCharColor with value and color
     * @param Value
     * @param col
     * @return
     */
    inline CCharColor creatPix(const char &Value, const std::string &col)
    {
        if(col.size() != 0)
            return std::make_pair(Value, setColor(col));
        else
            return std::make_pair(Value, col);
    }

}
