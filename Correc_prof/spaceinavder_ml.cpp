/**
 * \file      SpacInvadersML.cpp
 *
 * \author    Marc Laporte
 *
 * \date      28/10/2015
 *
 * \note      Last modification 19/11/2015
 *
 * \brief     Essais pour l'implémentation de space invaders
 *
 */

#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>
#include <utility>    // max()
#include "MyConst_ML.h"
#include "MyType_ML.h"

#define classdef typedef

using namespace std;

namespace SpaceInvaderML
{

    void Colour (const string & Coul)
    {
        cout << "\033[" << Coul <<"m";

    }// Colour()

    void ClearScreen ()
    {
        cout << "\033[H\033[2J";

    } //ClearScreen()

    void GotoXY (unsigned X, unsigned Y)
    {
        cout << "\033[" << Y << ';' << X << "H";

    } // gotoxy()

    void DownShift (CVString & Space, Size_t CurrentLine)
    {
        for (Size_t i (CurrentLine); i > 0; --i)
            Space [i] = Space [i - 1];
        Space [0] = KEmptyLine;

    } // DownShift()

    bool IsDead (const CVString & Space, Size_t Line, Size_t Column,
                 char Who)
    {
        return Space [Line][Column] != Who &&
               (Space [Line][Column] == KInsideInvader ||
                Space [Line][Column] == KInsideMe);

    } // IsDead()

    bool Shoot (CVString & Space, Size_t Line, Size_t Middle,
                char Projectile, char Who)
    {
        if (IsDead (Space, Line, Middle, Who))
        {
            Space [Line] = KEmptyLine;
            return true;
        }
        Space [Line][Middle] =
                KEmpty == Space [Line][Middle] ? Projectile : KEmpty;
        return false;

    } // Shoot()

    bool ManageInvader (int & Increment, Size_t & CurrentLine,
                        Size_t & Beg, bool & ToShoot,
                        bool & Win, CVString & Space)
    {
        if ((Increment > 0 &&
               (Beg + KInvadersSize == KSizeLine ||
                Space [CurrentLine][Beg + KInvadersSize] != KEmpty))
           ||
            (Increment < 0 &&
               (Beg  == 0 ||
                Space [CurrentLine][Beg - 1] != KEmpty)))
        {
            ++CurrentLine;
            for (Size_t j (Beg); j < Beg + KInvadersSize; ++j)
            {
                if (KTorpedo == Space [CurrentLine][j])
                {
                    Win = true;
                    Space [CurrentLine] = KEmptyLine;
                    return false;
                }
            }

            Increment *= -1;
            DownShift (Space, CurrentLine);
            if (Space.size () - 1 <= CurrentLine)
                return true;
        }
        else
        {
            string ToShift (Space [CurrentLine].
                                  substr (Increment > 0 ? 0 : 1,
                                          KSizeLine - 1));
            Space [CurrentLine] = (Increment > 0) ? ' ' + ToShift
                                  : ToShift + ' ';
        }
        Beg +=Increment;
        ToShoot = ! ToShoot;
        if (ToShoot)
        {
            return Shoot (Space, CurrentLine + 1,
                          Beg + KInvadersMiddle, KMissile, KInsideInvader);
        }

        return false;

    } // ManageInvaders()

    void Remove (CVString & Space, Size_t Line, Size_t Column)
    {
        char Form = Space [Line][Column];
        for (Size_t j (Column); j < KSizeLine &&
                                Space [Line][j] == Form; ++j)
            Space [Line][j] = KEmpty;
        for (Size_t j (Column); j-- > 0 &&
                                Space [Line][j] == Form; )
            Space [Line][j] = KEmpty;

    } // Remove()

