#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/wait.h>

/* bez obslugi bledow! */

int main() {

	pid_t potomek;

	if((potomek = fork()) == 0) {  /* proces potomny */
		
		printf("Uruchamiam ls -l za pomoca exec\n");
		execlp("ls","ls","-l", 0);

		exit(0);
	} else { /* proces macierzysty */
		
		wait(0);
		
		printf("Wazny komunikat na koniec\n");


	}

	printf("Napis wyswietlany przez oba procesy\n");
	exit(0);
	
}

