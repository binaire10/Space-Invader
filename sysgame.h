#ifndef SYSGAME_H
#define SYSGAME_H
#include "globaltype.h"
#include "ostream"
#include <unistd.h>
#include "screen.h"


/**
 * @file sysgame.h
 * \brief all system of gesture game are here
 * @author (binaire) Alexandre Wery
 */
namespace binaire
{
    /**
     * @typedef funcManageMe
     * \brief funcManageMe
     * pointer function to an Manage Me type function
     */
    typedef void(funcManageMe)(CVFrame &Space, unsigned &Pos, bool &Lost);
    /**
     * @typedef funcManageInvader
     * \brief funcManageInvader
     * pointer function to an Manage Invader type function
     */
    typedef void(funcManageInvader)(CVFrame &Space, int &Increment, unsigned &CurrentLine, unsigned &Beg, bool &Win, bool &ToShoot);
    /**
     * \brief run
     * Main Game function
     * @return
     */
    bool run();
    /**
     * \brief write
     * function to made an rand speed output like typewriter
     * @param os
     * output stream
     * @param Data
     * String to print on screen
     * @param uTime
     * duration in microsecond
     */
    void write(std::ostream &os, const std::string &Data, const uint_t &uTime = 500000);
    /**
     * \brief centerText
     * function to center texte
     * @param Texte
     * Text to transform
     * @param size
     * size of line
     * @return
     */
    std::string centerText(const std::string &Texte, const uint_t &size);
    /**
     * @var AIme
     * \brief AIme
     * function pointer to an AI of manege me
     */
    extern funcManageMe *AIme;
    /**
     * @var AIinvader
     * \brief AIinvader
     * function pointer to an AI of manage invader
     */
    extern funcManageInvader *AIinvader;
}

#endif // SYSGAME_H
