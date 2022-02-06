#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/un.h>
#include <sys/socket.h>
#include <string.h>

#define N_GOODS  40
#define N_CUSTOMERS 25
#define N_ROUNDS  100000
#define RATING 10
#define GNIAZDKO_SERWERA "/home/kskowron/.smietnik/gniazdko_serwera"
#define MAX_SIZE 64
int main()
{
int NRatings[N_GOODS];
double Ratings[N_GOODS];
int x,y,n,status;
int suma=0, pakiety=0;
int sock;
socklen_t serv_len, cli_len;
struct sockaddr_un serv_addrstr, cli_addrstr;
char message[MAX_SIZE];	/* bufor o domysl.rozmiarze */

sock = socket(PF_UNIX, SOCK_DGRAM, 0);
serv_addrstr.sun_family = AF_UNIX;
strcpy(serv_addrstr.sun_path, GNIAZDKO_SERWERA);

unlink(GNIAZDKO_SERWERA);
serv_len = sizeof(serv_addrstr);
if (bind(sock, (struct sockaddr *)&serv_addrstr, serv_len) == -1){
perror("BIND ERROR");
exit(-1);
}

//struct timespec timeout = {0, 10};

for (int i = 0; i<N_GOODS; i++)
{
Ratings[i]=0;
NRatings[i]=0;
}

int child[N_CUSTOMERS];
for (int k=0;k<N_CUSTOMERS;k++)
{
	 if((child[k]=fork())==0)
	{
	for (int i = 0; i < N_ROUNDS; i++)
	{
		int x,y;
		srand(time(NULL)+i+k);
		x = rand()%(N_GOODS);
		y = rand()%(RATING + 1 -0) + 0;
		/* transmisja */
		memcpy(message, &x, sizeof(int));
		memcpy(message+sizeof(int), &y, sizeof(int));
    		sendto(sock, message, sizeof(message),0,(struct sockaddr *)&serv_addrstr, serv_len);
	//	printf("<----- %d %d\n", message[0], message[4]);
	}
	 exit(0);
	}
}
//for (int i=0; i<N_CUSTOMERS;i++){wait(&status);};
//cli_len= sizeof(cli_addrstr);
while(1){
if(pakiety == N_CUSTOMERS*N_ROUNDS) break;
n=recvfrom(sock, &message, sizeof(message),0,(struct sockaddr *)0,0);
if (n==-1) {
     	perror("blad recvfrom");
        printf("Klient: wyslane %d, blad odczytu odpowiedzi\n", n);
    	}else
	{
  	memcpy((void *)&x, (void *)message, sizeof(int));
	memcpy((void *)&y, (void *)(message+sizeof(int)), sizeof(int));
	/* Operacje na danych */
	NRatings[x] += 1;
	Ratings[x] =((NRatings[x]-1) * Ratings[x] + y)/NRatings[x]; 
//	printf("Klient: wyslane, odebrane %d \t %d\n",x, y);
   	pakiety++;
	}

}
for (int i=0; i < N_GOODS; i++)
{
 printf("Indeks: %-2d | Ilość sztuk: %-3d | Sr ocena %-3f |\n", i, NRatings[i], Ratings[i]);
 suma = suma + NRatings[i];
}
printf("Suma towarow: %d\n", suma);
}
