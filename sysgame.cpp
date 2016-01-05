#include "sysgame.h"
#include "screen.h"
#include "gameengine.h"
#include <unistd.h>
#include <iostream>

using namespace std;


namespace binaire
{

    funcManageMe *AIme = manageMe;
    funcManageInvader *AIinvader = manageInvader;

    bool run()
    {
        uint_t Win(0), Lost(0);
        resizeFrame(18, 30);
        CVFrame &GameBox = getBox(2,0,KSizeSpace, KSizeLine);
        CVFrame &TextBox = getBox(0,14,3, 20);
        for(uint_t i(0) ; i<5 ; ++i)
        {
            clearBufScreen();
            bool OK(false), NO(false);
            bool Shoot(true);
            int Incr(1);
            uint_t LinePosInvader(0), PosInv(KBegInvader), PosMe(KBegMe);
            initSpace(GameBox);
            writeInBox(TextBox, centerText("WIN : " + to_string(Win) + " Lost : " + to_string(Lost),18),setColor(KGreen, KbBlue),1,1);
            printFrame();
            while((!OK && !NO) && LinePosInvader!=(KSizeSpace-2))
            {
                recomputeFrame(GameBox,OK, NO);
                AIinvader(GameBox, Incr, LinePosInvader, PosInv, OK, Shoot);
                AIme(GameBox,PosMe, NO);
                updateFrame();
                sleep(1);
            }
            if(OK)
                ++Win;
            if(NO)
                ++Lost;
            writeInBox(getBox(0,14,3, 20), centerText("WIN : " + to_string(Win) + " Lost : " + to_string(Lost),18),setColor(KGreen, KbBlue),1,1);
        }
        clearBufScreen();
        return true;
    }

    void write(ostream &os, const string &Data, const uint_t &uTime)
    {
        char alphaLast(0);
        for(const char &letter : Data)
        {
            os << letter << flush;
            if((isalnum(letter) || alphaLast!=letter) && (rand())%4==0)
                usleep(uTime);
            else if(letter==' ' || letter=='\n')
                usleep(uTime*4/3);
            alphaLast = letter;
        }
    }

    string centerText(const string &Texte, const uint_t &size)
    {
        string Word, Output;
        vector<string> Line;
        uint_t LineSize(0);
        for(uint_t i(0) ; i<Texte.size() ; ++i)
        {
            if((i<1 && Texte[i]==' ') || (i>=1 && Texte[i]==' ' && Texte[i-1]==' '))
                continue;
            else if(Texte[i]!=' ')
            {
                Word += Texte[i];
            }
            else if(Word.size()>=size)
            {
                if(Line.size()!=0)
                {
                    const uint_t space((size - LineSize)/(Line.size()+1));
                    const string comSpace(space,' ');
                    for(uint_t j(0) ; j<Line.size() ; ++j)
                    {
                        Output += comSpace;
                        Output += Line[j];
                    }
                    Output += comSpace;
                    Output += string(Output.size()%size, ' ');
                    Line.clear();
                    LineSize = 0;
                }

                const string SSpace(size-(Word.size()%size), ' ');
                Output += Word + SSpace;
                Word.clear();
            }
            else
            {
                if((Word.size() + LineSize) >= size)
                {
                    const uint_t space((size - LineSize)/(Line.size()+1));
                    const string comSpace(space,' ');
                    for(uint_t j(0) ; j<Line.size() ; ++j)
                    {
                        Output += comSpace;
                        Output += Line[j];
                    }
                    Output += comSpace;
                    Output += string(Output.size()%size, ' ');
                    Line.clear();
                    LineSize = 0;
                }
                LineSize += Word.size();
                Line.push_back(Word);
                Word.clear();
            }
        }

        if((Word.size() + LineSize) < size)
        {
            Line.push_back(Word);
            LineSize += Word.size();
            Word.clear();
        }
        if(Line.size() != 0)
        {
            const uint_t space((size - LineSize)/(Line.size()+1));
            const string comSpace(space,' ');
            for(uint_t j(0) ; j<Line.size() ; ++j)
            {
                Output += comSpace;
                Output += Line[j];
            }
            Output += comSpace;
            Output += string(Output.size()%size, ' ');
            Line.clear();
            LineSize = 0;
        }
        if(Word.size()!=0)
        {
            const string SSpace(size - (Word.size()%size), ' ');
            Output += Word + SSpace;
            Word.clear();
        }
        return Output;
    }

}
