#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <ctime>
#define BORNE_INF 0.0
#define BORNE_SUP 1.0
using namespace std;

double randomAB(double a, double b);
void generateur(int n);
int main()
{
    srand(time(NULL));
    generateur(5);
    return 0;
}
void generateur(int n)
{
    double increment, debut, fin;
    debut = BORNE_INF;
    fin = BORNE_SUP;
    for(int i=0; i<n; i++)
    {
        increment = fin / 3.0;
        cout << "[" << debut << ", " << debut+increment << "[" << "\t";
        cout << "[" << debut+increment << ", " << debut+2*increment << "[" << endl;
        debut = debut + increment;
        fin = debut+2*increment;
    }
}
double randomAB(double a, double b)
{
    return (double)rand()/(RAND_MAX)*(b-a)+a;
}
