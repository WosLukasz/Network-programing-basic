#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/wait.h>

/* Brak obslugi bledow! */

int main() {


	if(fork() == 0) {

		printf("Zombie PID: %d\n", getpid());
		exit(0);

	}

	printf("Macierz PID %d: zasypiam na 30 sek. zostawiajac potomka jako zombie\n", getpid());
	sleep(30);
	wait(NULL);
	printf("Macierz: uruchomilem wait() => zombie powinien zniknac\n");
	sleep(30);
	exit(0);

}
