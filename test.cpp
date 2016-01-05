#include "test.h"
#include <stdexcept>
#include "globaltype.h"
#include "gameengine.h"

using namespace std;
using namespace binaire;
#define RESET(X, A) X = false; A = false

bool collisionTestMissile(ostream &os)
{
    bool testPassed(true);
    bool Win, Lost;
    RESET(Win, Lost);
    // Serie de test afin de déterminer si la physique des torpille est correcte
    {
        CVSurface Test = {
            {KPxEmpty,   KPxEmpty,    KPxEmpty},
            {KPxEmpty,   KPxMissile,  KPxEmpty},
            {KPxEmpty,   KPxTorpedo,  KPxEmpty},
            {KPxEmpty,   KPxEmpty,    KPxEmpty}
        };
        CVSurface Result = {
            {KPxEmpty,   KPxEmpty,    KPxEmpty},
            {KPxEmpty,   KPxEmpty,    KPxEmpty},
            {KPxEmpty,   KPxEmpty,    KPxEmpty},
            {KPxEmpty,   KPxEmpty,    KPxEmpty}
        };
        recomputeFrame(Test, Win, Lost);

        os << string(10, '-') << endl;
        testPassed = testPassed && Test==Result && Win==false && Lost==false;
        if(Test==Result && Win==false && Lost==false)
            os << "Test 1 OK" << endl;
        else
            os << "Test 1 FAILD\nMissile or Torpedo cannot be destroy or sommething spawn on Test Frame" << endl;
    }

    RESET(Win, Lost);
    {
        CVSurface Test = {
            {KPxEmpty,   KPxEmpty,    KPxEmpty},
            {KPxEmpty,   KPxEmpty,    KPxEmpty},
            {KPxEmpty,   KPxMissile,  KPxEmpty},
            {KPxEmpty,   KPxInsideMe, KPxEmpty}
        };
        CVSurface Result = {
            {KPxEmpty,   KPxEmpty,    KPxEmpty},
            {KPxEmpty,   KPxEmpty,    KPxEmpty},
            {KPxEmpty,   KPxEmpty,    KPxEmpty},
            {KPxEmpty,   KPxEmpty,    KPxEmpty}
        };
        recomputeFrame(Test, Win, Lost);

        os << string(10, '-') << endl;
        testPassed = testPassed && Test==Result && Win==false && Lost==true;
        if(Test==Result && Win==false && Lost==true)
            os << "Test 2 OK" << endl;
        else
            os << "Test 2 FAILD\nWin condition failled or sommething spawn on Test Frame or player is on Frame maybe with " << KMissile << endl;
    }

    RESET(Win, Lost);
    {
        CVSurface Test = {
            {KPxEmpty,   KPxMissile,  KPxEmpty},
            {KPxEmpty,   KPxTorpedo,  KPxEmpty},
            {KPxEmpty,   KPxEmpty,    KPxEmpty},
            {KPxEmpty,   KPxEmpty,    KPxEmpty}
        };
        CVSurface Result = {
            {KPxEmpty,   KPxEmpty,    KPxEmpty},
            {KPxEmpty,   KPxEmpty,    KPxEmpty},
            {KPxEmpty,   KPxEmpty,    KPxEmpty},
            {KPxEmpty,   KPxEmpty,    KPxEmpty}
        };
        recomputeFrame(Test, Win, Lost);

        os << string(10, '-') << endl;
        testPassed = testPassed && Test==Result && Win==false && Lost==false;
        if(Test==Result && Win==false && Lost==false)
            os << "Test 3 OK" << endl;
        else
            os << "Test 3 FAILD\nMissile or Torpedo cannot be destroy on Top or sommething spawn on Test Frame" << endl;
    }

    RESET(Win, Lost);
    {
        CVSurface Test = {
            {KPxEmpty,   KPxEmpty,    KPxEmpty},
            {KPxEmpty,   KPxEmpty,    KPxEmpty},
            {KPxEmpty,   KPxMissile,  KPxEmpty},
            {KPxEmpty,   KPxTorpedo,  KPxEmpty}
        };
        CVSurface Result = {
            {KPxEmpty,   KPxEmpty,    KPxEmpty},
            {KPxEmpty,   KPxEmpty,    KPxEmpty},
            {KPxEmpty,   KPxEmpty,    KPxEmpty},
            {KPxEmpty,   KPxEmpty,    KPxEmpty}
        };
        recomputeFrame(Test, Win, Lost);

        os << string(10, '-') << endl;
        testPassed = testPassed && Test==Result && Win==false && Lost==false;
        if(Test==Result && Win==false && Lost==false)
            os << "Test 4 OK" << endl;
        else
            os << "Test 4 FAILD\nMissile or Torpedo cannot be destroy on bottom or sommething spawn on Test Frame" << endl;
    }

    RESET(Win, Lost);
    {
        CVSurface Test = {
            {KPxEmpty,   KPxEmpty,    KPxEmpty},
            {KPxEmpty,   KPxMissile,  KPxEmpty},
            {KPxEmpty,   KPxEmpty,    KPxEmpty},
            {KPxEmpty,   KPxEmpty,    KPxEmpty}
        };
        CVSurface Result = {
            {KPxEmpty,   KPxEmpty,    KPxEmpty},
            {KPxEmpty,   KPxEmpty,    KPxEmpty},
            {KPxEmpty,   KPxMissile,  KPxEmpty},
            {KPxEmpty,   KPxEmpty,    KPxEmpty}
        };
        recomputeFrame(Test, Win, Lost);

        os << string(10, '-') << endl;
        testPassed = testPassed && Test==Result && Win==false && Lost==false;
        if(Test==Result && Win==false && Lost==false)
            os << "Test 5 OK" << endl;
        else
            os << "Test 5 FAILD\nMissile cannot move or someting else wrong" << endl;
    }

    RESET(Win, Lost);
    {
        CVSurface Test = {
            {KPxEmpty,   KPxEmpty,    KPxEmpty},
            {KPxEmpty,   KPxEmpty,    KPxEmpty},
            {KPxEmpty,   KPxTorpedo,  KPxEmpty},
            {KPxEmpty,   KPxEmpty,    KPxEmpty}
        };
        CVSurface Result = {
            {KPxEmpty,   KPxEmpty,    KPxEmpty},
            {KPxEmpty,   KPxTorpedo,  KPxEmpty},
            {KPxEmpty,   KPxEmpty,    KPxEmpty},
            {KPxEmpty,   KPxEmpty,    KPxEmpty}
        };
        recomputeFrame(Test, Win, Lost);

        os << string(10, '-') << endl;
        testPassed = testPassed && Test==Result && Win==false && Lost==false;
        if(Test==Result && Win==false && Lost==false)
            os << "Test 6 OK" << endl;
        else
            os << "Test 6 FAILD\nTorpedo cannot move or someting else wrong" << endl;
    }
    return testPassed;
}
