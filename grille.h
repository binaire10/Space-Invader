#ifndef GRILLE_H
#define GRILLE_H
#include <string>
#include <vector>
#include "globaltype.h"
#include "screen.h"
#include "configfile.h"

/**
 * @file grille.h
 * \brief All constant of this game are here
 * @author (binaire) Alexandre Wery
 */

namespace binaire {
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

    //  Constantes liées à l'envahisseur

    /**
     * @var KInvadersColor
     * \brief KInvadersColor
     * color of space invader
     */
    const std::string KInvadersColor= getValueStr("COLOR_INVADER","SpaceInvader.config", KYellow);  // Couleur de l'envahisseur
    /**
     * @var KInsideInvader
     * \brief KInsideInvader
     * caracter who made invader
     */
    const char KInsideInvader       = getValueChar("INSIDE_INVADER","SpaceInvader.config", 'W');  // caractèrere formant l'envahisseur
    /**
     * @var KMissile
     * \brief KMissile
     * caracter who made Missile
     */
    const char KMissile             = getValueChar("INSIDE_MISSILE","SpaceInvader.config", 'T');  // missile
    /**
     * @var KInvadersSize
     * \brief KInvadersSize
     * size of invader
     */
    const unsigned KInvadersSize    =  getValueInt("SIZE_INVADER","SpaceInvader.config", 4);   // nombre de caractères qui forment l'envahisseur
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
    const std::string KMyColor      = getValueStr("COLOR_ME","SpaceInvader.config", KGreen);
    /**
     * @var KInsideMe
     * \brief KInsideMe
     * caracter who made player
     */
    const char KInsideMe            = getValueChar("INSIDE_ME","SpaceInvader.config", 'A');
    /**
     * @var KTorpedo
     * \brief KTorpedo
     * torpedo caracter
     */
    const char KTorpedo             = getValueChar("INSIDE_TORPEDO","SpaceInvader.config", '|');
    /**
     * @var KMySize
     * \brief KMySize
     * size of player
     */
    const unsigned KMySize          = getValueInt("SIZE_ME","SpaceInvader.config", 1);
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
    const unsigned KSizeLine   = getValueInt("SIZE_MAP_Y","SpaceInvader.config", 10);   // Nombre de lignes de l'écran (de l'espace)

    /**
     * @var KSizeSpace
     * \brief KSizeSpace
     * size of one column
     */
    const unsigned KSizeSpace  = getValueInt("SIZE_MAP_X","SpaceInvader.config", 10);   // Nombre de colonnes de l'écran (de l'espace)

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
}

#endif // GRILLE_H
