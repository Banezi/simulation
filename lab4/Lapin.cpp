#include "Lapin.h"
#include <ctime>
#include <cstdlib>
#include <cctype>

using namespace std;

int Lapin::nbLapins = 0;

Lapin::Lapin()
{
    age = 0;
    en_vie = true;
    sexe = 'm';
    nbLapins++;
}
Lapin::Lapin(char s)
{
    age = 0;
    en_vie = true;
    sexe = s;
    nbLapins++;
}

int Lapin::get_age()
{
    return age;
}
void Lapin::set_age(int a)
{
    age = a;
}

bool Lapin::get_en_vie()
{
    return en_vie;
}
void Lapin::set_en_vie(bool b)
{
    en_vie = b;
}

char Lapin::get_sexe()
{
    return sexe;
}
/*void Lapin::set_sexe()
{
    int s=rand()%(1-0+1);
    if(s==0)
        sexe = 'M';
    else
        sexe = 'F';
}*/
Lapin::~Lapin()
{
    nbLapins--;
}
int Lapin::get_ageMaturite()
{
    return ageMaturite;
}
bool Lapin::estMature()
{
    bool mature = age >= ageMaturite;
    if(mature)
        sexe = toupper(sexe);
    return mature;
}
/* ------------------------------------------------------------------------------- */
/*  deces : Méthode d'évaluation de deces d'un lapin                               */
/* ------------------------------------------------------------------------------- */
void Lapin::deces()
{
    int mortMature = rand()%2 + 1;
    int mortBebe = rand()%10 + 1;
    if(age>=5*12 || (estMature() && mortMature==1) || (!estMature() && (mortBebe==1 || mortBebe==2)))
        en_vie = false;
}
