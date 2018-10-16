#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

void jvn_generator(int seed); // John Von Neumann generator
void coin_tossing(int n); // n experiments
void lcg_intRand(int seed, int a, int c, int m); // Linear Congruential Generators with int random
void lcg_floatRand(int seed, int a, int c, int m); // Linear Congruential Generators with float random

int main()
{
    //jvn_generator(1234);
    //coin_tossing(1000);
    //lcg_intRand(5,5,1,16);
    //lcg_floatRand(5,5,1,16);
    //lcg_intRand(10,25,16,256);
    //lcg_intRand(0,31415821,1,100000000); // parameters respecting Knuth's properties
    return 0;
}

void jvn_generator(int seed)
{
    int i=0, n0=seed, n1;

    while(n0!=0) // don't forget to uncomment the line i++;
    //for(i=0;i<20;i++)
    {
        printf("%.4f \t N%d = %04d \t %04d*%04d = %08d \n", 0.1*n0/1000, i, n0, n0, n0, n0*n0);
        n1=((n0*n0)/100)%10000;
        n0=n1;
        i++; // comment this line if you use the for loop
    }
}

void coin_tossing(int n)
{
    srand(time(NULL)); // initialization of pseudo generator number
    int i, j, r, t[6]={0};
    t[1]=t[1]++; // don't work! ?
    for(i=0;i<n;i++)
    {
        r = rand()%6 + 1;
        for(j=0;j<6;j++)
        {
            if(r==(j+1))
            {
                t[j] = ++t[j]; // t[j] = t[j]++; why doesn't work?
                break;
            }
        }
        /*
        switch(r)
        {
        case 1:
            t[0] = ++t[0]; // t[0] = t[0]++; why?
            break;
        case 2:
            t[1] = ++t[1];
            break;
        case 3:
            t[2] = ++t[2];
            break;
        case 4:
            t[3] = ++t[3];
            break;
        case 5:
            t[4] = ++t[4];
            break;
        case 6:
            t[5] = ++t[5];
            break;
        default:
            printf("There's a matter!\n");
        }
        */
        printf("%d\t",r);
    }
    printf("\n\n");
    for(j=0;j<6;j++)
        printf("P(%d) = %d/%d = %.2f \n", j+1, t[j], n, (float)t[j]/n);
}

void lcg_intRand(int seed, int a, int c, int m)
{
    int x = seed, i;
    for(i=0;i<100;i++)
    {
        printf("%d\t",x);
        x=(a*x + c) % m;
    }
    printf("\n");
}
void lcg_floatRand(int seed, int a, int c, int m)
{
    int x = seed, i;
    for(i=0;i<100;i++)
    {
        printf("%g\t",(float)x/m);
        x=(a*x + c) % m;
    }
    printf("\n");
}
