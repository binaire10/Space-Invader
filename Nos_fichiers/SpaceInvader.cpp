/*!
  * \file SpaceInvader.cpp
  * \author Wery Tramier Vandecastle Tillier Ranaivosoa
  * \date 15 janvier 2016
  * \brief Projet de C++ simulant un SpaceInvader
  * \version 1.1
  * \bug Aucun connu
  */

#include <algorithm>
#include <iostream>
#include <fstream>
#include <cstdlib> //rand ()
#include <ctime> //time ()
#include <chrono>
#include <unistd.h> //read ()
#include <sstream>
#include <assert.h>
#include <QtMultimedia>
#include <QVector>
#ifndef __WIN32__
#include <termios.h>
#endif
#ifdef __WIN32__
#include <windows.h>
#endif

#include "MyType.h"
#include "SpaceInvader.h"
#include "MyConst.h"

using namespace std;
using namespace SpaceInvader_AC;
using namespace SpaceInvader;

template <typename T, typename U>
void ShowMap (const map <T, U>& MyMap)
{
    cout << string (20, '-') << endl;
    //for (unsigned i(0); i < MyMap.size(); ++i)
    //    cout << MyMap[i].first << " " << MyMap[i].second << endl;
    for (const auto & Elem : MyMap)
        cout << Elem.first << " " << Elem.second << endl;
    cout << string (20, '-') << endl;
}



namespace SpaceInvader
{
    //http://www.gnu.org/software/libc/manual/html_node/Noncanon-Example.html
    void set_input_mode (void)
    {
#ifndef __WIN32__
        struct termios tattr;

        /* Make sure stdin is a terminal. */
        if (!isatty (STDIN_FILENO))
        {
            fprintf (stderr, "Not a terminal.\n");
            exit (EXIT_FAILURE);
        }

        /* Set the funny terminal modes. */
        tcgetattr (STDIN_FILENO, &tattr);
        tattr.c_lflag &= ~(ICANON|ECHO); /* Clear ICANON and ECHO. */
        tattr.c_cc[VMIN] = 0;
        tattr.c_cc[VTIME] = 3;
        tcsetattr (STDIN_FILENO, TCSAFLUSH, &tattr);
#endif
    }

    void write(const string &Text, const unsigned &LineSize, const unsigned &uTime, const unsigned &LineBegin=0, const unsigned &ColumBegin=0);

    /**
     * @brief CleanScreen
     * Efface en dure l'écrant
     * @return
     */
    string CleanScreen() // Code Pour effacer l'écran
    {
        return "\033[H\033[2J";
    }

    string Reset() // Code pour réinitialiser la console
    {
        return "\033[0m";
    }

    /**
     * @brief GotoXY
     * Permet de déplacer le curseur
     * @param X
     * position X
     * @param Y
     * Poistion Y
     * @return
     */
    string GotoXY(unsigned X, unsigned Y)  // Code pour déplacer le prompt
    {
        return "\033[" + to_string(Y+1) + ";" + to_string(X) + "H";
    }

    /*!
     * \brief clearScreen
     * Fonction pour efacer une surface
     * \param X
     * position X
     * \param Y
     * Position Y
     */
    void clearScreen(unsigned X, unsigned Y) // code pour effacer de manière réaliste la console
    {
        cout << GotoXY(0,0);
        string EmptyLine(Y+1,' ');
        for(unsigned i(0) ; i<=X ; ++i)
            write(EmptyLine,Y+1,5000,i);
    }

    /**
     * @brief SetColor
     * fonction pour modifier la couleur du texte sur fond noir
     * @param ColorId
     * Couleur du texte
     * @return
     */
    string SetColor(unsigned ColorId) // code pour modifier la couleur du texte sur fond normal
    {
        assert(ColorId<10);
        return "\033[0;3" + to_string(ColorId) + "m";
    }

    /**
     * \brief SetColorAndBack
     * Fonction pour modifier la couleur de fond
     * \param ColorId
     * Couleur du texte
     * \param ColorBack
     * Couleur de fond
     * \return
     */
    string SetColorAndBack(unsigned ColorId, unsigned ColorBack) // code pour changer la couleur de fond et de texte
    {
        assert(ColorId<10);
        assert(ColorBack<10);
        return "\033[0;3" + to_string(ColorId)+";4"+to_string(ColorBack)+"m";
    }

