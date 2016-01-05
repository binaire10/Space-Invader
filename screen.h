#ifndef SCREEN_H
#define SCREEN_H
#include "globaltype.h"
#include <unistd.h>
#include "tool.h"
/**
 * @file screen.h
 * \brief Help to work on terminal (screen) into all tool on screen
 * @author (binaire) Alexandre Wery
 */
namespace binaire {
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

    /**
         * \brief operator ==
         * bool operator for __EscapeCmd
         * @return
         */
    bool operator ==(const __EscapeCmd &, const __EscapeCmd &);


    /**
     * @typedef CCharColor
     * \brief CCharColor
     * representation of an element of screen buffer
     */
    typedef std::pair<char, __EscapeCmd> CCharColor;

    /**
     * @typedef CVLineFrame
     * \brief CVLineFrame
     * line of an screen buffer
     */
    typedef std::vector<CCharColor> CVLineFrame;

    /**
     * @typedef CVSurface
     * \brief CVSurface
     * it's a array class todo a screen buffer.
     */
    typedef std::vector<CVLineFrame> CVSurface;



    /**
     * \brief ClearBufScreen
     * function to clear screen and screen buffer
     */
    void clearBufScreen ();
    /**
     * @var KReset
     * \brief KReset
     * Reset Terminal
     */
    const std::string KReset    =   "0";
    /**
     * @var KBlack
     * \brief KBlack
     * set color text to black
     */
    const std::string KBlack    =   "30";
    /**
     * @var KRed
     * \brief KRed
     * set color text to red
     */
    const std::string KRed      =   "31";
    /**
     * @var KGreen
     * \brief KGreen
     * set color text to green
     */
    const std::string KGreen    =   "32";
    /**
     * @var KYellow
     * \brief KYellow
     * set color text to yellow
     */
    const std::string KYellow   =   "33";
    /**
     * @var KBlue
     * \brief KBlue
     * set color text to blue
     */
    const std::string KBlue     =   "34";
    /**
     * @var KMAgenta
     * \brief KMAgenta
     * set color text to magenta
     */
    const std::string KMAgenta  =   "35";
    /**
     * @var KCyan
     * \brief KCyan
     * set color text to Cyan
     */
    const std::string KCyan     =   "36";
    /**
     * @var KbBlack
     * \brief KbBlack
     * set color background to black
     */
    const std::string KbBlack   =   "40";
    /**
     * @var KbRed
     * \brief KbRed
     * set color background to red
     */
    const std::string KbRed     =   "41";
    /**
     * @var KbGreen
     * \brief KbGreen
     * set color background to green
     */
    const std::string KbGreen   =   "42";
    /**
     * @var KbYellow
     * \brief KbYellow
     * set color background to yellow
     */
    const std::string KbYellow  =   "43";
    /**
     * @var KbBlue
     * \brief KbBlue
     * set color background to blue
     */
    const std::string KbBlue    =   "44";
    /**
     * @var KbMAgenta
     * \brief KbMAgenta
     * set color background to magenta
     */
    const std::string KbMAgenta =   "45";
    /**
     * @var KbCyan
     * \brief KbCyan
     * set color background to cyan
     */
    const std::string KbCyan    =   "46";

    // Console Control
    /**
     * \brief Color
     * function to change color of texte
     * @param coul
     * Constante of Color KColore/KbColor
     */
    void color(const std::string &coul);
    /**
     * @fn clearCMD
     * \brief clearCMD
     * function for flux to clear screen
     * \brief [deprecated] clear console
     * @deprecated more better usage of clearScreen with cout
     * @return
     */
    const __EscapeCmd clearCMD ();

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
    __EscapeCmd setColor(const std::string &coul, const std::string &back = KReset);

    /**
     * \brief GotoXY
     * move cursor
     * @deprecated more better usage of GotoXY like operator <<
     * @param X
     * Position X
     * @param Y
     * Position Y
     */

