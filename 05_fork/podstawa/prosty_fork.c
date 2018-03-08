#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>

/* bez obslugi bledow! */

int main() {

	pid_t potomek;

	if((potomek = fork()) == 0) {  /* proces potomny */
		
		printf("Potomek: PID: %d, PPID %d\n",
				getpid(), getppid());


	} else { /* proces macierzysty */
		
		printf("Macierz: PID: %d, PPID %d, PID potomka: %d\n",
				getpid(), getppid(), potomek);


	}

	printf("Napis wyswietlany przez oba procesy\n");
	exit(0);
	
}
