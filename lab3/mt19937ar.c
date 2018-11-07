/*
   A C-program for MT19937, with initialization improved 2002/1/26.
   Coded by Takuji Nishimura and Makoto Matsumoto.

   Before using, initialize the state by using init_genrand(seed)
   or init_by_array(init_key, key_length).

   Copyright (C) 1997 - 2002, Makoto Matsumoto and Takuji Nishimura,
   All rights reserved.

   Redistribution and use in source and binary forms, with or without
   modification, are permitted provided that the following conditions
   are met:

     1. Redistributions of source code must retain the above copyright
        notice, this list of conditions and the following disclaimer.

     2. Redistributions in binary form must reproduce the above copyright
        notice, this list of conditions and the following disclaimer in the
        documentation and/or other materials provided with the distribution.

     3. The names of its contributors may not be used to endorse or promote
        products derived from this software without specific prior written
        permission.

   THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
   "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
   LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
   A PARTICULAR PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL THE COPYRIGHT OWNER OR
   CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
   EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
   PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
   PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
   LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
   NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
   SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.


   Any feedback is very welcome.
   http://www.math.sci.hiroshima-u.ac.jp/~m-mat/MT/emt.html
   email: m-mat @ math.sci.hiroshima-u.ac.jp (remove space)
*/

#include <stdio.h>

/* Period parameters */
#define N 624
#define M 397
#define MATRIX_A 0x9908b0dfUL   /* constant vector a */
#define UPPER_MASK 0x80000000UL /* most significant w-r bits */
#define LOWER_MASK 0x7fffffffUL /* least significant r bits */

#include <math.h> /* Pour l'utilisation de M_PI */
#include <stdlib.h>

static unsigned long mt[N]; /* the array for the state vector  */
static int mti=N+1; /* mti==N+1 means mt[N] is not initialized */

/* initializes mt[N] with a seed */
void init_genrand(unsigned long s)
{
    mt[0]= s & 0xffffffffUL;
    for (mti=1; mti<N; mti++) {
        mt[mti] =
	    (1812433253UL * (mt[mti-1] ^ (mt[mti-1] >> 30)) + mti);
        /* See Knuth TAOCP Vol2. 3rd Ed. P.106 for multiplier. */
        /* In the previous versions, MSBs of the seed affect   */
        /* only MSBs of the array mt[].                        */
        /* 2002/01/09 modified by Makoto Matsumoto             */
        mt[mti] &= 0xffffffffUL;
        /* for >32 bit machines */
    }
}

/* initialize by an array with array-length */
/* init_key is the array for initializing keys */
/* key_length is its length */
/* slight change for C++, 2004/2/26 */
void init_by_array(unsigned long init_key[], int key_length)
{
    int i, j, k;
    init_genrand(19650218UL);
    i=1; j=0;
    k = (N>key_length ? N : key_length);
    for (; k; k--) {
        mt[i] = (mt[i] ^ ((mt[i-1] ^ (mt[i-1] >> 30)) * 1664525UL))
          + init_key[j] + j; /* non linear */
        mt[i] &= 0xffffffffUL; /* for WORDSIZE > 32 machines */
        i++; j++;
        if (i>=N) { mt[0] = mt[N-1]; i=1; }
        if (j>=key_length) j=0;
    }
    for (k=N-1; k; k--) {
        mt[i] = (mt[i] ^ ((mt[i-1] ^ (mt[i-1] >> 30)) * 1566083941UL))
          - i; /* non linear */
        mt[i] &= 0xffffffffUL; /* for WORDSIZE > 32 machines */
        i++;
        if (i>=N) { mt[0] = mt[N-1]; i=1; }
    }

    mt[0] = 0x80000000UL; /* MSB is 1; assuring non-zero initial array */
}

/* generates a random number on [0,0xffffffff]-interval */
unsigned long genrand_int32(void)
{
    unsigned long y;
    static unsigned long mag01[2]={0x0UL, MATRIX_A};
    /* mag01[x] = x * MATRIX_A  for x=0,1 */

    if (mti >= N) { /* generate N words at one time */
        int kk;

        if (mti == N+1)   /* if init_genrand() has not been called, */
            init_genrand(5489UL); /* a default initial seed is used */

        for (kk=0;kk<N-M;kk++) {
            y = (mt[kk]&UPPER_MASK)|(mt[kk+1]&LOWER_MASK);
            mt[kk] = mt[kk+M] ^ (y >> 1) ^ mag01[y & 0x1UL];
        }
        for (;kk<N-1;kk++) {
            y = (mt[kk]&UPPER_MASK)|(mt[kk+1]&LOWER_MASK);
            mt[kk] = mt[kk+(M-N)] ^ (y >> 1) ^ mag01[y & 0x1UL];
        }
        y = (mt[N-1]&UPPER_MASK)|(mt[0]&LOWER_MASK);
        mt[N-1] = mt[M-1] ^ (y >> 1) ^ mag01[y & 0x1UL];

        mti = 0;
    }

    y = mt[mti++];

    /* Tempering */
    y ^= (y >> 11);
    y ^= (y << 7) & 0x9d2c5680UL;
    y ^= (y << 15) & 0xefc60000UL;
    y ^= (y >> 18);

    return y;
}

