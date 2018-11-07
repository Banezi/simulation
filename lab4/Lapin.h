#ifndef LAPIN_H_INCLUDED
#define LAPIN_H_INCLUDED

class Lapin
{
    protected:
        int age; // en mois
        bool en_vie;
        char sexe;

    public:
        Lapin();
       ~Lapin();
        int get_age(); void set_age(int a);
        bool get_en_vie(); void set_en_vie(bool b);
        char get_sexe(); void set_sexe();

        static int nbLapins;
};

#endif // LAPIN_H_INCLUDED