    /*!
     * \brief PrintGameLine
     * Fonction pour afficher la grille de jeux
     * \param Line
     * Ligne à afficher
     */
    void PrintGameLine(const string &Line)
    {
        for(const char &CharLine : Line)
        {
            if(CharLine == KInsideInvader) // si le caractère à affficher est celui d'un invader alors on change la couleur
                cout << SetColor(KInvadersColor);
            else if(CharLine == KInsideMe) // si le caractère à affficher est celui du Joueur alors on change la couleur
                cout << SetColor(KMyColor);
            else
                cout << Reset(); // si non on réinitialise la couleur de fond
            cout << CharLine; // on affiche le caractère
        }
    }

    /*!
     * \brief write
     * permet d'écrire du texte sur la console à l'image d'un machine à écrire
     * \param Text
     * texte à écrire sur la console
     * \param LineSize
     * Longueur d'une ligne
     * \param uTime
     * temp en microseconde pour écrire
     * \param LineBegin
     * premier ligne ou écrire
     * \param ColumBegin
     * colone ou écrire
     */
    void write(const string &Text, const unsigned &LineSize, const unsigned &uTime, const unsigned &LineBegin, const unsigned &ColumBegin)
    {
        cout << GotoXY(ColumBegin,LineBegin);
        char alphaLast(0);
        unsigned line(0);
        for(unsigned i(0) ; i<Text.size() ; ++i)
        {
            const char &letter = Text[i];
            cout << letter << flush; // On force l'affichage du texte sans pour autant faire de retour à la ligne
            if((i+1)%LineSize ==0)
            {
                // si on revient à la ligne on déplace manuellement le prompt
                ++line;
                cout << GotoXY(ColumBegin,LineBegin+line);
                usleep(uTime*12/7);
            }
            if(isalnum(letter) && alphaLast!=letter)
                usleep(uTime); // Si ce n'est pas la même lettre que la dernière tappée, on attend.
            else if(letter==' ' && alphaLast!=letter)
                usleep(uTime*8/7); // Si c'est un espace ou un retour à la ligne on attend plus longtemps.

            if(alphaLast==letter)
                alphaLast = '\0';
            else
                alphaLast = letter; // on récupère la dernière lettre tappée.
        }
    }

    /*!
     * \brief resizeText
     * Fonction qui redimensione le nombre de mots par longueur de caractére
     * \param Text
     * texte à redimensionner
     * \param size
     * longeur de caractére
     * \return
     * chaine transformer
     */
    string resizeText(const string &Text, const unsigned &size)
    {
        string Word, Result;
        vector<string> Line;
        stringstream TextS(Text);
        while (TextS >> Word) // on place dans un Tableau les Mots
        {
            Word +=' ';// on ajoute un espace par mot
            Line.push_back(Word);
        }
        vector<string>::iterator PosWordBegin(Line.begin()), // premier mot dans la phrase
                PosWordEnd(Line.begin()); // dernier mot dans la phrase
        while(PosWordBegin!=Line.end())
        {
            unsigned sizeLine(0);
            while(sizeLine<=size && PosWordEnd!=Line.end())
            {
                sizeLine+=PosWordEnd->size(); // on mesure la supposée longueur jusqu'à ce que la longueur de la chaine soit trop longue
                ++PosWordEnd;
            }

            if(sizeLine>size)
            {
                if((PosWordBegin+1) != PosWordEnd) // si il y a plusieurs mots à afficher
                {
                    sizeLine -= (--PosWordEnd)->size(); // on retire le dernier mot à afficher
                }

                for(vector<string>::iterator i(PosWordBegin) ; i<PosWordEnd ; ++i)
                {
                    Result += *i; // on réassemble les mots entre
                }
            }
            else
            {
                for(vector<string>::iterator i(PosWordBegin) ; i<PosWordEnd ; ++i)
                {
                    Result += *i; // on réassemble les mots entre
                }
            }
            if(Result.size()%size!=0) // si la longueur de la nouvelle ligne n'est pas conforme
                Result += string(size-(Result.size()%size),' '); // on comble d'espaces pour la rendre conforme
            PosWordBegin = PosWordEnd; // on recommence à partir de Pos WordEnd
        }
        assert(Result.size()%size == 0); // on controle que les phrases soient conformes
        return Result; // on retourne le resultat
    }

