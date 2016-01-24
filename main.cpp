#include <iostream>
#include <stdexcept>
#include "Nos_fichiers/SpaceInvader.h"
#include <QtCore>
using namespace std;
using namespace SpaceInvader;

int main()
{
    try {
        Run();
    }
    catch (const out_of_range & e)
    {
        cout<< e.what() << endl;
    }

    return 0;
}