    void gotoXY (unsigned X, unsigned Y); // gotoxy()
    /**
     * \brief GotoXY
     * Creat escape Comande to move cursor
     * @param pos
     * Position of cursor
     * @return
     */
    const __EscapeCmd gotoXY(CPosXY pos);
    /**
     * @var clearLine
     * \brief clearLine
     * smart code to clean screen
     */
    const std::string clearLine     =  "\033[2K";
    /**
     * @var clearScreen
     * \brief clearScreen
     * smart code to clean Line
     */
    const std::string clearScreen   =  "\033c";

    // Screen Process
    /**
     * \brief printFrame
     * code to print on screen The data in Buffer
     * @deprecated prefer updateFrame
     */
    void printFrame();
    /**
     * \brief updateFrame
     * code to print on screen element changed
     */
    void updateFrame();
    /**
     * \brief resizeFrame
     * resize lenght of screen buffer
     * @param X
     * X axis lenght
     * @param Y
     * Y axis lenght
     */
    void resizeFrame(unsigned X, unsigned Y);

    /**
     * @typedef CVFrame
     * \brief CVFrame
     * is a semantique type and compatibility to like CVFrame base.
     * CVFrame it's a framme of an CVSurface. CVFrame is a bi-dimensionnal array
     */
    typedef experimental::BiDimvectorRef<CCharColor> CVFrame;
    /**
     * @typedef CVLineRef
     * \brief CVLineRef
     * is an simple definition of CVFrame line
     */
    typedef CVFrame::TabLineRef CVLineRef;
    /**
     * \brief FrameValidator
     * Can Valide a frame from buffer screen
     * @param val
     * Frame to valide
     * @param x
     * from x position
     * @param y
     * from y position
     * @return
     */
    bool frameValidator(const CVFrame &val, const uint_t &x, const uint_t &y);

    // Frame Mod
    /**
     * \brief getPix
     * get data from buffer screen
     * @param X
     * Postion Axis X
     * @param Y
     * Postion Axis Y
     * @return
     * an CCharColor from position
     */
    CCharColor &getPix(unsigned X, unsigned Y);

    /**
     * \brief getMainFrame
     * fonction to get screen buffer
     * @deprecated please use getBox instead getMainFrame
     * @return
     * screen buffer
     */
    CVSurface &getMainFrame();

    /**
     * \brief getBox
     * get frame of screen buffer By reference
     * @param x
     * tell column where begin
     * @param y
     * tell line where begin
     * @param heigh
     * number of column ge
     * @param width
     * @return
     */
    CVFrame &getBox(const uint_t &x, const uint_t y, const uint_t &heigh, const uint_t &width);

    /**
     * \brief writeInBox
     * function to write inside box
     * @param color
     * Escape code
     * @param borderH
     * border horizontal size
     * @param borderV
     * border vertical size
     */
    void writeInBox(const CVFrame &, const std::string &, __EscapeCmd color = KReset, const uint_t &borderH=0, const uint_t &borderV = 0);

    /**
     * \brief ViewAt
     * function to get value at pos (X, Y)
     * @param X
     * @param Y
     * @return
     */
    const CCharColor &viewAt(unsigned X, unsigned Y);

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

    // flux Op
    /**
     * \brief operator <<
     * do comptible CCharColor with flux
     * @param os
     * @param Val
     * @return
     */
    std::ostream &operator << (std::ostream &os, const CCharColor &Val);
    /**
     * \brief operator <<
     * do comptible __EscapeCmd with flux
     * @param os
     * @param Mode
     * @return
     */
    std::ostream &operator << (std::ostream &os, const __EscapeCmd &Mode);

    /**
     * \brief operator ==
     * do compatible with char boolean
     * @return
     */
    bool operator ==(const CCharColor &, const char &);
    /**
     * \brief operator ==
     * do compatible with char boolean
     * @return
     */
    bool operator ==(const char &, const CCharColor &);

    /**
     * \brief operator !=
     * do compatible with char boolean
     * @return
     */
    bool operator !=(const CCharColor &, const char &);
    /**
     * \brief operator !=
     * do compatible with char boolean variable type CCharColor
     * @return
     */
    bool operator !=(const char &, const CCharColor &);
}

#endif // SCREEN_H
