#include "gameengine.h"
#include "screen.h"
#include "grille.h"
#include <iostream>
#include <cstring>
#include <time.h>
#include <valarray>
#include "tool.h"

using namespace std;
namespace binaire
{


    bool projectileMoveTo(CCharColor &From, CCharColor &To, const char &Target)
    {
        CCharColor Val(To);
        if(Val!=KEmpty)
            To = KPxEmpty;
        else
            To = From;
        From = KPxEmpty;
        return Val == Target;

    }

    void remove(CVSurface &GameFrame, unsigned Line)
    {
        CVLineFrame &VLine(GameFrame[Line]);
        for(CCharColor &Val : VLine)
            Val = KPxEmpty;
    }

    void manageInvader(CVSurface &Space, int &Increment, unsigned &CurrentLine, unsigned &Beg, bool &Win, bool &ToShoot)
    {
        ToShoot = !ToShoot;

        CVLineFrame &currentLine = Space[CurrentLine];
        if(Increment == 1)
        {
            currentLine[Beg + KInvadersForm.size()] = KPxInsideInvader;
            currentLine[Beg++] = KPxEmpty;
        }
        else
        {
            currentLine[--Beg] = KPxInsideInvader;
            currentLine[Beg + KInvadersForm.size()] = KPxEmpty;
        }

        if(Increment == -1 && currentLine[0] == KInsideInvader)
        {
            Increment = 1;
            CVLineFrame &futureLine = Space[++CurrentLine];
            if(Find(KTorpedo, futureLine) != futureLine.size())
                Win = true;
            futureLine.swap(currentLine);
        }
        else if(Increment == 1 && currentLine[currentLine.size()-1] == KInsideInvader)
        {
            CVLineFrame &futureLine = Space[++CurrentLine];
            Increment = -1;
            if(Find(KTorpedo, futureLine) != futureLine.size())
                Win = true;
            futureLine.swap(currentLine);
        }

        if(ToShoot)
        {
            uint_t pos(rand()%KInvadersSize);
            Space[CurrentLine+1][pos + Beg] = KPxMissile;
        }
    }

    void initSpace(CVSurface &GameFrame)
    {
        srand (time(NULL));
        GameFrame = CVSurface(KSizeSpace,CVLineFrame(KSizeLine, KPxEmpty));
        for(uint_t i(0) ; i < KInvadersForm.size() ; ++i)
            GameFrame[0][i + KBegInvader] = creatPix(KInvadersForm[i], KYellow);

        for(uint_t i(0) ; i < KMyForm.size() ; ++i)
            GameFrame[GameFrame.size()-1][i+KBegMe] = creatPix(KMyForm[i], KGreen);
    }

    void manageMe(CVSurface &Space, unsigned &Pos, bool &Lost)
    {
        vector<uint_t> WarnLevelX(Space[0].size());
        vector<uint_t> WarnLevelY(Space.size());
        uint_t WarnLeft(0), WarnRight(0), WarnFront(0);
        for(uint_t i(0) ; i<Space.size() ; ++i)
        {
            for(uint_t j(0) ; j<Space[i].size() ; ++j)
            {
                WarnLevelX[j] += (Space[i][j]==KMissile);
                WarnLevelY[i] += (Space[j][i]==KMissile);
            }
        }
        for(uint_t i(0) ; i<WarnLevelY.size() ; ++i)
        {
            if(i<Pos)
            {
                WarnLeft += WarnLevelY[i];
            }
            else if(i==Pos)
            {
                WarnFront += WarnLevelY[i];
            }
            else if(i>Pos)
            {
                WarnRight += WarnLevelY[i];
            }
        }

        CVLineFrame &Line = Space[Space.size()-1];

        if(Pos != 0 && (Pos+1)==Line.size() && WarnLevelY[Pos-1]!=0 && WarnLevelY[Pos]!=0 && WarnLevelY[Pos+1]!=0)
            return;
        if(WarnLeft < WarnRight && Pos != 0 && (WarnLevelY[Pos+1]!=0 || WarnLevelY[Pos]!=0))
        {
            if(Line[Pos-1] != KMissile)
                swap(Line[Pos], Line[Pos-1]);
            else
            {
                Line[Pos] = Line[Pos-1] = KPxEmpty;
                Lost = true;
            }
            --Pos;
        }
        else if(Pos==0 && Line[Pos+1] != KMissile )
        {
            if(Line[Pos+1] != KMissile)
                swap(Line[Pos], Line[Pos+1]);
            else
            {
                Line[Pos] = Line[Pos-1] = KPxEmpty;
                Lost = true;
            }
            if(Line[Pos+1] != KMissile)
                swap(Line[Pos], Line[Pos+1]);
            ++Pos;
        }
        else if((Pos+1)==Line.size() && Line[Pos-1] != KMissile)
        {
            if(Line[Pos-1] != KMissile)
                swap(Line[Pos], Line[Pos-1]);
            else
            {
                Line[Pos] = Line[Pos-1] = KPxEmpty;
                Lost = true;
            }
            --Pos;
        }

    }


