#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <unistd.h>
#include <sys/wait.h>

int main()
{
srand(time(NULL));
int N_GOODS = 40;
int N_CUSTOMERS =1;
int N_ROUNDS = 1000000;
int RATING = 10;
int NRatings[N_GOODS];
double Ratings[N_GOODS];
int x =0;
double y=1;
int suma =0;
for (int i=0; i<N_GOODS;i++){ NRatings[i]=0;};
for (int i=0; i<N_GOODS; i++){ Ratings[i]=0;};
for (int i = 0; i < N_ROUNDS; i++)
{
	 x = rand()%(N_GOODS);
	 NRatings[x]++;
	 y = rand()%(RATING + 1 -0) + 0;
	 Ratings[x] = (((NRatings[x]-1) * Ratings[x] + y) /NRatings[x]);
}
for (int i=0; i < N_GOODS; i++)
{
 printf("Indeks: %d | Ilość sztuk: %d | Sr ocena %3f |\n", i,  NRatings[i], Ratings[i]);
 suma = suma + NRatings[i];
}
printf("%d \n",suma);
return 0;
}
