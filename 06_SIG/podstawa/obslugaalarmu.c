#include <unistd.h>
#include <stdio.h>
#include <signal.h>

void obsluga(int s){
	printf("Alarm!\n" );
}

int main(int argc, char **argv){
	unsigned int czas;

	signal(SIGALRM, obsluga);
	
	while(1) {
		
		alarm(1); /* za 1s otrzymam sygnal SIGALRM */
		
		czas = sleep(3);
		if (czas == 0) /* czy funkcja czekala 3 sekundy? */
			printf("Funkcja sleep() dziala 3 sekundy.\n");
		else 
			printf("Funkcja sleep() zostala przerwana %u sekund przed czasem.\n", czas);
		
	}

	return 0;
}

