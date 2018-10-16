#include <stdio.h>
#include <stdlib.h>

void affiche(int n); //Affichage de l'entier n en 4 bits
void affiche8(int n);
int main()
{
    int a = 0b00000001;
    affiche(a);
    return 0;
}
 void affiche(int n)
 {
    int q,r,i=0,j, t[10]={0};
    if(n>16)
        n=n%16;
    while(n!=0)
    {
        q=n/2;
        r=n%2;
        n=q;
        t[i]=r;
        i++;
    }
    for(j=0;j<4-i;j++)
    {
        if(j==4)
            printf(" ");
        printf("0");
    }
    for(i=i-1;i>=0;i--)
    {
        printf("%d",t[i]);
    }
    printf("\n");
 }

void affiche8(int n)
 {
    int q,r,i=0,j, t[10]={0};
    if(n>255)
        n=n%255;
    while(n!=0)
    {
        q=n/2;
        r=n%2;
        n=q;
        t[i]=r;
        i++;
    }
    for(j=0;j<8-i;j++)
    {
        if(j==4)
            printf(" ");
        printf("0");
    }
    for(i=i-1;i>=0;i--)
    {
        if(i==3)
            printf(" ");
        printf("%d",t[i]);
    }
    printf("\n");
 }
