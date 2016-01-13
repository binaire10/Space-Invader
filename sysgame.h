#pragma once
#include <ostream>
#include <unistd.h>
#include "mytype.h"
#include "myscreentype.h"


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
 * @file sysgame.h
 * \brief all system of gesture game are here
 * @author (binaire) Alexandre Wery
 */
namespace binaire
{
    /**
     * \brief run
     * Main Game function
     * @return
     */
    bool run();

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
