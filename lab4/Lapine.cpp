#include "Lapine.h"
#include <ctime>
#include <cstdlib>

using namespace std;

Lapine::Lapine()
{
    age = 0;
    en_vie = true;
    sexe = 'f';
    portee=0;
    ageMaturite = rand()%(8-5+1)+5;
    nbTotalPortee = rand()%(8-4+1)+4;
}

Lapine::~Lapine()
{

}

int Lapine::get_nbTotalPortee()
{
    return nbTotalPortee;
}
int Lapine::get_portee()
{
    return portee;
}

int Lapine::reproduction()
{
    if(estMature() && portee<nbTotalPortee)
    {
        portee++;
        return rand()%(6-3+1)+3;
    }
    return 0;
}
