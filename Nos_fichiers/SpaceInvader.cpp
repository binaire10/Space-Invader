/*!
  * \file SpaceInvader.cpp
  * \author Alain Casali Marc Laporte
  * \date 15 janvier 2016
  * \brief Projet de C++ simulant un SpaceInvader
  * \version 1.0
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
#include <termio.h>
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

    void write(const string &Text, const unsigned &LineSize, const unsigned &uTime);

    string CleanScreen()
    {
        return "\033[H\033[2J";
    }

    string Reset()
    {
        return "\033[0m";
    }

    string gotoXY(unsigned X, unsigned Y)
    {
        return "\033[" + to_string(X+1) + ";" + to_string(Y) + "H";
    }

    void clearScreen(unsigned X, unsigned Y)
    {
        cout << gotoXY(0,0);
        string EmptyLine(Y+1,' ');
        for(unsigned i(0) ; i<=X ; ++i)
            write(EmptyLine,Y+1,10000);
    }

    string SetColor(unsigned ColorId)
    {
        assert(ColorId<10);
        return "\033[0;3" + to_string(ColorId) + "m";
    }

    string SetColorAndBack(unsigned ColorId, unsigned ColorBack)
    {
        assert(ColorId<10);
        return "\033[0;3" + to_string(ColorId)+";4"+to_string(ColorBack)+"m";
    }

    void PrintGameLine(const string &Line)
    {
        for(const char &CharLine : Line)
        {
            if(CharLine == KInsideInvader)
                cout << SetColor(KInvadersColor);
            else if(CharLine == KInsideMe)
                cout << SetColor(KMyColor);
            else
                cout << Reset();
            cout << CharLine;
        }
    }

    void write(const string &Text, const unsigned &LineSize, const unsigned &uTime)
    {
        char alphaLast(0);
        for(unsigned i(0) ; i<Text.size() ; ++i)
        {
            if((i%LineSize+1)==LineSize)
            {
                cout << endl;
                usleep(uTime*12/7);
            }
            const char &letter = Text[i];
            cout << letter << flush; // On force l'affichage du texte sans pour autant faire de retour à la ligne
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

    string resizeText(const string &Text, const unsigned &size)
    {
        string Word, Output;
        vector<string> Line;
        stringstream TextS(Text);
        while (TextS >> Word) // on place dans un Tableau les Mots
        {
            Word +=' ';// on ajoute un espace par mots
            Line.push_back(Word);
        }
        unsigned PosWordBegin(0), PosWordEnd(0);
        while(PosWordBegin<Line.size())
        {
            unsigned sizeLine(0);
            while(sizeLine<=size && PosWordEnd<Line.size())
                sizeLine+=Line[PosWordEnd++].size();

            if(sizeLine>size)
            {
                if((PosWordBegin+1) != PosWordEnd)
                    sizeLine -= Line[--PosWordEnd].size();

                for(unsigned i(PosWordBegin) ; i<PosWordEnd ; ++i)
                {
                    Output += Line[i];
                }
            }
            else
            {
                for(unsigned i(PosWordBegin) ; i<PosWordEnd ; ++i)
                {
                    Output += Line[i];
                }
            }
            if(Output.size()%size!=0)
                Output += string(size-(Output.size()%size),' ');
            PosWordBegin = PosWordEnd;
        }
        assert(Output.size()%size == 0);
        return Output;
    }

    void ManageScenar ( const unsigned &Level )
    {
        cout << gotoXY(0,0);
        const string KStrIntroduction = "Cela faisait maintenant 2 jours que le drame s'etait produit. Johnny, bien decide a faire payer les coupables, "
                                        "acheta un vaisseau a un vieil ami. C'etait l'heure de la revanche.";
        const string KStrLevel2 ="4 jours depuis le drame. Johnny avancait peniblement au milieu des hordes ennemies, en cette douce matinee d'hiver,"
                                 " il entendit au loin les tirs raisonner au fin fond du vide de l'espace. Mais Johnny etait deja pret. ";
        const string KStrLevel3 ="8 jours depuis le drame. Johnny recuperait sur Pandore, planete tellurique riche en oxygene de la voie lactee de la Bulle Savonneuse, "
                                 "un droede du nom de C6R4. Meme si il n'était qu'une IA, ils avaient la meme philosophie de vie suite au drame qui a bouleverse la vie "
                                 "dans l'univers il y avait maintenant 8 jours.";
        const string KStrLevel4 ="10 jours depuis le drame. Johnny commencait a s'interroger sur le but de sa quete, y aura - t - il un jour une fin a cette guerre ? "
                                 "Pourrons-nous un jour nous entendre à nouveau ? Ces questions rongeaient Johnny au plus profond de son etre..";
        const string KStrLevel5 ="12 jours depuis le drame. C'est fini, la musique de la marche imperiale se fait entendre du fond de l'etoile robotisee dans laquelle Johnny est enferme"
                                 "Lorsque tout espoir disparut aux yeux de Johnny, C6R4 surgit et le libéra. Ils dérobèrent un X-Zwim dans le hangar de l'empire. "
                                 "C'etait l'heure du dernier combat. Ils allaient payer pour avoir aime Star Wars 7.";
        switch (Level)
        {
        case 0:
            write(resizeText(KStrIntroduction,60), 60 ,100000);
            break;
        case 1:
            write(resizeText(KStrLevel2,60), 60 ,100000);
            break;
        case 2:
            write(resizeText(KStrLevel3,60), 60 ,100000);
            break;
        case 3:
            write(resizeText(KStrLevel4,60), 60 ,100000);
            break;
        case 4:
            write(resizeText(KStrLevel5,60), 60 ,100000);
            break;
        }
        sleep(5);
        clearScreen(25,60);
    }

    char MoveTo(string::iterator &From, string::iterator &To)
    {
        char LastValueTo(*To);
        if(*To!=KEmpty)
            *To = KEmpty;
        else
            *To = *From;
        *From = KEmpty;
        return LastValueTo;
    }

    void initSpace(CVString &Space, unsigned MyPos, unsigned InvaderPos)
    {
        srand (time(NULL));
        Space = CVString(KSizeSpace,string(KSizeLine, KEmpty));
        for(unsigned i(0) ; i < KInvadersSize ; ++i)
            Space[0][i + InvaderPos] = KInsideInvader;

        Space[Space.size()-1][MyPos] = KInsideMe;
    }

    bool WinTest(CVString &Space, const unsigned &Ligne)
    {
        string &InvaderLine(Space[Ligne]);
        return find(InvaderLine.begin(), InvaderLine.end(), KInsideInvader)==InvaderLine.end();
    }

    bool LoseTest(CVString &Space, const unsigned &Ligne)
    {
        string &MyLine(Space[Ligne]);
        return find(MyLine.begin(), MyLine.end(), KInsideMe)==MyLine.end();
    }

    void ManageInvaderMove(CVString &Space, bool &Increment, unsigned &CurrentLine, unsigned &Beg)
    {
        string &currentLine = Space[CurrentLine];
        if(Increment)
        {
            for(unsigned i(currentLine.size()-1) ; i!=0 ; --i)
            {
                if(currentLine[i-1] == KInsideInvader)
                {
                    if(currentLine[i]   ==  KTorpedo)
                    {
                        currentLine[i] = KEmpty;
                        currentLine[i-1] = KEmpty;
                    }
                    else
                        swap(currentLine[i-1], currentLine[i]);
                }
            }
        }
        else
        {
            for(unsigned i(0) ; i<(currentLine.size()-1) ; ++i)
            {
                if(currentLine[i+1] == KInsideInvader)
                {
                    if(currentLine[i]   ==  KTorpedo)
                    {
                        currentLine[i] = KEmpty;
                        currentLine[i+1] = KEmpty;
                    }
                    else
                        swap(currentLine[i], currentLine[i+1]);
                }
            }
        }

        Beg = find(currentLine.begin(),currentLine.end(), KInsideInvader) - currentLine.begin();

        if(Increment == false && currentLine[0] == KInsideInvader)
        {
            Increment = true;
            string &futureLine = Space[++CurrentLine];
            for(string::iterator i(currentLine.begin()), j(futureLine.begin()) ; i!=currentLine.end() && j!=futureLine.end() ; ++i, ++j)
            {
                if(*i == KInsideInvader)
                    MoveTo(i, j);
            }
        }
        else if(Increment == true && currentLine[currentLine.size()-1] == KInsideInvader)
        {
            string &futureLine = Space[++CurrentLine];
            Increment = false;
            for(string::iterator i(currentLine.begin()), j(futureLine.begin()) ; i!=currentLine.end() && j!=futureLine.end() ; ++i, ++j)
            {
                if(*i == KInsideInvader)
                    MoveTo(i, j);
            }
        }

    }

    void ManageInvaderShoot(CVString & Space, unsigned &CurrentLine, unsigned &Beg, unsigned &MyLife)
    {
        string SMisile(1,KMissile);
        unsigned pos(rand()%KInvadersSize);
        string &ShootLine = Space[CurrentLine+1];
        while(Space[CurrentLine][pos + Beg] != KInsideInvader)
            pos = (pos+1)%KInvadersSize;
        string::iterator dest(ShootLine.begin()+ pos + Beg);
        string::iterator from(SMisile.begin());
        if(MoveTo(from, dest) == KInsideMe)
        {
            --MyLife;
            if(MyLife != 0)
                *dest = KInsideMe;
        }
    }

    void ManageMe (CVString & Space, unsigned &MyPos, int &FireWait)
    {
        string &CurrentLine = Space[Space.size()-1];
        char Move;
        //fonction en C qui permet de lire un caractÃ¨re. cin ne fonctionnant pas dans cette configuration
#ifdef __WIN32__
        string Buf;
        cin >> Buf;
        Move = Buf[0];
#else
        char Buf;
        read (STDIN_FILENO, &Move, 1);
        while(read (STDIN_FILENO, &Buf, 1)!=0);
#endif
        if(Move==KLeft)
        {
            if(MyPos != 0)
            {
                swap(CurrentLine[MyPos], CurrentLine[MyPos-1]);
                --MyPos;
            }
        }
        else if(Move==KRight)
        {
            if((MyPos+1) != CurrentLine.size())
            {
                swap(CurrentLine[MyPos], CurrentLine[MyPos+1]);
                ++MyPos;
            }
        }
        else if(Move==KShoot && FireWait==0)
        {
            Space[Space.size()-2][MyPos] = KTorpedo;
            FireWait = KFireWait;
        }
        if(FireWait != 0)
            --FireWait;
    }// ManageMe ()

    void ManageMissileAndTorpedo(CVString &Space, unsigned &InvaderCount, unsigned &MyLife)
    {
        string &FirstLine = Space[0];
        string &LastLine = Space[Space.size()-1];

        for(char &Val : FirstLine)
            if(Val == KTorpedo)
                Val = KEmpty;

        for(char &Val : LastLine)
            if(Val == KMissile)
                Val = KEmpty;

        for(char &Val : LastLine)
            if(Val == KBonus)
                Val = KEmpty;

        vector<string::iterator> DontMoveIt;

        for(CVString::iterator i(Space.begin()), z(Space.begin()+1) ; z!=Space.end() ; ++i, ++z)
        {
            for(string::iterator j(i->begin()), k(z->begin()) ; j!=i->end() ; ++j, ++k)
            {
                if(*k == KTorpedo && find(DontMoveIt.begin(), DontMoveIt.end(), k)==DontMoveIt.end())
                {
                    if(MoveTo(k, j) == KInsideInvader)
                        --InvaderCount;
                    DontMoveIt.push_back(j);
                }

                if(*j == KMissile&& find(DontMoveIt.begin(), DontMoveIt.end(), j)==DontMoveIt.end())
                {
                    if(MoveTo(j, k) == KInsideMe)
                    {
                        --MyLife;
                        if(MyLife != 0)
                            *k = KInsideMe;
                    }
                    DontMoveIt.push_back(k);
                }

                if(*j == KBonus && find(DontMoveIt.begin(), DontMoveIt.end(), j)==DontMoveIt.end())
                {
                    if(MoveTo(j, k) == KInsideMe)static_cast<void>(KInsideInvader);
                    DontMoveIt.push_back(k);
                }
            }
        }
    }

    void ManageBonus(CVString &Space, const unsigned &LineInvader)
    {
        Space[LineInvader+1][rand()%KSizeLine] = KBonus;
    }

    void MainFont(const unsigned &EyeColor = KRouge, const unsigned &BodyColor = KNoir, const unsigned &BackGroundColor = KVert)
    {
        cout << gotoXY(0,0);
        string Col  (SetColorAndBack(BodyColor, BodyColor));
        string Col2 (SetColorAndBack(EyeColor, EyeColor));
        string Col3 (SetColorAndBack(BackGroundColor, BodyColor));
        string Col4 (SetColorAndBack(BackGroundColor, BackGroundColor));
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
        if(Picture[0]!=' ')
            cout << Col;
        for(string::iterator i(Picture.begin()) ; i != Picture.end() ; ++i)
        {
            if(*i==' ')
                cout << Col;
            else if(*i=='X')
                cout << Col2;
            else if(*i=='.')
                cout << Col3;
            else if(*i=='M')
                cout << Col4;
            else
                cout << Reset();
            cout << *i;
            usleep(5000);
        }
        cout << Reset() << flush;
        sleep(2);
        clearScreen(25,60);
    }

    void Run()
    {
        QThread Thread;
        QMediaPlayer player;
        player.moveToThread(&Thread);
        player.setVolume(50);
        QVector<QUrl> playlist;
        playlist.push_back(QUrl(QString::fromStdString(KIntroSound)));
        playlist.push_back(QUrl(QString::fromStdString(KEndSound)));
        playlist.push_back(QUrl(QString::fromStdString(KGameOverSound)));
        playlist.push_back(QUrl(QString::fromStdString(KHistoSound)));
        playlist.push_back(QUrl(QString::fromStdString(KGameSound)));

        player.setMedia(playlist[0]);
        player.play();

        srand (time(NULL));
        set_input_mode();
        MainFont();
        CVString Space;
        int FinalScore(0);
        unsigned Level(0);
        for( ; Level<5 && (Level==0 || !LoseTest(Space, Space.size()-1)) ; ++Level)
        {
            unsigned PosInvader(KBegInvader), PosMe(KBegMe);
            unsigned LineInvader(0);
            unsigned FirstInvaderCount (KInvadersSize);
            unsigned PlayerLife (KMyLife);
            int Score(0);
            bool Increment(true);
            int FireWait(0);
            initSpace(Space, PosMe, PosInvader);
            cout << CleanScreen();

            player.stop();
            player.setMedia(playlist[3]);
            player.play();

            ManageScenar(Level);

            player.stop();
            player.setMedia(playlist[4]);
            player.play();

            cout << CleanScreen();
            while(!WinTest(Space, LineInvader) && !LoseTest(Space, Space.size()-1))
            {
                unsigned LastInvaderCount (FirstInvaderCount);
                Score -= 10;

                if(LastInvaderCount != FirstInvaderCount)
                {
                    ManageBonus(Space, LineInvader);
                    Score += 100;
                }

                for(unsigned i(0) ; i<KRatioMeInvaders &&  (!WinTest(Space, LineInvader) && !LoseTest(Space, Space.size()-1)); ++i)
                {
                    ManageMissileAndTorpedo(Space, FirstInvaderCount, PlayerLife);
                    if(i == 0)
                        ManageInvaderShoot(Space, LineInvader, PosInvader, PlayerLife);
                    chrono::high_resolution_clock::time_point t1 = chrono::high_resolution_clock::now();
                    ManageMe(Space, PosMe, FireWait);
                    cout << gotoXY(0,0) << "\t\t\t" << SetColorAndBack(KNoir, KRouge) << string(KSizeLine+2,'-') << Reset() << endl;
                    for(const string &Line : Space)
                    {
                        cout << "\t\t\t" << SetColorAndBack(KNoir, KRouge) << '|' << Reset();
                        PrintGameLine(Line);
                        cout << SetColorAndBack(KNoir, KRouge) << '|' << Reset() << endl;
                    }
                    cout << "\t\t\t" << SetColorAndBack(KNoir, KRouge) << string(KSizeLine+2,'-') << Reset() << endl;
                    cout << SetColorAndBack(KCyan, KRouge) << resizeText("             Score : " + to_string(Score) + " Player Life : " + to_string(PlayerLife), 60) << Reset() << endl;
                    cout << SetColorAndBack(KCyan, KRouge) << resizeText("   FinalScore : " + to_string(Score + FinalScore) + " Invader Count : " + to_string(FirstInvaderCount),60)<< Reset() << endl;
                    chrono::high_resolution_clock::time_point t2 = chrono::high_resolution_clock::now();
                    auto duration = chrono::duration_cast<chrono::microseconds>( t2 - t1 ).count();
                    if(duration<350000)
                        usleep(350000-duration);
                }
                if(player.state() != QMediaPlayer::PlayingState)
                    player.play();

                ManageInvaderMove(Space, Increment,  LineInvader, PosInvader);
            }
            if(PlayerLife==0)
            {

                player.stop();
                player.setMedia(playlist[2]);
                player.play();

                MainFont(KNoir,KRouge, KNoir);
            }
            else if(Level == 4)
            {
                player.stop();
                player.setMedia(playlist[1]);
                player.play();

            }
            FinalScore += Score;
        }
    }
}