    void initSpace(CVFrame &GameFrame)
    {
        srand (time(NULL));
        for(CVLineRef &Line : GameFrame)
            for(CCharColor &PXref : Line)
                PXref = KPxEmpty;
        for(uint_t i(0) ; i < KInvadersForm.size() ; ++i)
            GameFrame[0][i + KBegInvader] = KPxInsideInvader;

        for(uint_t i(0) ; i < KMyForm.size() ; ++i)
            GameFrame[GameFrame.size()-1][i+KBegMe] = KPxInsideMe;
    }

    void remove(CVFrame &GameFrame, unsigned Line)
    {
        CVLineRef &VLine(GameFrame[Line]);
        for(CCharColor &Val : VLine)
            Val = KPxEmpty;
    }

    void manageMe(CVFrame &Space, unsigned &Pos, bool &Lost)
    {

        vector<uint_t> WarnLevelX(Space[0].size());
        vector<uint_t> WarnLevelY(Space.size());
        uint_t WarnLeft(0), WarnRight(0), WarnFront(0);
        for(uint_t i(0) ; i<Space.size() ; ++i)
        {
            for(uint_t j(0) ; j<Space[i].size() ; ++j)
            {
                WarnLevelX[j] += (Space[i][j]==KMissile);
                WarnLevelY[i] += (Space[j][i]==KMissile);
            }
        }
        for(uint_t i(0) ; i<WarnLevelY.size() ; ++i)
        {
            if(i<Pos)
            {
                WarnLeft += WarnLevelY[i];
            }
            else if(i==Pos)
            {
                WarnFront += WarnLevelY[i];
            }
            else if(i>Pos)
            {
                WarnRight += WarnLevelY[i];
            }
        }

        CVLineRef &Line = Space[Space.size()-1];

        if(Pos != 0 && (Pos+1)==Line.size() && WarnLevelY[Pos-1]!=0 && WarnLevelY[Pos]!=0 && WarnLevelY[Pos+1]!=0)
            return;
        if(WarnLeft < WarnRight && Pos != 0 && (WarnLevelY[Pos+1]!=0 || WarnLevelY[Pos]!=0))
        {
            if(Line[Pos-1] != KMissile)
                swap(Line[Pos], Line[Pos-1]);
            else
            {
                Line[Pos] = KPxEmpty;
                Line[Pos-1] = KPxEmpty;
                Lost = true;
            }
            --Pos;
        }
        else if(Pos==0 && Line[Pos+1] != KMissile )
        {
            if(Line[Pos+1] != KMissile)
                swap(Line[Pos], Line[Pos+1]);
            else
            {
                Line[Pos] = KPxEmpty;
                Line[Pos-1] = KPxEmpty;
                Lost = true;
            }
            ++Pos;
        }/*
        else if(WarnRight < WarnLeft && (Pos+1)!=Line.size() && (WarnLevelY[Pos-1]!=0 || WarnLevelY[Pos]!=0))
        {
            Line[Pos].value() = KPxEmpty;
            Line[Pos-1].value() = KPxEmpty;
            Lost = true;
            ++Pos;
        }*/
        else if((Pos+1)==Line.size() && Line[Pos-1] != KMissile)
        {
            if(Line[Pos-1] != KMissile)
                swap(Line[Pos], Line[Pos-1]);
            else
            {
                Line[Pos] = KPxEmpty;
                Line[Pos-1] = KPxEmpty;
                Lost = true;
            }
            --Pos;
        }
    }

    void manageInvader(CVFrame &Space, int &Increment, unsigned &CurrentLine, unsigned &Beg, bool &Win, bool &ToShoot)
    {
        ToShoot = !ToShoot;

        CVLineRef &currentLine = Space[CurrentLine];
        if(Increment == 1)
        {
            currentLine[Beg + KInvadersForm.size()] = KPxInsideInvader;
            currentLine[Beg++] = KPxEmpty;
        }
        else
        {
            currentLine[--Beg] = KPxInsideInvader;
            currentLine[Beg + KInvadersForm.size()] = KPxEmpty;
        }

        if(Increment == -1 && currentLine[0] == KInsideInvader)
        {
            Increment = 1;
            CVLineRef &futureLine = Space[++CurrentLine];
            if(Find(KTorpedo, futureLine) != futureLine.size())
                Win = true;
            for(uint_t i(0) ; i<currentLine.size() ; ++i)
                swap(currentLine[i], futureLine[i]);
        }
        else if(Increment == 1 && currentLine[currentLine.size()-1] == KInsideInvader)
        {
            CVLineRef &futureLine = Space[++CurrentLine];
            Increment = -1;
            if(Find(KTorpedo, futureLine) != futureLine.size())
                Win = true;
            for(uint_t i(0) ; i<currentLine.size() ; ++i)
                swap(currentLine[i], futureLine[i]);
        }

        if(ToShoot)
        {
            uint_t pos(rand()%KInvadersSize);
            Space[CurrentLine+1][pos + Beg] = KPxMissile;
        }
    }

}
