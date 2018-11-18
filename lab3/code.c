/* ----------------------------------------------------------------- */
/* computePi    : Generation de Pi avec la méthode Monte Carlo       */
/* En entrée    : ni, nombre entier désignant e nombre d'itération   */
/* En sortie    : la valeur réelle obtenue pour le calcul de Pi      */
/* ----------------------------------------------------------------- */
double computePi(int ni) // ni nombre d'itération
{
    double rand1, rand2, nbInside=0. , rate, pi;
    int i;
    for(i=0;i<ni;i++)
    {
        rand1 = genrand_real1();
        rand2 = genrand_real1();
        if(rand1*rand1 + rand2*rand2 < 1)
            nbInside++;
    }
    rate = nbInside/ni;
    pi = 4*rate;
    return pi;
}

/* ---------------------------------------------------------------------- */
/* compute_n_Pi : Valeur moyenne de Pi avec n expériences indépendantes   */
/* En entrée    : n, nombre d'expérience indépendantes à réaliser         */
/*                ni, nombre entier désignant le nombre d'itération       */
/*                pour chaque expérience                                  */
/* En sortie    : la valeur moyenne de Pi obtenue                         */
/* ---------------------------------------------------------------------- */
double compute_n_Pi(int n, int ni) // n : nombre d'experience, ni:nombre d'iteration pour chaque experience
{
    int i;
    double pi = 0.;
    for(i=0; i<n; i++)
        pi += computePi(ni);
    pi /= n;
    return pi;
}

/* ----------------------------------------------------------------------------------------- */
/* confidence_interval : Calcul le rayon de confiance et affiche l'intervalle de confiance   */
/* En entrée    : n, nombre d'expérience indépendantes à réaliser                            */
/*                ni, nombre entier désignant le nombre d'itération                          */
/*                pour chaque expérience                                                     */
/* En sortie    : Affiche l'intervalle de confiance                                          */
/* ----------------------------------------------------------------------------------------- */
void confidence_interval(int n, int ni)
{
    double t[30] = {12.706,4.303,3.182, 2.776, 2.571, 2.447, 2.365, 2.308, 2.262, 2.228, 2.201, 2.179,
                    2.160, 2.145, 2.131, 2.120, 2.110, 2.101, 2.093, 2.086, 2.080, 2.074, 2.069, 2.064,
                    2.060, 2.056, 2.052, 2.048, 2.045, 2.042};
    double s2=.0, r, pi_ = .0;
    double* pi = NULL;
    pi =  malloc(n*sizeof(double));
    int i;
    for(i=0; i<n; i++)
    {
        pi[i] = computePi(ni);
        pi_ += pi[i];
    }
    pi_ /= n;
    for(i=0; i<n; i++)
    {
        s2 += pow ( (pi[i]-pi_) , 2);
    }
    s2 /= n-1;
    r = t[n-1]*sqrt(s2/n);
    printf("Intervale de confiance : [%f , %f]\n", pi_-r, pi_+r);
    free(pi);
}

/* ---------------------------------------------------------------------- */
/* fib : Suite de Fibbonacci                                              */
/* En entrée    : n, nombre entier                                        */
/* En sortie    : entier, la n ième valeur de la suite de Fibonnaci       */
/* ---------------------------------------------------------------------- */
int fib(int n)
{
    if(n==0 || n==1)
        return n;
    else
        return fib(n-1)+fib(n-2);
}
typedef struct Lapin Lapin;
struct Lapin
{
    char type;
};
/* ---------------------------------------------------------------------- */
/* rabbit_population_growth : Affiche la croissance des lapins sur n mois */
/* En entrée    : n, nombre de mois                                       */
/* En sortie    : Affichage des lapins                                    */
/* ---------------------------------------------------------------------- */
void rabbit_population_growth(int n)
{
    int i,j, paire, nbLapins=0, nbLapinsTotal, fils;
    nbLapinsTotal = fib(n);
    Lapin* listeLapins = malloc(nbLapinsTotal*sizeof(Lapin));
    for(i=0; i<n; i++)
    {
        paire = fib(i);
        fils = paire-nbLapins;
        for(j=nbLapins; j<nbLapins+fils; j++)
            listeLapins[j].type='l';
        for(j=0;j<nbLapins+fils;j++)
        {
            printf("%c+%c\t",listeLapins[j].type, listeLapins[j].type);
        }
        printf("\n---------------------------------------------\n");
        for(j=nbLapins;j<nbLapins+fils;j++)
        {
            if(listeLapins[j].type=='l')
                listeLapins[j].type='L';
        }

        nbLapins+=fils;

    }
}

