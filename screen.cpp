#include <iostream>
#include "grille.h"
#include "gameengine.h"
#include "tool.h"
#include "screen.h"

using namespace std;

namespace binaire
{
    std::ostream &operator << (std::ostream &os, const __EscapeCmd &Mode)
    {
        os << Mode.s_CODE;
        return os;
    }

    /**
     * @private
     * \brief TabLast
     * Object to delete CVFrame creat by getBox
     */
    experimental::AutoRemover<CVFrame> TabLast;
    /**
     * @private
     * @var LastFrame
     * \brief LastFrame
     */
    CVSurface LastFrame;
    /**
     * @private
     * @var MainFrame
     * \brief MainFrame
     */
    CVSurface MainFrame;

    void clearBufScreen()
    {
        if(LastFrame.size()!=0)
            LastFrame = CVSurface(LastFrame.size(), CVLineFrame(LastFrame[0].size(), KPxEmpty));
        cout << clearScreen << flush;
    }

    /**
     * \brief Color
     * function to change color of texte
     * @param coul
     * Constante of Color KColore/KbColor
     */
    void color(const string &coul)
    {
        cout << "\033[" << coul <<"m";
    }

    void gotoXY(unsigned X, unsigned Y)
    {
        cout << "\033[" << Y << ';' << X << "H";

    }

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
    __EscapeCmd setColor(const string &coul, const string &back)
    {
        return "\033["+back+";"+coul+"m";
    }

    const __EscapeCmd clearCMD()
    {
        return "\033c";
    }

    void printFrame()
    {
        //ClearScreen();
        for(CVLineFrame &Line : MainFrame)
        {
            for(CCharColor &Px : Line)
            {
                cout << Px << flush;
            }
            cout << '\n';
        }
        LastFrame = MainFrame;
    }

    void updateFrame()
    {
        for(uint_t i(0) ; i <MainFrame.size() ; ++i)
        {
            CVLineFrame &LigneM = MainFrame[i];
            CVLineFrame &LigneLM = LastFrame[i];
            if(LigneM != LigneLM)
            {

                cout << gotoXY(make_pair(i,0)) << clearLine;
                for(uint_t j(0) ; j<LigneM.size() ; ++j)
                {
                    cout << LigneM[j];
                }
            }
        }
        cout << gotoXY(make_pair(MainFrame.size(),0)) << flush;
        LastFrame = MainFrame;
    }

    const __EscapeCmd gotoXY(CPosXY pos)
    {
        return "\033[" + to_string(pos.first+1) + ";" + to_string(pos.second) + "H";
    }

    CCharColor &getPix(unsigned X, unsigned Y)
    {
        return MainFrame[X][Y];
    }
    /**
    * \brief __EscapeCmd
    * Constructor
    * @param Code
    * Escape Sequence
    */
    __EscapeCmd::__EscapeCmd(const string &Code) : s_CODE(Code)
    {}

    __EscapeCmd::__EscapeCmd(const char *Code) : __EscapeCmd(std::string(Code))
    {}

    /**
     * \brief operator <<
     * do comptible CCharColor with flux
     * @param os
     * @param Val
     * @return
     */
    ostream &operator<<(ostream &os, const CCharColor &Val)
    {
        os << Val.second.s_CODE << Val.first << Val.second.s_postCODE;
        return os;
    }

    void resizeFrame(unsigned X, unsigned Y)
    {
        MainFrame.resize(X, CVLineFrame(Y, KPxEmpty));
        LastFrame.resize(X, CVLineFrame(Y, KPxEmpty));
    }

    const CCharColor &viewAt(unsigned X, unsigned Y)
    {
        return MainFrame[X][Y];
    }

    CVSurface &getMainFrame()
    {
        return MainFrame;
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


    //  __EscapeCmd

    bool operator ==(const __EscapeCmd &, const __EscapeCmd &)
    {return true;}

    // CCharColorRef

    CVFrame &getBox(const uint_t &x, const uint_t y, const uint_t &heigh, const uint_t &width)
    {
        for(uint_t i(0) ; i<TabLast.size() ; ++i)
        {
            CVFrame &val = *TabLast.get(i);
            if(val.size() == heigh && val[0].size() == width && frameValidator(*(TabLast.get(0)), x, y))
                return *TabLast.get(i);
        }
        TabLast.add(new CVFrame);

        CVFrame &Frame = *TabLast.get(TabLast.size()-1);
        Frame.clear();
        Frame.setTabRef(MainFrame,x, y, heigh, width);
        return Frame;
    }

    bool frameValidator(const CVFrame &val, const uint_t &x, const uint_t &y)
    {
        for(uint_t i(0) ; i<val.size() ; ++i)
        {
            for(uint_t j(0) ; j<val[i].size() ; ++j)
            {
                if(&val[i][j] != &MainFrame[i+y][j+x])
                    return false;
            }
        }
        return true;
    }

    /**
     * \brief writeInBox
     * function to write inside box
     * @param Box
     * Frame of buffer screen
     * @param Str
     * Text to write in to the frame
     * @param Color
     * Escape code
     * @param borderH
     * border horizontal size
     * @param borderV
     * border vertical size
     */
    void writeInBox(const CVFrame &Box, const string &Str, __EscapeCmd Color, const uint_t &borderH, const uint_t &borderV)
    {
        uint_t Pos(0), x(borderH), y(borderV);
        while(Pos<Str.size() && (y+borderV)<Box.size())
        {
            Box[y][x++] = creatPix(Str[Pos++],"");
            if((x+borderH)>=Box[y].size())
            {
                ++y;
                x = 0;
            }
        }
        for(CVLineRef Line : Box)
        {
            Line[0].second = Color;
            Line[Line.size()-1].second.s_postCODE = setColor(KReset).s_CODE;
        }
    }

}

