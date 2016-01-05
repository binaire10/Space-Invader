#include <iostream>
#include <iomanip>
#include <stdexcept>
#include "screen.h"
#include "gameengine.h"
#include "grille.h"
#include "test.h"
#include "sysgame.h"
#include "tool.h"
#include "configfile.h"
using namespace std;
using namespace binaire;
#define RESET(X, A) X = false; A = false

int main()
{/*
    std::stringstream voidF;
    if(collisionTestMissile(voidF))
        cout << "[Test][Collision][Missile&Torpedo] -> All OK" << endl;
    else
        cout << voidF.str() << "[Test][Collision][Missile&Torpedo] -> FAILD" << endl;
    voidF.str("");*/

    try
    {
        run();
    }
    catch(exception &e)
    {
        cerr << e.what() << endl;
    }
    catch(...)
    {
        cerr << "something wrong" << endl;
    }

    return 0;
}