/* generates a random number on [0,0x7fffffff]-interval */
long genrand_int31(void)
{
    return (long)(genrand_int32()>>1);
}

/* generates a random number on [0,1]-real-interval */
double genrand_real1(void)
{
    return genrand_int32()*(1.0/4294967295.0);
    /* divided by 2^32-1 */
}

/* generates a random number on [0,1)-real-interval */
double genrand_real2(void)
{
    return genrand_int32()*(1.0/4294967296.0);
    /* divided by 2^32 */
}

/* generates a random number on (0,1)-real-interval */
double genrand_real3(void)
{
    return (((double)genrand_int32()) + 0.5)*(1.0/4294967296.0);
    /* divided by 2^32 */
}

/* generates a random number on [0,1) with 53-bit resolution*/
double genrand_res53(void)
{
    unsigned long a=genrand_int32()>>5, b=genrand_int32()>>6;
    return(a*67108864.0+b)*(1.0/9007199254740992.0);
}
/* ------------------------------------------------------------------------------------------------------------- */
/*                                              Mon code commence ici                                            */
/* ------------------------------------------------------------------------------------------------------------- */

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
    //printf("Pi = %f\n", pi);
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

/* Ecriture du tableau t(n-1),1-a/2 */
void ecriture_tab(double t[], int taille)
{
    /*
    int i;
    for(i=0; i<taille; i++)
    {
        printf("%d : ", i+1);
        scanf("%lf", &t[i]);
        printf("\n");
    }
    */

    t[0] = 12.706;  t[1] = 4.303;   t[2] = 3.182;   t[3] = 2.776;
    t[4] = 2.571;   t[5] = 2.447;   t[6] = 2.365;   t[7] = 2.308;
    t[8] = 2.262;   t[9] = 2.228;   t[10] = 2.201;  t[11] = 2.179;
    t[12] = 2.160;  t[13] = 2.145;  t[14] = 2.131;  t[15] = 2.120;
    t[16] = 2.110;  t[17] = 2.101;  t[18] = 2.093;  t[19] = 2.086;
    t[20] = 2.080;  t[21] = 2.074;  t[22] = 2.069;  t[23] = 2.064;
    t[24] = 2.060;  t[25] = 2.056;  t[26] = 2.052;  t[27] = 2.048;
    t[28] = 2.045;  t[29] = 2.042;
    //t[39] = 2.021;  t[79] = 2.000; t[119] = 1.980;
    // infini : 1.960

}
/* Lecture du tableau */
void lecture_tab(double t[], int taille)
{
    int i;
    for(i=0; i<taille; i++)
    {
        printf("%d : %.3f\n", i+1, t[i]);
    }
}

/* Intervalle de confiance */
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
int fib(int n)
{
    if(n==0 || n==1)
        return n;
    else
        return fib(n-1)+fib(n-2);
}
void rabbit_population_growth(int n)
{
    int i,j, paire;
    for(i=1; i<=n; i++)
    {
        paire = fib(i);
        if(i==2)
        {
            printf("L+L\t");
        }
        else
            printf("l+l\t");
        for(j=2;j<=paire;j++)
        {
            printf("L+L\t");
        }
        printf("\n---------------------------------------------\n");
    }
}

/* These real versions are due to Isaku Wada, 2002/01/09 added */

int main(void)
{

    int i;
    unsigned long init[4]={0x123, 0x234, 0x345, 0x456}, length=4;
    init_by_array(init, length);
    /*
    printf("1000 outputs of genrand_int32()\n");
    for (i=0; i<1000; i++) {
      printf("%10lu ", genrand_int32());
      if (i%5==4) printf("\n");
    }
    printf("\n1000 outputs of genrand_real2()\n");
    for (i=0; i<1000; i++) {
      printf("%10.8f ", genrand_real2());
      if (i%5==4) printf("\n");
    }
    */
    /*
    double pi;
    printf("Pour 1000 iterations, PI = %.3f\n", computePi(1000));
    printf("Pour 1.000.000 iterations, PI = %.3f\n", computePi(1000000));
    pi = computePi(1000000000);
    printf("Pour 1.000.000.000 iterations, PI = %.3f a 10^-3 pres\n", pi);
    printf("Pour 1.000.000.000 iterations, PI = %.4f a 10^-4 pres\n", pi);
    */

    //printf("La valeur moyenne de Pi avec 10 experiences et 1000000 iterations/exp est : Pi = %.3f\n", compute_n_Pi(10,1000000));
    //confidence_interval(10,1000000);
    rabbit_population_growth(10);
    return 0;
}