    /*!
     * \brief ManageScenar
     * gére l'avancer dans l'histoire du joueur
     * \param Level
     * niveau du joueur
     */
    void ManageScenar ( const unsigned &Level )
    {
        cout << GotoXY(0,0); // on place le curseur au début

        // différentes chaines de texte qui constituent le scénario
        const string KStrIntroduction = "Cela faisait maintenant 2 jours que le drame s'etait produit. Johnny, bien decide a faire payer les coupables, "
                                        "acheta un vaisseau a un vieil ami. C'etait l'heure de la revanche.";

        const string KStrLevel2 ="4 jours depuis le drame. Johnny avancait peniblement au milieu des hordes ennemies, en cette douce matinee d'hiver,"
                                 " il entendit au loin les tirs raisonner au fin fond du vide de l'espace. Mais Johnny etait deja pret. ";

        const string KStrLevel3 ="8 jours depuis le drame. Johnny recuperait sur Pandore, planete tellurique riche en oxygene de la voie lactee de la Bulle Savonneuse, "
                                 "un droide du nom de C6R4. Meme si il n'était qu'une IA, ils avaient la meme philosophie de vie suite au drame qui a bouleverse la vie "
                                 "dans l'univers il y avait maintenant 8 jours.";

        const string KStrLevel4 ="10 jours depuis le drame. Johnny commencait a s'interroger sur le but de sa quete, y aura - t - il un jour une fin a cette guerre ? "
                                 "Pourrons-nous un jour nous entendre à nouveau ? Ces questions rongeaient Johnny au plus profond de son etre..";

        const string KStrLevel5 ="12 jours depuis le drame. C'est fini, la musique de la marche imperiale se fait entendre du fond de l'etoile robotisee dans laquelle Johnny est enferme"
                                 "Lorsque tout espoir disparut aux yeux de Johnny, C6R4 surgit et le libéra. Ils dérobèrent un X-Zwim dans le hangar de l'empire. "
                                 "C'etait l'heure du dernier combat. Ils allaient payer pour avoir aime Star Wars 7.";
        switch (Level) // niveau atteint par le joueur
        {
        case 0:
            write(resizeText(KStrIntroduction,60), 60 ,50000);
            break;
        case 1:
            write(resizeText(KStrLevel2,60), 60 ,50000);
            break;
        case 2:
            write(resizeText(KStrLevel3,60), 60 ,50000);
            break;
        case 3:
            write(resizeText(KStrLevel4,60), 60 ,50000);
            break;
        case 4:
            write(resizeText(KStrLevel5,60), 60 ,50000);
            break;
        }
        sleep(3);// on attend 3 secondes
        clearScreen(25,60);// on efface le texte
    }

    /*!
     * \brief MoveTo
     * déplace les objets du From ver le To. Si une colision à lieu les 2 son effacer
     * \param From
     * Position de l'objet qui veux se déplacer
     * \param To
     * Destination de l'objet
     * \return
     * Retourne le caractére qui était sur le to
     */
    char MoveTo(string::iterator &From, string::iterator &To)
    {
        char LastValueTo(*To); // on sauve la valeur d'origine stockée dans To
        if(*To!=KEmpty)
            *To = KEmpty;  // si la destination n'est pas vide on l'efface
        else
            *To = *From; // si elle est vide alors on déplace le contenu de From
        *From = KEmpty; // On affecte KEmpty à la position d'origine
        return LastValueTo;
    }

    /*!
     * \brief initSpace
     * On initialise l'espace de jeux, on positione les joueur
     * \param Space
     * L'espace de jeux
     * \param MyPos
     * Position du joueur
     * \param InvaderLine
     * Position de L'invader
     */
    void initSpace(CVString &Space, unsigned MyPos, unsigned InvaderLine)
    {
        srand (time(NULL));
        Space = CVString(KSizeSpace,string(KSizeLine, KEmpty)); // initialise la grille avec KEmpty
        for(unsigned i(0) ; i < KInvadersSize ; ++i)
            Space[0 + InvaderLine][i] = KInsideInvader; // Place l'invader

        Space[Space.size()-1][MyPos] = KInsideMe; // place le joueur
    }

    /*!
     * \brief WinTest
     * Test si le joueur à gagner
     * \param Space
     * Espace de jeux
     * \param Line
     * Ligne ou se trouve l'invader
     * \return
     * Vrai si victoire
     */
    bool WinTest(CVString &Space, const unsigned &Line)
    {
        const string &InvaderLine(Space[Line]);
        return find(InvaderLine.begin(), InvaderLine.end(), KInsideInvader)==InvaderLine.end(); // On cherche si l'invader existe encore
    }

    /*!
     * \brief LoseTest
     * test si le joueur à perdue
     * \param Space
     * Espace de jeux
     * \param Line
     * Ligne ou se trouve le joueur
     * \return
     * revois vrai si le joueur à était éliminer
     */
    bool LoseTest(CVString &Space, const unsigned &Line)
    {
        string &MyLine(Space[Line]);
        return find(MyLine.begin(), MyLine.end(), KInsideMe)==MyLine.end(); // On cherche si le joueur existe encore
    }

