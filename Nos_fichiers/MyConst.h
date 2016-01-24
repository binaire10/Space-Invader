#pragma once

/*!
  * \file MyConst_AC.h
  * \author Alain Casali Marc Laporte
  * \date 7 janvier 2016
  * \brief Fichier décrivant l'ensemble des constantes utilisées dans le jeu
  * \version 1.0
  * \bug Aucun connu
  */

#include "MyType.h"
#include "readconfig.h"

namespace SpaceInvader
{
    //Constantes de couleur
    /*!
     * \brief Alias remetant la couleur du texte du terminal à  sa valeur par défaut.
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
     * \brief Alias vers la touche servant à  se déplacer à  droite.
     */
    const char KRight               = GetValueChar("KRight", "config.yaml", 'x');  // déplacement vers la droite

    /*!
     * \brief Alias vers la touche servant à  se déplacer à  gauche.
     */
    const char KLeft                = GetValueChar("KLeft", "config.yaml", 'w');  // Déplacement vers la gauche

    /*!
     * \brief Alias vers la touche servant à lancer une torpille.
     */
    const char KShoot               = GetValueChar("KShoot", "config.yaml", ' ');  // Lancer de torpille

    //  Constantes liées à  l'envahisseur
    /*!
     * \brief Couleur de l'envahisseur.
     */
    const unsigned KInvadersColor = GetValueInt("KInvadersColor", "config.yaml", KJaune);  // Couleur de l'envahisseur

    /*!
     * \brief Caractèrere formant l'envahisseur.
     */
    const char KInsideInvader       = GetValueChar("KInsideInvader", "config.yaml", 'W');  // caractèrere formant l'envahisseur

    /*!
     * \brief Caractèrere formant le missile.
     */
    const char KMissile             = GetValueChar("KMissile", "config.yaml", 'T');  // missile

    const unsigned KFireWait    =  GetValueInt("KFireWait","config.yaml", 4);   // nombre de caractères qui forment l'envahisseur

    /*!
     * \brief Nombre de caractères qui forment l'envahisseur.
     */
    const unsigned KInvadersSize    =  GetValueInt("KInvadersSize","config.yaml", 5);   // nombre de caractères qui forment l'envahisseur

    /*!
     * \brief Nombre de fois où l'envahisseur tire un missile par rapport à  son déplacement.
     */
    const unsigned KMissileRatio =  GetValueInt("KMissileRatio","config.yaml", 2); // nombre de fois où l'envahisseur tire un missile par rapport à  son déplacement

    // Constantes liées au joueur
    /*!
     * \brief Couleur liée à  mes objets (vaisseaux et tropilles).
     */
    const unsigned KMyColor = GetValueInt("KMyColor", "config.yaml", KVert); // Ma couleur

    /*!
     * \brief Caractèrere formant mon vaisseau.
     */
    const char KInsideMe            = GetValueChar("KInsideMe", "config.yaml", 'A'); // caractèrere formant mon vaisseau

    /*!
     * \brief Caractèrere formant ma torpille.
     */
    const char KTorpedo             = GetValueChar("KTorpedo", "config.yaml", '|'); // caractèrere formant ma torpille

    /*!
     * \brief Nombre de caractères qui forment mon vaisseau.
     */
    const unsigned KMyLife          =  GetValueInt("KMyLife","config.yaml", 4); //  nombre de caractères qui forment mon vaisseau


    /*!
     * \brief Nombre de fois où c'est le tour du joueur pour un tour de l'envahisseur.
     */
    const unsigned KRatioMeInvaders =  GetValueInt("KRatioMeInvaders","config.yaml", 4);    // Nombre de fois où c'est le tour du joueur pour un tour de l'envahisseur


    // Constantes liées à  l'eapace (l'écran)
    /*!
     * \brief Alias vers une case vide à  l'écran.
     */
    const char KEmpty               =  GetValueChar("KEmpty","config.yaml", ' ');  // case vide de l'écran
    /*!
     * \brief Nombre de lignes de l'écran (de l'espace).
     */
    const unsigned KSizeLine   =  GetValueInt("KSizeLine","config.yaml", 10);   // Nombre de lignes de l'écran (de l'espace)

    /*!
     * \brief Nombre de colonnes de l'écran (de l'espace).
     */
    const unsigned KSizeSpace  =  GetValueInt("KSizeSpace","config.yaml", 10);   // Nombre de colonnes de l'écran (de l'espace)

    /*!
     * \brief Numéro de colonne où commence l'envahisseur.
     */
    const unsigned KBegInvader =  GetValueInt("KBegInvader","config.yaml", 0);    // Numéro de colonne où commence l'envahisseur

    /*!
     * \brief Numéro de colonne où commence le joueur.
     */
    const unsigned KBegMe      =  GetValueInt("KBegMe","config.yaml", 5);  // Numéro de colonne où commence le joueur

    // Constante liées au fonctionalité
    /*!
     * \var KBonus
     * \brief KBonus
     * Représentation des bonus
     */
    const char KBonus           = GetValueChar("KBonus","config.yaml", '*')!=KEmpty ? GetValueChar("KBonus","config.yaml", '*') : '*';

    /*!
     * \brief KRatio
     * Ratio d'apparition de bonus
     */
    const unsigned KRatio       = GetValueInt("KRatio","config.yaml", 60);

    /*!
     * \var KMur
     * \brief KMur
     * Représentation des Mur
     */
    const char KMur             = GetValueChar("KMur","config.yaml", '=')!=KEmpty ? GetValueChar("KMur","config.yaml", '=') : '=';

    /*!
     * \var KIntroSound
     * \brief KIntroSound
     * stock l'adresse vers la resource audio du programme ecouter aux début
     */
    const std::string KIntroSound = GetValueStr("KIntroSound", "config.yaml", "http://216.227.134.162/ost/space-invaders-gbc-gb-/xanousrrne/01-title-screen.mp3");

    /*!
     * \var KHistoSound
     * \brief KHistoSound
     * stock l'adresse vers la resource audio du programme écouter pendant les phases d'histoire
     */
    const std::string KHistoSound = GetValueStr("KHistoSound", "config.yaml", "http://cdn.frustra.org/sounds/sound/vo/core01/space21.mp3");

    /*!
     * \var KGameSound
     * \brief KGameSound
     * stock l'adresse vers la resource audio du programme écouter pendant le jeux
     */
    const std::string KGameSound = GetValueStr("KGameSound", "config.yaml", "http://216.227.134.162/ost/space-invaders-gbc-gb-/tmymegclzp/12-invader-homeworld.mp3");

    /*!
     * \var KEndSound
     * \brief KEndSound
     * stock l'adresse vers la resource audio du programme écouter à la fin en cas de victoire
     */
    const std::string KEndSound = GetValueStr("KEndSound", "config.yaml", "http://i1.theportalwiki.net/img/1/1e/Portal2-13-Want_You_Gone_RT.mp3");

    /*!
     * \var KGameOverSound
     * \brief KGameOverSound
     * stock l'adresse vers la resource audio du programme écouter lors d'une défaite
     */
    const std::string KGameOverSound = GetValueStr("KGameOverSound", "config.yaml", "http://216.227.134.162/ost/pokemon-yellow-blue-red-gb-/oacqzkmnml/01-opening-part-1-.mp3");
}//namespace
