#pragma once
#include "MyType_ML.h"
namespace SpaceInvaderML
{
/*!
 * \brief Alias caractère de fond de l'espace.
 */
    const char KEmpty               = ' ';
    /*!
     * \brief Alias caractère de remplissage d'un envahisseur.
     */
    const char KInsideInvader       = 'W';
    /*!
     * \brief Alias caractère de remplissage d'un joueur.
     */
    const char KInsideMe            = 'A';
    /*!
     * \brief Alias caractère correspondant à une torpille.
     */
    const char KTorpedo             = '|';  // For me
    /*!
     * \brief Alias caractère correspondant à un missile.
     */
    const char KMissile             = 'T';  // For Invaders

    // caractères correspondants aux saisies
    /*!
     * \brief Alias du caractère pour aller à droite.
     */
    const char KRight               = '6';
    /*!
     * \brief Alias du carctère pour aller à gauche.
     */
    const char KLeft                = '4';
    /*!
     * \brief Alias du caractère pour tirer.
     */
    const char KShoot               = '5';

    // diverses tailles
    /*!
     * \brief Alias taille (en nombre de caractères) d'un envahisseur.
     */
    const Size_t KInvadersSize      = 4;
    /*!
     * \brief Alias déplacement du milieu d'un envahisseur.
     */
    const Size_t KInvadersMiddle    = KInvadersSize / 2;
    /*!
     * \brief Alias taille d'un joueur.
     */
    const Size_t KMySize            = 1;
    /*!
     * \brief Alias déplacement du milieu d'un joueur.
     */
    const Size_t KMyMiddle          = KMySize / 2;
    /*!
     * \brief Alias nombre de colonnes de l'espace.
     */
    const Size_t KSizeLine          = 10;
    /*!
     * \brief Alias nombre de lignes de l'espace.
     */
    const Size_t KSizeSpace         = 10;
    /*!
     * \brief Alias indice de la position initiale de l'envahisseur.
     */
    const Size_t KBegInvader        = 0;
    /*!
     * \brief Alias indice de la position initiale du joueur.
     */
    const Size_t KBegMe             = KSizeLine / 2;

    /*!
     * \brief Alias ratio de jeu entre le joueur et l'envahisseur.
     */
    const unsigned KRatioMeInvaders = 4;

    /*!
     * \brief Alias ligne vide.
     */
    const std::string KEmptyLine (KSizeLine, KEmpty);

    /*!
     * \brief Alias forme d'un envahisseur.
     */
    const std::string KInvadersForm (KInvadersSize, KInsideInvader);
    /*!
     * \brief Alias forme d'un joueur.
     */
    const std::string KMyForm       (KMySize,       KInsideMe);

    //Constantes de couleur
    /*!
     * \brief Alias remetant la couleur du texte du terminal à sa valeur par défaut.
     */
    const std::string KReset   ("0");

    /*!
     * \brief Alias mettant en noir la couleur du texte du terminal.
     */
    const std::string KBlack   ("30");
    /*!
     * \brief Alias mettant en rouge la couleur du texte du terminal.
     */
    const std::string KRed     ("31");

    /*!
     * \brief Alias mettant en vert la couleur du texte du terminal.
     */
    const std::string KGreen   ("32");

    /*!
     * \brief Alias mettant en jaune la couleur du texte du terminal.
     */
    const std::string KYellow  ("33");

    /*!
     * \brief Alias mettant en bleu la couleur du texte du terminal.
     */
    const std::string KBlue    ("34");

    /*!
     * \brief Alias mettant en mangenta la couleur du texte du terminal.
     */
    const std::string KMAgenta ("35");

    /*!
     * \brief Alias mettant en cyan la couleur du texte du terminal.
     */
    const std::string KCyan    ("36");

}