    /*!
     * \brief ManageInvaderMove
     * Déplace l'invader
     * \param Space
     * Espace de jeux
     * \param Increment
     * Donne le sens de déplacement du joueur
     * \param CurrentLine
     * Ligne de l'invader
     * \param Beg
     * Position de l'invader sur la ligne
     */
    void ManageInvaderMove(CVString &Space, bool &Increment, unsigned &CurrentLine, unsigned &Beg)
    {
        string &currentLine = Space[CurrentLine];// on récupère la derniere ligne pour un accés rapide

        if(Increment == false && currentLine[0] == KInsideInvader) // si l'invader est en début de ligne
        {
            Increment = true; // on change de sens de déplacement
            string &futureLine = Space[++CurrentLine];
            for(string::iterator i(currentLine.begin()), j(futureLine.begin()) ; i!=currentLine.end() && j!=futureLine.end() ; ++i, ++j)
                if(*i == KInsideInvader)
                {
                    if(*j   ==  KTorpedo) // si la destination est une torpille
                    {
                        *i = KEmpty; // on efface les deux objets
                        *j = KEmpty;
                    }
                    else
                    {
                        *j = *i;
                        *i = KEmpty; // sinon on déplace l'invader
                    }
                }
            return; // On finit le tour de l'invader
        }
        else if(Increment == true && currentLine[currentLine.size()-1] == KInsideInvader)
        {
            string &futureLine = Space[++CurrentLine];
            Increment = false;
            for(string::iterator i(currentLine.begin()), j(futureLine.begin()) ; i!=currentLine.end() && j!=futureLine.end() ; ++i, ++j)
                if(*i == KInsideInvader)
                {
                    if(*j   ==  KTorpedo) // si la destination est une torpille
                    {
                        *i = KEmpty; // on efface les deux objets
                        *j = KEmpty;
                    }
                    else
                    {
                        *j = *i;
                        *i = KEmpty; // sinon on déplace l'invader
                    }
                }
            return; // On finit le tour de l'invader
        }

        if(Increment) // selon qu'on incrémente ou décrémente on déplace l'invader
        {
            for(string::iterator i(currentLine.end()-1), j(currentLine.end()) ; j!=currentLine.begin() ; --i,--j) // on parcoure toute la ligne
            {
                if(*i == KInsideInvader) // si l'élément actuel est l'invader
                {
                    if(*j   ==  KTorpedo) // si la destination est une torpille
                    {
                        *i = KEmpty; // on efface les deux objets
                        *j = KEmpty;
                    }
                    else
                    {
                        *j = *i;
                        *i = KEmpty; // sinon on déplace l'invader
                    }
                }
            }
        }
        else
        {
            for(string::iterator i(currentLine.begin()), j(currentLine.begin()+1) ; j!=currentLine.end() ; ++i, ++j) // on parcoure toute la ligne
            {
                if(*j == KInsideInvader) // si l'élément actuel est l'invader
                {
                    if(*i   ==  KTorpedo) // si la destination est un torpille
                    {
                        *i = KEmpty;
                        *j = KEmpty; // on efface les 2 objets
                    }
                    else
                    {
                        *i = *j; // sinon on déplace L'invader
                        *j = KEmpty;
                    }
                }
            }
        }

        Beg = find(currentLine.begin(),currentLine.end(), KInsideInvader) - currentLine.begin(); // on repositione la variable Beg sur l'invader
    }

    /*!
     * \brief ManageInvaderShoot
     * Fonction qui fait tirée l'invader
     * \param Space
     * Espace de jeux
     * \param CurrentLine
     * Ligne de l'invader
     * \param Beg
     * Position de l'invader
     * \param MyLife
     * Vie Du Joueur
     */
    void ManageInvaderShoot(CVString & Space, unsigned &CurrentLine, unsigned &Beg, unsigned &MyLife)
    {
        string SMisile(1,KMissile); // origine du missile (lance missile)
        unsigned pos(rand()%KInvadersSize); // generation aleatoire de la position où le missile va apparaitre
        string &ShootLine = Space[CurrentLine+1]; // racourci vers la ligne de tire
        while(Space[CurrentLine][pos + Beg] != KInsideInvader && !WinTest(Space, CurrentLine))
            pos = (pos+1)%KInvadersSize; // tant que le missile n'est pas en face d'un invader
        string::iterator dest(ShootLine.begin()+ pos + Beg); // destination du missile
        string::iterator from(SMisile.begin()); // origine
        if(MoveTo(from, dest) == KInsideMe) // déplacement du Missile
        {
            --MyLife; // Si le Missile apparait sur le joueur on l'élimine
            if(MyLife != 0)
                *dest = KInsideMe;
        }
    }

