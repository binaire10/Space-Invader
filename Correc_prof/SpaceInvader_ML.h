#pragma once

#include "MyType_ML.h"
namespace SpaceInvaderML
{
    /*!
    * \fn Colour
     * \param[in] Coul couleur du texte
     * \brief Fonction permettant de changer la couleur du texte.
     */
    void Colour (const std::string & Coul);

    /*!
     * \fn ClearScreen
     * \brief Fonction effaçant le contenu de l'écran
     */
    void ClearScreen ();

    /*!
     * \brief Descend l'envahisseur d'une ligne dans l'espace
     * \param [in, out] Space état de l'espace
     * \param [in] CurrentLine ligne sur laquelle se trouve l'e belligérant concerné'envahisseur.
     */
    void DownShift (CVString & Space, Size_t CurrentLine);

    /*!
     * \brief Renvoie vrai si le belligérant meurt.
     * \param [in] Space état de l'espace
     * \param [in] Line ligne sur laquelle se trouve le belligérant concerné.
     * \param [in] Column colonne sur laquelle se trouve le belligérant concerné.
     * \param [in, out] Who qui est concerné.
     */
    bool IsDead (const CVString & Space, Size_t Line, Size_t Column, char Who);

    /*!
     * \brief Simule le tir d'un belligérant. Renvoie vrai si le belligérant a gagné (faux sinon).
     * \param [in, out] Space état de l'espace
     * \param [in] Line ligne sur laquelle se trouve le tireur.
     * \param [in] Middle colonne du tir.
     * \param [in] Projectile projectile à  lancer (torpille ou missile).
     * \param [in] Who qui tire.
     */
    bool Shoot (CVString & Space, Size_t Line, Size_t Middle,
                char Projectile, char Who);

    /*!
     * \brief Simule le jeu de l'envahisseur. C'est ici que l'envahisseur joue. En bout de ligne l'envahisseur descend d'une ligne et change de sens.
     * Il tire également une fois sur 2. Renvoie vrai si l'envahisseur a gagné (faux sinon).
     * \param [in, out] Increment -1 ou 1 suivant que l'nvahisseur va à  gauche ou à  droite
     * \param [in, out] CurrentLine ligne sur laquelle se déplace l'envahisseur.
     * \param [in, out] Beg colonne où est positionné l'envahisseur.
     * \param [in, out] ToShoot indique si l'envahisseur doit tirer.
     * \param [in, out] Win indique si le joueur a gagné.
     * \param [in, out] Space état de l'espace
     */
    bool ManageInvader (int & Increment, Size_t & CurrentLine,
                        Size_t & Beg, bool & ToShoot,
                        bool & Win, CVString & Space);

    /*!
    * \brief enlève de l'espace le belligérant qui a perdu.
    * \param [in, out] Space Espace de jeu
    * \param [in] Line indique la ligne sur laquelle se trouve le belligérant à  supprimer
    * \param [in] Column indique la colonne à  partir de laquelle il faut supprimer
    */
    void Remove (CVString & Space, Size_t Line, Size_t Column);

    /*!
     * \brief recalcule l'espace (déplacement des torpilles et des missiles) à  chaque fois qu'un belligérant a joué.
     * \param [in, out] Space Espace de jeu
     * \param [in, out] Win  indique si le joueur a gagné
     * \param [in, out] Lost  indique si le joueur a perdu
     */
    void RecomputeSpace (CVString & Space, bool & Win, bool & Lost);


    /*!
     * \brief Permet d'afficher l'espace de jeu.
     * \param [in] Space Espace de jeu
     */
    void DisplaySpace (const CVString & Space);

    /*!
     * \brief Simule le jeu du joueur. C'est ici que le joueur choisit ce qu'il fait. S'il décide de tirer, une tropille est lancée, d'une position au hasard,
     * au dessus d'une de ses positions. Renvoie vrai si le joueur a gagné (faux sinon).
     * \param [in, out] Space Espace de jeu
     * \param [in, out] Pos   position du joueur sur sa ligne
     * \param [in, out] Lost  indique si le joueur a perdu
     */
    bool ManageMe (CVString & Space, Size_t & Pos, bool & Lost);

    /*!
     * \brief simule le jeux
     * <ol>
     *     <li>
     *         Déclare la grille de jeux
     *     </li>
     *     <li>
     *         L'initialise
     *     </li>
     *     <li>
     *         L'affiche
     *     </li>
     *     <li>
     *         boucle dont on sortira quand le joueur aura perdu ou gagné
     *         <ul>
     *             <li>
     *                 joue pour le joueur
     *             </li>
     *             <li>
     *                 recalcule l'espace si le joueur n'a ni gagné ni perdu
     *             </li>
     *             <li>
     *                 affiche l'espace
     *             </li>
     *             <li>
     *                 sort de la boucle en cas de victoire ou de défaite
     *             </li>
     *             <li>
     *                 réitère ces 4 opérations KRatioMeInvaders fois
     *             </li>
     *             <li>
     *                 sort de la boucle en cas de victoire ou de défaite
     *             </li>
     *             <li>
     *                 joue pour l'e joueur'envahisseur
     *             </li>
     *             <li>
     *                 recalcule l'espace si l'e joueur'envahisseur n'a ni gagné ni perdu
     *             </li>
     *             <li>
     *                 affiche l'espace
     *             </li>
     *             <li>
     *                 sort de la boucle en cas de victoire ou de défaite
     *             </li>
     *         </ul>
     *     </li>
     *     <li>
     *         affiche le résultat
     *     </li>
     * </ol>
     */
    void SpaceInvaders (void);
}
