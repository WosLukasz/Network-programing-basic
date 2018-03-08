#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>

/* Brak obslugi bledow! */

int main() {


	if(fork() == 0) {

		printf("Potomek: zasypiam na 60 sekund\n");
		sleep(60);
		exit(0);

	}

	printf("Macierz: koncze i zostawiam sierote\n");
	exit(0);

}