    /*!
     * \brief ManageMe
     * Controle Le joueur
     * \param Space
     * Espace de jeux
     * \param MyPos
     * Position du joueur
     * \param FireWait
     * Nombre de tour à attendre avant de pouvoir  tiré
     * \param MyLife
     * Nombre de Vie Restant
     */
    void ManageMe (CVString & Space, unsigned &MyPos, int &FireWait, unsigned &MyLife)
    {
        string &CurrentLine = Space[Space.size()-1];
        char Move;
        //fonction en C qui permet de lire un caractère. cin ne fonctionnant pas dans cette configuration
#ifdef __WIN32__  // Support Multi Platform
        // lecture de touche windows
        Move = '\0';
        Move = GetKeyState(toupper(KRight))&0x8000 ? KRight : Move;
        if(Move == '\0')
        {
            Move = GetKeyState(toupper(KLeft))&0x8000 ? KLeft : Move;
        }
        if(Move == '\0')
        {
            Move = GetKeyState(toupper(KShoot))&0x8000 ? KShoot : Move;
        }
#else
        // lecteur de touche linux et mac
        char Buf;
        for(unsigned i(read (STDIN_FILENO, &Move, 1)+1) ; i!=0 ; --i)
            read (STDIN_FILENO, &Buf, 1);
#endif
        if(Move==KLeft)
        { // Si on se déplace à gauche
            if(MyPos != 0)// on verifie qu'on ne soit pas trop à gauche
            {
                if(CurrentLine[MyPos-1] == KBonus)
                {
                    unsigned Bonus;
                    Bonus = rand()%3; // on choisi un bonus au hazard
                    switch(Bonus)
                    {
                    case 0:
                        ++MyLife; // on incrémente sa vie
                        break;
                    case 1:
                        Score += 500; // on augmente son score
                        break;
                    case 2:
                        *j = KMur; // on place un Murt devant le joueur
                        break;
                    default: // sinon rien
                        break;
                    }
                }
                if(CurrentLine[MyPos-1] == KMissile && MyLife!=0) // si on se déplace sur un missile
                    --MyLife; // on décrémente 
                if(MyLife==0) // si le joueur est mort on l'efface
                    CurrentLine[MyPos] = KEmpty;
                else
                    swap(CurrentLine[MyPos], CurrentLine[MyPos-1]); // on échange les positions entre elles
                --MyPos;// on décremente la position
            }
        }
        else if(Move==KRight)
        { // Si on se déplace à droite
            if((MyPos+1) != CurrentLine.size())
            {
                if(CurrentLine[MyPos+1] == KBonus)
                {
                    unsigned Bonus;
                    Bonus = rand()%3; // on choisi un bonus au hazard
                    switch(Bonus)
                    {
                    case 0:
                        ++MyLife; // on incrémente sa vie
                        break;
                    case 1:
                        Score += 500; // on augmente son score
                        break;
                    case 2:
                        *j = KMur; // on place un Murt devant le joueur
                        break;
                    default: // sinon rien
                        break;
                    }
                }
                if(CurrentLine[MyPos+1] == KMissile && MyLife!=0)
                    --MyLife; // si l'invader se déplace sur un missile
                if(MyLife==0)
                {
                    CurrentLine[MyPos] = KEmpty; // si l'invader est mort
                }
                else
                    swap(CurrentLine[MyPos], CurrentLine[MyPos+1]); // on échange les positions entre elles
                ++MyPos; // on incremente la position
            }
        }
        else if(Move==KShoot && FireWait==0) // le joueur ne peut tirer qu'une fois si le FireWait null
        {
            Space[Space.size()-2][MyPos] = KTorpedo; // on place la torpille devant le joueur
            FireWait = KFireWait;
        }
        if(FireWait != 0) // si le temps d'attente n'est pas null
            --FireWait;
    }// ManageMe ()

