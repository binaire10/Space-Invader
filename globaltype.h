#ifndef GLOBALTYPE
#define GLOBALTYPE
#include <vector>
#include <string>
#include <cstdlib>
#include <list>

/**
 * @file globaltype.h
 * \brief Here some alias and struct to work with flux
 * @author (binaire) Alexandre Wery
 */

namespace binaire {

    /**
 * @typedef CVString
 * \brief CVString
 * IUT type
 */
    typedef std::vector <std::string> CVString;    // c'est le type de l'écran (l'espace, la matrice)

    /**
 * @typedef uint_t
 * \brief uint_t
 * it's a semantic type
 */
    typedef unsigned uint_t;
    /**
 * @typedef uchar
 * \brief uchar
 * it's a semantic type
 */
    typedef unsigned uchar;

    /**
 * @typedef CPosXY
 * \brief CPosXY
 * Object position
 */
    typedef std::pair<unsigned , unsigned> CPosXY;
}
#endif // GLOBALTYPE
