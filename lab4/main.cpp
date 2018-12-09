#include <iostream>
#include "Lapin.h"
#include "Lapine.h"
#include <ctime>
#include <cstdlib>
#include <cstdio>
#include <vector>
#include <windows.h>

using namespace std;

int main()
{
    srand(time(NULL));
    int annee_simu=3;
    vector<Lapin*> listeLapins;
    vector<Lapine*> listeLapines;
    Lapin* m = new Lapin();
    Lapine* f = new Lapine();
    listeLapins.push_back(m);
    listeLapins.push_back(f);
    listeLapines.push_back(f);
    for(int mois=0; mois<12*annee_simu; mois++)
    {
        for(int i=0; i<listeLapins.size(); i++)
        {
            listeLapins[i]->set_age(listeLapins[i]->get_age()+1);
        }
        for(int i=0; i<listeLapines.size(); i++)
        {
            int nvo;
            Lapin* m;
            Lapine* f;
            nvo = listeLapines[i]->reproduction();
            for(int j=0; j<nvo; j++)
            {
                if(rand()%2 == 0)
                {
                    m = new Lapin();
                    listeLapins.push_back(m);
                }
                else
                {
                    f = new Lapine();
                    listeLapins.push_back(f);
                    listeLapines.push_back(f);
                }
            }
        }

        //Evaluation decès
        int nb_deces=0, n=listeLapins.size();
        for(int i=1; i<n; i++)
        {
            listeLapins[i]->deces();
            if(listeLapins[i]->get_en_vie()==false)
            {
                nb_deces++;
                //delete listeLapins[i];
                //listeLapins.erase(listeLapins.begin()+i);
            }
        }



        //Affichage
        cout << "Mois : " << mois << "\tNombre lapins : " << Lapin::nbLapins << endl;
        for(int i=0; i<listeLapins.size(); i++)
        {
            listeLapins[i]->estMature();
            cout << listeLapins[i]->get_sexe() << " ";
        }
        Sleep(1000);
        if(mois<12*annee_simu-1)
            system("cls");


    }

    //cout << Lapin::nbLapins<< endl;
    //Libération de la mémoire
    for(int i=0; i<listeLapins.size(); i++)
    {
        delete listeLapins[i];
        listeLapins[i] = 0;
    }
    //cout << Lapin::nbLapins<< endl;
    return 0;
}