    /*!
     * \brief ManageMissileAndTorpedo
     * Controle la physique de déplacement d'objet telle que des missile
     * \param Space
     * \param InvaderCount
     * \param MyLife
     * Nombre de vie restant au joueur
     * \param Score
     * Score du joueur
     */
    void ManageMissileAndTorpedo(CVString &Space, unsigned &InvaderCount, unsigned &MyLife, int &Score)
    {
        string &FirstLine = Space[0]; // Alias vers la ligne de départ
        string &LastLine = Space[Space.size()-1]; // alias vers la derniere ligne

        for(char &Val : FirstLine) // on efface toute les torpilles sur la premiere ligne
            if(Val == KTorpedo)
                Val = KEmpty;

        for(char &Val : LastLine) // on efface les Missiles sur la derniere ligne
            if(Val == KMissile)
                Val = KEmpty;

        for(char &Val : LastLine) // on efface les Bonnus sur la dernier ligne
            if(Val == KBonus)
                Val = KEmpty;

        vector<string::iterator> DontMoveIt; // On stock ici l'emplacement des objets déja déplacés

        for(CVString::iterator i(Space.begin()), z(Space.begin()+1) ; z!=Space.end() ; ++i, ++z) // i représente la premiere ligne j la deuxiéme de façon à ce que les missiles aillent de i ver z et les torpilles de j ver i
        {
            for(string::iterator j(i->begin()), k(z->begin()) ; j!=i->end() ; ++j, ++k) // j et k sont la même colone
            {
                // ici on déplacé les torpilles
                if(*k == KTorpedo && find(DontMoveIt.begin(), DontMoveIt.end(), k)==DontMoveIt.end()) // si la torpille n'a pas encore bougé
                {
                    if(MoveTo(k, j) == KInsideInvader) // on la déplace
                        --InvaderCount; // si on touche un invader on décompte le nombre d'invaders restant
                    DontMoveIt.push_back(j);// on l'ajoute à la liste des objets à ne pas déplacer
                }

                // ici on s'occupe de déplacer les Missiles
                if(*j == KMissile && find(DontMoveIt.begin(), DontMoveIt.end(), j)==DontMoveIt.end()) // si il n'est pas dans la liste on ne le déplace pas
                {
                    if(MoveTo(j, k) == KInsideMe)
                    { // si il touche un joueur on décrémente le nombre de vies du joueur
                        --MyLife;
                        if(MyLife != 0)
                            *k = KInsideMe;
                    }
                    DontMoveIt.push_back(k); // on l'ajoute à la liste d'objets a ne pas déplacer
                }

                // si c'est un bonus
                if(*j == KBonus && find(DontMoveIt.begin(), DontMoveIt.end(), j)==DontMoveIt.end()) // on verifie qu'il n'a pas déjà bougé
                {
                    if(MoveTo(j, k) == KInsideMe) // si lors du déplacement il touche le joueur on l'élimine
                    {
                        *k = KInsideMe; // on replace le joueur effacé lors de la collision avec le bonus
                        unsigned Bonus;
                        Bonus = rand()%3; // on choisi un bonus au hazard
                        switch(Bonus)
                        {
                        case 0:
                            ++MyLife; // on incrémente sa vie
                            break;
                        case 1:
                            Score += 500; // on augmente son score
                            break;
                        case 2:
                            *j = KMur; // on place un Murt devant le joueur
                            break;
                        default: // sinon rien
                            break;
                        }
                    }
                    DontMoveIt.push_back(k); // on l'ajoute à la liste des objets dejà déplacés
                }
            }
        }
    }

    /*!
     * \brief ManageBonus
     * Fait apparaitre un bonus
     * \param Space
     * Espace de jeux
     * \param LineInvader
     * Ligne ou se trouve l'invader
     */
    void ManageBonus(CVString &Space, const unsigned &LineInvader)
    {
		unsigned NBalea = rand()%100;
		if (NBalea <= KRatio)
            Space[LineInvader+1][rand()%KSizeLine] = KBonus; // on place un bonus
    }

