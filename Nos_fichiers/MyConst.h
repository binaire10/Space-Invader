#pragma once

/*!
  * \file MyConst_AC.h
  * \author Alain Casali Marc Laporte
  * \date 7 janvier 2016
  * \brief Fichier dÈcrivant l'ensemble des constantes utilisÈes dans le jeu
  * \version 1.0
  * \bug Aucun connu
  */

#include "MyType.h"
#include "readconfig.h"

namespace SpaceInvader
{
    //Constantes de couleur
    /*!
     * \brief Alias remetant la couleur du texte du terminal √  sa valeur par d√©faut.
     */
    const std::string KReset   ="\033[0m";

    /*!
     * \brief Alias mettant en noir la couleur du texte du terminal.
     */
    const unsigned KNoir    = 0;
    /*!
     * \brief Alias mettant en rouge la couleur du texte du terminal.
     */
    const unsigned KRouge   = 1;

    /*!
     * \brief Alias mettant en vert la couleur du texte du terminal.
     */
    const unsigned KVert    = 2;

    /*!
     * \brief Alias mettant en jaune la couleur du texte du terminal.
     */
    const unsigned KJaune   = 3;

    /*!
     * \brief Alias mettant en bleu la couleur du texte du terminal.
     */
    const unsigned KBleu    = 4;

    /*!
     * \brief Alias mettant en mangenta la couleur du texte du terminal.
     */
    const unsigned KMAgenta = 5;

    /*!
     * \brief Alias mettant en cyan la couleur du texte du terminal.
     */
    const unsigned KCyan    = 6;

    // Constantes pour les touches
    /*!
     * \brief Alias vers la touche servant √  se d√©placer √  droite.
     */
    const char KRight               = GetValueChar("KRight", "config.yaml", 'x');  // d√©placement vers la droite

    /*!
     * \brief Alias vers la touche servant √  se d√©placer √  gauche.
     */
    const char KLeft                = GetValueChar("KLeft", "config.yaml", 'w');  // D√©placement vers la gauche

    /*!
     * \brief Alias vers la touche servant √  lancer une torpille.
     */
    const char KShoot               = GetValueChar("KShoot", "config.yaml", ' ');  // Lancer de torpille

    //  Constantes li√©es √  l'envahisseur
    /*!
     * \brief Couleur de l'envahisseur.
     */
    const unsigned KInvadersColor = GetValueInt("KInvadersColor", "config.yaml", KJaune);  // Couleur de l'envahisseur

    /*!
     * \brief Caract√®rere formant l'envahisseur.
     */
    const char KInsideInvader       = GetValueChar("KInsideInvader", "config.yaml", 'W');  // caractËrere formant l'envahisseur

    /*!
     * \brief Caract√®rere formant le missile.
     */
    const char KMissile             = GetValueChar("KMissile", "config.yaml", 'T');  // missile

    const unsigned KFireWait    =  GetValueInt("KFireWait","config.yaml", 4);   // nombre de caractËres qui forment l'envahisseur

    /*!
     * \brief Nombre de caract√®res qui forment l'envahisseur.
     */
    const unsigned KInvadersSize    =  GetValueInt("KInvadersSize","config.yaml", 5);   // nombre de caractËres qui forment l'envahisseur

    /*!
     * \brief Nombre de fois o˘ l'envahisseur tire un missile par rapport ‡  son dÈplacement.
     */
    const unsigned KMissileRatio =  GetValueInt("KMissileRatio","config.yaml", 2); // nombre de fois o˘ l'envahisseur tire un missile par rapport √  son dÈplacement

    // Constantes li√©es au joueur
    /*!
     * \brief Couleur li√©e √  mes objets (vaisseaux et tropilles).
     */
    const unsigned KMyColor = GetValueInt("KMyColor", "config.yaml", KVert); // Ma couleur

    /*!
     * \brief Caract√®rere formant mon vaisseau.
     */
    const char KInsideMe            = GetValueChar("KInsideMe", "config.yaml", 'A'); // caractËrere formant mon vaisseau

    /*!
     * \brief Caract√®rere formant ma torpille.
     */
    const char KTorpedo             = GetValueChar("KTorpedo", "config.yaml", '|'); // caractËrere formant ma torpille

    /*!
     * \brief Nombre de caract√®res qui forment mon vaisseau.
     */
    const unsigned KMyLife          =  GetValueInt("KMySize","config.yaml", 4); //  nombre de caractËres qui forment mon vaisseau


    /*!
     * \brief Nombre de fois o√π c'est le tour du joueur pour un tour de l'envahisseur.
     */
    const unsigned KRatioMeInvaders =  GetValueInt("KRatioMeInvaders","config.yaml", 4);    // Nombre de fois o˘ c'est le tour du joueur pour un tour de l'envahisseur


    // Constantes li√©es √  l'eapace (l'√©cran)
    /*!
     * \brief Alias vers une case vide √  l'√©cran.
     */
    const char KEmpty               =  GetValueChar("KEmpty","config.yaml", ' ');  // case vide de l'Ècran
    /*!
     * \brief Nombre de lignes de l'√©cran (de l'espace).
     */
    const unsigned KSizeLine   =  GetValueInt("KSizeLine","config.yaml", 10);   // Nombre de lignes de l'Ècran (de l'espace)

    /*!
     * \brief Nombre de colonnes de l'√©cran (de l'espace).
     */
    const unsigned KSizeSpace  =  GetValueInt("KSizeSpace","config.yaml", 10);   // Nombre de colonnes de l'Ècran (de l'espace)

    /*!
     * \brief Num√©ro de colonne o√π commence l'envahisseur.
     */
    const unsigned KBegInvader =  GetValueInt("KBegInvader","config.yaml", 0);    // Num√©ro de colonne o˘ commence l'envahisseur

    /*!
     * \brief Num√©ro de colonne o√π commence le joueur.
     */
    const unsigned KBegMe      =  GetValueInt("KBegMe","config.yaml", 5);  // Num√©ro de colonne o˘ commence le joueur

    const char KBonus = GetValueChar("KBonus","config.yaml", '*')!=KEmpty ? GetValueChar("KBonus","config.yaml", '*') : '*';
}//namespace
