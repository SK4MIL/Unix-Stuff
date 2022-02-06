#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

int main ()
{
int id;
 char polecenie[4];
    while (1) {
        printf("Podaj polecenie do wykonania [d,s,c,t,q]:\n");
        fgets(polecenie, sizeof(polecenie), stdin);
      	switch (polecenie[0]) {
	case 'q':
		exit(0);
	break;
	default:
        if (fork()==0){
            printf("Tu potomek pid=%d\n", getpid());
            /* ... wykonanie polecenia potomka ... */
            switch (polecenie[0]) {
            	case 'd': execlp("date", "date", (char *)NULL); break;
		case 's': execlp("sh", "sh", (char *)NULL); break;
		case 'c': execlp("xclock", "xclock","-update", "1",(char *)NULL); break;
		case 't': execlp("xterm", "xterm", (char *)NULL); break;
		case 'q': printf("tym zajmie sie mama\n"); break; 
           }
            exit(0); /* obowiazkowe zakonczenie potomka */
        }
	}
        printf("Tu rodzic po utworzeniu potomka.\n");
        if (polecenie[0] == 'd' || polecenie[0] == 's')
	 {
	  waitpid(id, NULL, 0);
	 }
	/* ... czekanie na potomka terminalowego ... */
        /* ... lub sprzatanie zombie okienkowego ... */
    } /* nieskonczona petla rodzica */
return 0;
}