    /*!
     * \brief MainFont
     * Fonction qui affiche un invader
     * \param EyeColor
     * Definit la couleur des yeux
     * \param BodyColor
     * Definit la couleur du corp
     * \param BackGroundColor
     * Definit la couleur de fond
     */
    void MainFont(const unsigned &EyeColor = KRouge, const unsigned &BodyColor = KNoir, const unsigned &BackGroundColor = KVert)
    {
        cout << GotoXY(0,0); // on déplace le prompt à la position 0,0
        string ColorBody  (SetColorAndBack(BodyColor, BodyColor));
        string ColorEye (SetColorAndBack(EyeColor, EyeColor));
        string ColorBackBody (SetColorAndBack(BackGroundColor, BodyColor));
        string ColorBackground (SetColorAndBack(BackGroundColor, BackGroundColor));
        string Picture ("MMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMM\n"
                        "MMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMM\n"
                        "MMMMMMMMMMMMMMM   MMMMMMMMMMMMMMMMMMM    MMMMMMMMMMMMMMMMMMM\n"
                        "MMMMMMMMMMMMMMM   MMMMMMMMMMMMMMMMMMM    MMMMMMMMMMMMMMMMMMM\n"
                        "MMMMMMMMMMMMMMMMMM.   MMMMMMMMMMM.   MMMMMMMMMMMMMMMMMMMMMMM\n"
                        "MMMMMMMMMMMMMMMMMM    MMMMMMMMMMM    MMMMMMMMMMMMMMMMMMMMMMM\n"
                        "MMMMMMMMMMMMMMMMMM    MMMMMMMMMMM    MMMMMMMMMMMMMMMMMMMMMMM\n"
                        "MMMMMMMMMMMMMMM                          MMMMMMMMMMMMMMMMMMM\n"
                        "MMMMMMMMMMMMMMM                          MMMMMMMMMMMMMMMMMMM\n"
                        "MMMMMMMMMMM       XXXX           XXXX        MMMMMMMMMMMMMMM\n"
                        "MMMMMMMMMMM       XXXX           XXXX        MMMMMMMMMMMMMMM\n"
                        "MMMMMMMMMMM       XXXX           XXXX        MMMMMMMMMMMMMMM\n"
                        "MMMMMMM                                         MMMMMMMMMMMM\n"
                        "MMMMMMM                                         MMMMMMMMMMMM\n"
                        "MMMMMMM    MMMM                          MMMM   MMMMMMMMMMMM\n"
                        "MMMMMMM    MMMM                          MMMM   MMMMMMMMMMMM\n"
                        "MMMMMMM    MMMM   MMMMMMMMMMMMMMMMMMM    MMMM   MMMMMMMMMMMM\n"
                        "MMMMMMM    MMMM   MMMMMMMMMMMMMMMMMMM    MMMM   MMMMMMMMMMMM\n"
                        "MMMMMMM   .MMMM   MMMMMMMMMMMMMMMMMMM   .MMMM   MMMMMMMMMMMM\n"
                        "MMMMMMMMMMMMMMMMMM        MMMM       MMMMMMMMMMMMMMMMMMMMMMM\n"
                        "MMMMMMMMMMMMMMMMMM        MMMM       MMMMMMMMMMMMMMMMMMMMMMM\n"
                        "MMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMM\n"
                        "MMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMM\n"
                        "MMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMM\n"
                        "MMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMM\n");

        for(string::iterator i(Picture.begin()) ; i != Picture.end() ; ++i)
        {
            if(*i==' ') // on définit la couleur pour chaque espace
                cout << ColorBody;
            else if(*i=='X') // on définit la couleur pour les yeux
                cout << ColorEye;
            else if(*i=='.') // on définit la couleur d'une partie du corps de l'invader
                cout << ColorBackBody;
            else if(*i=='M') // on définit la couleur du fond de l'invader
                cout << ColorBackground;
            else
                cout << Reset(); // sinon on réinitialise la console
            cout << *i;
            usleep(5000); // on attend quelques minisecondes
        }
        cout << Reset() << flush; // on réinitialise la console
        sleep(2); // on laisse l'image quelques secondes
        clearScreen(25,60); // on efface l'écran de manière spéciale
    }

