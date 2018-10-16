#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

int    randomAB(int a, int b);
double random01();
void   distribution();
void   distribution_exp();


int randomAB(int a, int b)
{

    return ( (rand()%(b-a) + 1 ) );
}

double random01()
{
    return (double)rand() / (double) RAND_MAX;
}

void distribution()
{
    int i, t[3]={0};
    float r;
    for(i=0;i<1000;i++)
    {
        r=random01();
        if(r<0.5)
            t[0] = t[0]+1;
        else if (r<0.6)
            t[1] = t[1]+1;
        else
            t[2] = t[2] +1;

    }
    printf("P(A) = %d\n", t[0]);
    printf("P(B) = %d\n", t[1]);
    printf("P(C) = %d\n", t[2]);
}

/* -------------------------------------------------------------------- */
/* negExp       Retourne une valeur suivant une loi exponentielle       */
/*              negative de moyenne inMoyenne                           */
/*                                                                      */
/* En entrée : inMoyenne - la moyenne désirée                           */
/*                                                                      */
/* En sortie : un nombre distribué suivant la loi NegExp(inMoyenne)     */
/* -------------------------------------------------------------------- */

double negExp(double inMoyenne)
{
    return (log(1. - random01()) * inMoyenne * -1);
}

/* -------------------------------------------------------------------- */

int main()
{
/*    srand(time(NULL));


    distribution();
  */
    int    i, tabF[21] = { 0 };
    double x, moy = 0.;

    for (i = 0; i < 1000000; i++)
    {
        x = negExp(10.);
        moy += x;

        if (x < 20.)
        {
            /*printf("x = %f\n", x);
            printf("(int) x = %d\n", (int) x);
            */
            ++tabF[(int) x];
        }
        else tabF[20]++;
    }
    moy = moy / (double) 1000000;

    for (i = 0; i < 20 ; i++)
    {
        printf("Tab[%02d] = %d\n", i, tabF[i]);
    }
    printf("Tab[20] = %d\n", tabF[20]);
    printf("Moyenne = %f\n", moy);

    return 0;
}

