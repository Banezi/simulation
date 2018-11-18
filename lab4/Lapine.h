#ifndef LAPINE_H_INCLUDED
#define LAPINE_H_INCLUDED

#include "Lapin.h"

class Lapine : public Lapin
{
private:
    int nbTotalPortee;
    int portee;
public:
    Lapine();
    ~Lapine();
    int get_nbTotalPortee();
    int get_portee();
    int reproduction();
};


#endif // LAPINE_H_INCLUDED