    /*!
     * \brief Run
     * Programe principale du jeux
     */
    void Run()
    {
        QThread Thread; // on crée un objet QThread pour le Timer de QMediaPlayer
        QMediaPlayer player; // on crée un lecteur de Musique
        player.moveToThread(&Thread); // on le place dans le Thread
        player.setVolume(50); // on modifie le volume
        QVector<QUrl> playlist; // on affecte une playlist d'URL

        playlist.push_back(QUrl(QString::fromStdString(KIntroSound)));
        playlist.push_back(QUrl(QString::fromStdString(KEndSound)));
        playlist.push_back(QUrl(QString::fromStdString(KGameOverSound)));
        playlist.push_back(QUrl(QString::fromStdString(KHistoSound)));
        playlist.push_back(QUrl(QString::fromStdString(KGameSound)));

        player.setMedia(playlist[0]);
        player.play(); // On joue la musque d'introduction au jeux

        srand (time(NULL));
        set_input_mode();
        MainFont(); // On affiche un Invader
        CVString Space; // On crée la variable qui est la grille de jeux
        int FinalScore(0); // variable qui stock le score
        unsigned Level(0); // variable qui stock le niveau atteint par le joueur
        for( ; Level<5 && (Level==0 || !LoseTest(Space, Space.size()-1)) ; ++Level)
        {
            unsigned PosInvader(KBegInvader), PosMe(KBegMe); // Variable stockant la position de l'invader et du joueur
            unsigned LineInvader(0); // ligne de l'invader
            unsigned FirstInvaderCount (KInvadersSize);  // Compteur du nombre d'invaders restant
            if(Level>2)
                FirstInvaderCount = KInvadersSize*2/3;
            unsigned PlayerLife (KMyLife); // Variable stockant la vie du joueur
            int Score(0); // score du joueur
            bool Increment(true); // variable qui donne le sens de déplacement de l'invader
            int FireWait(0); // Variable evitant que le joueur puisse tiré rapidement
            initSpace(Space, PosMe, LineInvader); // Variable initialisant
            cout << CleanScreen(); // on efface l'écran pour rafraichir l'image

            player.stop();
            player.setMedia(playlist[3]); // on joue la musique de scenario
            player.play();

            ManageScenar(Level); // démarage de l'affichage du scénario

            player.stop();
            player.setMedia(playlist[4]); // a la fin du scenario on lance la musique de jeux
            player.play();

            cout << CleanScreen(); // on efface l'écran
            unsigned Turn(0); // nombre de tours écoulés
            while(!WinTest(Space, LineInvader) && !LoseTest(Space, Space.size()-1)) // on boucle tan que le joueur ou l'invader n'a pas gagne ou qu'il soit arrive sur la dernier ligne
            {
                Score -= 10; // on decremente le score à chaque tours de l'invader


                for(unsigned i(0) ; i<KRatioMeInvaders &&  (!WinTest(Space, LineInvader) && !LoseTest(Space, Space.size()-1)); ++i, ++Turn) // boucle pour equilibré le ration
                {
                    unsigned LastInvaderCount (FirstInvaderCount); // on sauvegarde le nombre d'invaders avant de faire se déplacer les missile

                    ManageMissileAndTorpedo(Space, FirstInvaderCount, PlayerLife, Score);

                    if(LastInvaderCount != FirstInvaderCount) // si il manque un ou plusieurs invaders on incrémente le score et on fait apparaitre un bonus
                    {
                        ManageBonus(Space, LineInvader);
                        Score += 100;
                    }

                    if(Turn%KMissileRatio == 0) // on respecte un ratio pour les tirs de missile
                        ManageInvaderShoot(Space, LineInvader, PosInvader, PlayerLife);

                    chrono::high_resolution_clock::time_point t1 = chrono::high_resolution_clock::now(); // on recupère le temps de début
                    ManageMe(Space, PosMe, FireWait, PlayerLife); // on donne le tour au joueur
                    cout << GotoXY(0,0) << "\t\t\t" << SetColorAndBack(KNoir, KRouge) << string(KSizeLine+2,'-') << Reset() << endl; // place le haut de la grille
                    for(const string &Line : Space)
                    {
                        cout << "\t\t\t" << SetColorAndBack(KNoir, KRouge) << '|' << Reset(); // on affiche la grille de jeux
                        PrintGameLine(Line);
                        cout << SetColorAndBack(KNoir, KRouge) << '|' << Reset() << endl;
                    }
                    cout << "\t\t\t" << SetColorAndBack(KNoir, KRouge) << string(KSizeLine+2,'-') << Reset() << endl;
                    cout << SetColorAndBack(KCyan, KRouge) << resizeText("             Score : " + to_string(Score) + " Player Life : " + to_string(PlayerLife), 60) << Reset() << endl; // afficher les info du jeux
                    cout << SetColorAndBack(KCyan, KRouge) << resizeText("   FinalScore : " + to_string(Score + FinalScore) + " Invader Count : " + to_string(FirstInvaderCount),60)<< Reset() << endl;
                    chrono::high_resolution_clock::time_point t2 = chrono::high_resolution_clock::now();
                    auto duration = chrono::duration_cast<chrono::microseconds>( t2 - t1 ).count(); // on fait la différence pour eviter que le jeux aille trop vite
                    if(duration<350000)
                        usleep(350000-duration); // on attend que le temps manquant ce soit écoulé
                }
                if(player.state() != QMediaPlayer::PlayingState) // si la musique s'arrete on la relance
                    player.play();

                ManageInvaderMove(Space, Increment,  LineInvader, PosInvader); // on déplace l'invader
            }
            if(PlayerLife==0)
            {

                player.stop();
                player.setMedia(playlist[2]); // on joue la musique de game over
                player.play();

                MainFont(KNoir,KRouge, KNoir); // image de game over
            }
            FinalScore += Score;
            if(Level == 4)
            {
                player.stop();
                player.setMedia(playlist[1]); // musique de victoire
                player.play();
                MainFont(KNoir,KVert, KNoir); // image de victoire
                cout << "Score Final "<< FinalScore; // affichage du score final

            }
        }
    }
}
