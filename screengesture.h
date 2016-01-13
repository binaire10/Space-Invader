#pragma once
#include <ostream>
#include <string>
#include "mytype.h"
#include "myconst.h"

namespace binaire
{
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
     * \brief ClearBufScreen
     * function to clear screen and screen buffer
     */
    void clearBufScreen ();
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
}
