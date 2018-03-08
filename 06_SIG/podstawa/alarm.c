#include <unistd.h>
#include <stdio.h>
#include <signal.h>


int main(int argc, char **argv) {

	int c;

	alarm(7); /* ustawiam budzik na 7 sek. */	

	for(c=0; ; ++c)  {
		
		printf("Dzialam: %2d sek.\n", c);	
		sleep(1);

	}

	return 0;
}

