#pragma once
#include <vector>
#include "shadowTool.h"
#include "shadowclass.h"

/**
 * @typedef CCharColor
 * \brief CCharColor
 * representation of an element of screen buffer
 */
typedef std::pair<char, binaire::__EscapeCmd> CCharColor;

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
* @typedef CPosXY
* \brief CPosXY
* Object position
*/
typedef std::pair<unsigned , unsigned> CPosXY;
/**
 * @typedef CVFrame
 * \brief CVFrame
 * is a semantique type and compatibility to like CVFrame base.
 * CVFrame it's a framme of an CVSurface. CVFrame is a bi-dimensionnal array
 */
typedef binaire::experimental::BiDimvectorRef<CCharColor> CVFrame;
/**
 * @typedef CVLineRef
 * \brief CVLineRef
 * is an simple definition of CVFrame line
 */
typedef CVFrame::TabLineRef CVLineRef;
