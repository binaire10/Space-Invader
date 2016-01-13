#pragma once
#include <array>
#include "mytype.h"
#include "myconst.h"
#include "shadowoverloaded.h"


/**
 * @file gameengine.h
 * \brief Here game engine
 * @author (binaire) Alexandre Wery
 */
namespace binaire
{

    // new system better
    /**
     * \brief InitSpace
     * Initialize an Frame of screen for game context
     * @param[out] GameFrame
     * Screen buffer Frame
     */
    void initSpace (CVFrame &GameFrame);


    /**
     * \brief manageInvader
     * control Invader
     * @param[in, out] Space
     * Screen buffer
     * @param Increment
     * tell where invader go
     * @param[in,out] CurrentLine
     * tell line position of invader
     * @param[in,out] Beg
     * tell colone of invader
     * @param[out] Win
     * tell if player win
     * @param[in,out] ToShoot
     * tell if invader can fire
     */
    void manageInvader(CVFrame &Space, int &Increment, unsigned &CurrentLine, unsigned &Beg, bool &Win, bool &ToShoot);

    /**
     * \brief manageMe
     * Control the player
     * @param[in,out] Space
     * it's frame of buffer screen
     * @param[in,out] Pos
     * tell the colone of player
     * @param[out] Lost
     * tell if player lost
     */
    void manageMe(CVFrame &Space, unsigned &Pos, bool &Lost);

    /**
     * \brief Remove
     * function can be reset line
     * @param[in,out] GameFrame
     * frame of screen buffer
     * @param[in] Line
     * line position to be clear
     */
    void remove(CVFrame &GameFrame, unsigned Line);

    /**
     * \brief InitSpace
     * initilize the space of screen buffer
     * @param GameFrame
     * screen buffer
     */
    void initSpace (CVSurface &GameFrame);

    /**
     * \brief ProjectileMoveTo
     * can move projectile
     * @param From
     * projectile position
     * @param To
     * target position
     * @param Target
     * Projectile target
     * @return
     */
    bool projectileMoveTo(CCharColor &From, CCharColor &To, const char &Target);

    /**
     * \brief ManageInvader
     * AI of invader
     * @param[in, out] Space
     * Screen buffer
     * @param[in, out] Increment
     * tell where invader go
     * @param[in,out] CurrentLine
     * tell line position of invader
     * @param[in,out] Beg
     * tell colone of invader
     * @param[out] Win
     * tell if player win
     * @param[in,out] ToShoot
     * tell if invader can fire
     */
    void manageInvader(CVSurface &Space, int &Increment, unsigned &CurrentLine, unsigned &Beg, bool &Win, bool &ToShoot);

    /**
     * \brief ManageMe
     * AI of Player
     * @param[in,out] Space
     * it's frame of buffer screen
     * @param[in,out] Pos
     * tell the colone of player
     * @param[out] Lost
     * tell if player lost
     */
    void manageMe(CVSurface &Space, unsigned &Pos, bool &Lost);

    /**
     * \brief Remove
     * function can be reset line
     * @param[in,out] GameFrame
     * frame of screen buffer
     * @param[in] Line
     * line position to be clear
     */
    void remove(CVSurface &GameFrame, unsigned Line);

    /**
     * \brief recomputeFrame
     * game physic work
     * @param[out, in] GameFrame
     * Screen buffer Frame
     * @param[out] Win
     * tell if player win
     * @param[out] Lost
     * tell if player lost
     */
    template<typename Space>
    void recomputeFrame(Space &GameFrame, bool &Win, bool &Lost)
    {
        auto &FirstLine = GameFrame[0];
        auto &LastLine = GameFrame[GameFrame.size()-1];
        for(uint_t j(0) ; j<FirstLine.size() ; ++j)
        {
            if(FirstLine[j] == KTorpedo)
                FirstLine[j] = KPxEmpty;
        }

        for(uint_t j(0) ; j<LastLine.size() ; ++j)
        {
            if(LastLine[j] == KMissile)
                LastLine[j] = KPxEmpty;
        }

        for(uint_t i(1), z(GameFrame.size()-1) ; i<GameFrame.size() ; ++i, --z)
        {
            for(uint_t j(0) ; j<GameFrame[i].size() ; ++j)
            {
                if(GameFrame[i][j] == KTorpedo)
                {
                    if(projectileMoveTo(GameFrame[i][j], GameFrame[i-1][j], KInsideInvader))
                    {
                        Win = true;
                        remove(GameFrame, i-1);
                    }
                }
                else if(GameFrame[z][j] == KMissile)
                {
                    if(projectileMoveTo(GameFrame[z][j], GameFrame[z+1][j], KInsideMe))
                    {
                        Lost = true;
                        remove(GameFrame, i+1);
                    }
                }

            }
        }
    }
}
