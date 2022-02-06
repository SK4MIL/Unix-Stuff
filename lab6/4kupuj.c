
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <sys/time.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/types.h>
#include <sys/times.h>

#define N_GOODS  40
#define N_CUSTOMERS 20
#define N_ROUNDS 1000000
#define RATING 10
struct shared_memory {
	int NRatings[N_GOODS];
	double Ratings[N_GOODS];
};

struct shared_memory *mem;
double real_time_used;
struct tms cpu_time_used;
clock_t val;
double cpu_systime, cpu_utime;

int main()
{
struct timeval start_real, end_real;
gettimeofday(&start_real, NULL);

int child[N_CUSTOMERS];

	int      key;       /* key to be passed to shmget() */
	int      shmflg;    /* shmflg to be passed to shmget() */
 	int      shmid;     /* return value from shmget() */
// 	if (key = (ftok ("/home/kskowron/Pulpit/lab8/shared_memory_key", 7 )) == -1) perror ("ftok");
	key = 253152;
	int size = sizeof ( struct shared_memory);
	shmflg = IPC_CREAT;

	if ((shmid = shmget ('key', size, 0660 | shmflg )) == -1) {
 		perror("shmget: shmget failed");
 		exit(1);
 	} else {
 		//(void) fprintf(stderr,"shmget: shmget returned %d\n", shmid);
 	}
int status;
int suma =0;
mem = (struct shared_memory*) shmat(shmid, NULL, 0);
if( (long int)(mem = ((struct shared_memory*) shmat(shmid, NULL, 0))) == -1){
        perror("shmat");
        exit(1);
};
for (int i=0; i<N_GOODS;i++){
mem->Ratings[i]=0; mem->NRatings[i]=0;};

for (int k=0;k<N_CUSTOMERS;k++)
{ if((child[k]=fork())==0)
{srand(getpid());
mem = (struct shared_memory*) shmat(shmid, NULL, 0);
if(mem ==(void *)-1) { perror("shmat"); exit(-1); }

int x =0;
double y=1;

for (int i = 0; i < N_ROUNDS; i++){
	srand(NULL+k+i);
	 x = rand()%(N_GOODS);
	mem->NRatings[x]++;
	 y = rand()%(RATING + 1 -0) + 0;
	mem->Ratings[x] = ((((mem->NRatings[x])-1) * mem->Ratings[x] + y) /mem->NRatings[x]);

}
exit(1);
}else {};
}
for (int i=0;i<N_CUSTOMERS;i++) {wait(&status);};
for (int i=0; i < N_GOODS; i++)
{
 printf("Indeks: %-2d | Ilość sztuk: %-3d | Sr ocena %.3f |\n", i,  mem->NRatings[i], mem->Ratings[i]);
 suma = suma + ((*mem).NRatings[i]);
}
printf("\n\tSuma zakupionych produktów: %d \n",suma);
gettimeofday(&end_real, NULL);
real_time_used = ((end_real.tv_sec - start_real.tv_sec) * 1000000u + end_real.tv_usec - start_real.tv_usec) / 1.e6;
val=times(&cpu_time_used);
double tick = (double) sysconf(_SC_CLK_TCK);
cpu_utime = ((double)(cpu_time_used.tms_utime + cpu_time_used.tms_cutime))/tick ;
cpu_systime = ((double)(cpu_time_used.tms_stime + cpu_time_used.tms_cstime))/tick ;
printf("\tCzas realny: %.3fs \n\tCzas użytkownika: %.3fs\n",real_time_used,cpu_utime);
printf("\tCzas systemu: %.3fs\n\tCałkowity czas CPU: %.3fs\n",cpu_systime,(cpu_utime+cpu_systime));

return 0;
}
