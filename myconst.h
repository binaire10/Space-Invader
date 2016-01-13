#pragma once
#include <string>
#include "configLoader.h"
#include "mytype.h"
#include "lightinitilize.h"


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
/**
 * @var KEmpty
 * \brief KEmpty
 * Empty character
 */
const char KEmpty               = ' ';  // case vide de l'écran
/**
 * @var KRight
 * \brief KRight
 */
const char KRight               = '6';  // déplacement vers la droite
/**
 * @var KLeft
 * \brief KLeft
 */
const char KLeft                = '4';  // Déplacement vers la gauche
/**
 * @var KShoot
 * \brief KShoot
 */
const char KShoot               = '5';  // Lancé de torpille
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
//  Constantes liées à l'envahisseur

/**
 * @var KInvadersColor
 * \brief KInvadersColor
 * color of space invader
 */
const std::string KInvadersColor= binaire::getValueStr("COLOR_INVADER","SpaceInvader.config", KYellow);  // Couleur de l'envahisseur

/**
 * @var KInsideInvader
 * \brief KInsideInvader
 * caracter who made invader
 */
const char KInsideInvader       = binaire::getValueChar("INSIDE_INVADER","SpaceInvader.config", 'W');  // caractèrere formant l'envahisseur

/**
 * @var KMissile
 * \brief KMissile
 * caracter who made Missile
 */
const char KMissile             = binaire::getValueChar("INSIDE_MISSILE","SpaceInvader.config", 'T');  // missile

/**
 * @var KInvadersSize
 * \brief KInvadersSize
 * size of invader
 */
const unsigned KInvadersSize    =  binaire::getValueInt("SIZE_INVADER","SpaceInvader.config", 4);   // nombre de caractères qui forment l'envahisseur

/**
 * @var KInvadersMiddle
 * \brief KInvadersMiddle
 * middle size of invader
 */
const unsigned KInvadersMiddle  = KInvadersSize / 2;
/**
 * @var KInvadersForm
 * \brief KInvadersForm
 * invader form
 * @deprecated Use KInsideInvader instead this
 */
const std::string KInvadersForm = std::string(KInvadersSize, KInsideInvader);  // forme de l'envahisseur

// Constantes liées au joueur

/**
 * @var KMyColor
 * \brief KMyColor
 * Color of player
 */
const std::string KMyColor      = binaire::getValueStr("COLOR_ME","SpaceInvader.config", KGreen);
/**
 * @var KInsideMe
 * \brief KInsideMe
 * caracter who made player
 */
const char KInsideMe            = binaire::getValueChar("INSIDE_ME","SpaceInvader.config", 'A');
/**
 * @var KTorpedo
 * \brief KTorpedo
 * torpedo caracter
 */
const char KTorpedo             = binaire::getValueChar("INSIDE_TORPEDO","SpaceInvader.config", '|');
/**
 * @var KMySize
 * \brief KMySize
 * size of player
 */
const unsigned KMySize          = binaire::getValueInt("SIZE_ME","SpaceInvader.config", 1);
/**
 * @var KMyMiddle
 * \brief KMyMiddle
 * middle size of player
 */
const unsigned KMyMiddle        = KMySize / 2;
/**
 * @var KMyForm
 * \brief KMyForm
 * player form
 * @deprecated Use KInsideMe instead this
 */
const std::string KMyForm       = std::string(KMySize, KInsideMe);

// Constantes liées à l'eapace (l'écran)

/**
 * @var KSizeLine
 * \brief KSizeLine
 * Size of one line
 */
const unsigned KSizeLine   = binaire::getValueInt("SIZE_MAP_Y","SpaceInvader.config", 10);   // Nombre de lignes de l'écran (de l'espace)

/**
 * @var KSizeSpace
 * \brief KSizeSpace
 * size of one column
 */
const unsigned KSizeSpace  = binaire::getValueInt("SIZE_MAP_X","SpaceInvader.config", 10);   // Nombre de colonnes de l'écran (de l'espace)

/**
 * @var KBegInvader
 * \brief KBegInvader
 * where begin invader
 */
const unsigned KBegInvader = 0;    // Numéro de colonne où commence l'envahisseur

/**
 * @var KBegMe
 * \brief KBegMe
 * where player begin
 */
const unsigned KBegMe      = KSizeLine / 2;  // Numéro de colonne où commence le joueur

/**
 * @var KEmptyLine
 * \brief KEmptyLine
 * Empty line
 * @deprecated Use KEmpty instead this
 */
const std::string KEmptyLine = std::string(KSizeLine, KEmpty);  // Une ligne vide de la matrice

/**
 * @var KRatioMeInvaders
 * \brief KRatioMeInvaders
 * number round where player can be play
 */
const unsigned KRatioMeInvaders = 4;    // Nombre de fois où c'est le tour du joueur pour un tour de l'envahisseur


/**
 * @var KPxEmpty
 * \brief KPxEmpty
 * fast access to An empty
 */
const CCharColor KPxEmpty        = binaire::creatPix(KEmpty,           "");
/**
 * @var KPxMissile
 * \brief KPxMissile
 * fast access to  Missile
 */
const CCharColor KPxMissile      = binaire::creatPix(KMissile,         KRed);
/**
 * @var KPxTorpedo
 * \brief KPxTorpedo
 * fast access to Torpedo
 */
const CCharColor KPxTorpedo      = binaire::creatPix(KTorpedo,         KBlue);
/**
 * @var KPxInsideInvader
 * \brief KPxInsideInvader
 * fast access to Invader
 */
const CCharColor KPxInsideInvader= binaire::creatPix(KInsideInvader,   KInvadersColor);
/**
 * @var KPxInsideMe
 * \brief KPxInsideMe
 * fast access to me
 */
const CCharColor KPxInsideMe    = binaire::creatPix(KInsideMe,        KMyColor);

