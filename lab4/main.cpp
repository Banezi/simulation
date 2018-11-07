#include <iostream>
#include "Lapin.h"
#include <ctime>
#include <cstdlib>

using namespace std;

int main()
{
    srand(time(NULL));
    Lapin l;
    cout << l.get_age() << endl;
    cout << l.get_sexe() << endl;
    cout << l.get_en_vie() << endl;
    cout << Lapin::nbLapins;
    return 0;
}