    void RecomputeSpace (CVString & Space, bool & Win, bool & Lost)
    {
        for (Size_t i (0); i < KSizeSpace; ++i)
        {
            for (Size_t j (0); j < KSizeLine; ++j)
            {
                if (KTorpedo == Space [i][j])
                {
                    if (i != 0)
                    {
                        if (KInsideInvader == Space [i - 1][j])
                        {
                            Remove (Space, i - 1, j);
                            Win = true;
                        }
                        else if (KMissile == Space [i - 1][j])
                        {
                            Space [i - 1][j] = KEmpty;
                        }
                        else
                        {
                            Space [i - 1][j] = KTorpedo;
                        }
                        Space [i][j]     = KEmpty;
                    }
                    else
                    {
                        Space [i][j] = KEmpty;
                    }
                }
                else if (KMissile == Space [i][j])
                {
                    /* le probleme est de ne pas faire avancer le missile de plus d'un */
                    if (i != KSizeSpace - 1)
                    {
                        if (KInsideMe == Space [i + 1][j])
                        {
                            Remove (Space, i + 1, j);
                            Lost = true;
                            Space [i][j]     = KEmpty;
                        }
                        else if (KTorpedo == Space [i + 1][j])
                        {
                            Space [i + 1][j] = KEmpty;
                            Space [i][j]     = KEmpty;
                        }
                        else
                        {
                            if (i > 0 && KMissile == Space[i - 1][j])
                            {
                                Space [i - 1][j] = KEmpty;
                            }
                            else
                            {
                                Space [i + 1][j] = KMissile;
                            }
                        }
                    }
                    else if (KMissile == Space [i - 1][j])
                    {
                        Space [i - 1][j] = KEmpty;
                    }
                    else
                    {
                        Space [i][j] = KEmpty;
                    }
                }

            }
        }
    } // RecomputeSpace()

    void DisplaySpace (const CVString & Space)
    {
        ClearScreen ();
        for (string Line : Space)
        {
            cout << Line.size ();
            for (unsigned Col (0); Col < Line.size (); ++Col)
            {
                switch (Line [Col])
                {
                  case KInsideMe :
                  case KTorpedo  :
                    Colour (KYellow);
                    break;
                  case KInsideInvader :
                  case KMissile       :
                    Colour (KGreen);
                    break;
                }
                cout << Line [Col];

                Colour (KReset);
            }
            cout << Line.size ();
            cout << endl;
        }

    } // DisplaySpace()

    bool ManageMe (CVString & Space, Size_t & Pos, bool & Lost)
    {
        char C;
        cin >> C;

        Size_t Line = Space.size () - 1;
        string NewLastLine = Space [Line];
        switch (C)
        {
          case KLeft    :
            if (Pos > 0)
            {
                --Pos;
                if (IsDead (Space, Line, Pos, KInsideMe))
                {
                    NewLastLine = KEmptyLine;
                    Lost = true;
                }
                else
                {
                    NewLastLine = Space [Line].substr (0, Pos) +
                                  Space [Line].substr (Pos + 1) + ' ';
                }
            }
            break;
          case KRight   :
            if (Pos < KSizeLine - 1)
            {
                ++Pos;
                if (IsDead (Space, Line, Pos, KInsideMe))
                {
                    NewLastLine = KEmptyLine;
                    Lost = true;
                }
                else
                {
                    NewLastLine = Space [Line].substr (0, Pos - 1) + ' ' +
                                  Space [Line].substr (Pos - 1,
                                                        KSizeLine - Pos);
                }
            }
            break;
          case KShoot :
            return Shoot (Space, Line - 1, Pos, KTorpedo, KInsideMe);
        }
        Space [Line] = NewLastLine;

        return false;

    } // ManageMe()

    void SpaceInvaders (void)
    {
        CVString Space (KSizeSpace, KEmptyLine);

        //  Initialisation of Space
        Space [0] = KEmptyLine.substr (0, KBegInvader) +
                    KInvadersForm +
                    KEmptyLine.substr (0,
                                       KSizeLine - KBegInvader
                                                 - KInvadersSize);
        Space [Space.size () - 1] = KEmptyLine.substr (0, KBegMe) + KMyForm +
                                    KEmptyLine.substr
                                            (0, KSizeLine - KBegMe - KMySize);

        int Direction = 1;
        Size_t CurrentLine (0);
        Size_t PosInvader (KBegInvader);
        Size_t PosMe      (KBegMe);

        bool IWin           = false;
        bool ILoose         = false;
        bool InvadersShoots = false;
        DisplaySpace (Space);
        GotoXY (10, 20);
        for (;;)
        {
            for (unsigned i (max (2u, KRatioMeInvaders)); i-- > 0; )
            {
                if (!ManageMe (Space, PosMe, ILoose) && ! ILoose)
                {
                    RecomputeSpace (Space, IWin, ILoose);
                }
                DisplaySpace (Space);
                if (ILoose || IWin) break;
            }
            if (ILoose || IWin) break;
            ILoose = ManageInvader (Direction, CurrentLine, PosInvader,
                                    InvadersShoots, IWin, Space);
            if (! IWin && ! ILoose)
                RecomputeSpace (Space, IWin, ILoose);
            DisplaySpace (Space);
            if (ILoose || IWin) break;
        }
        if (IWin)
        {
            cout << "J'ai gagné" << endl;
        }
        else
        {
            cout << "J'ai perdu" << endl;
        }

    } // SpaceInvaders()

} // namespace

