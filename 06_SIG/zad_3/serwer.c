#include <unistd.h>
#include <stdio.h>
#include <signal.h>
#include<stdlib.h>

void obsluga(int s){
		printf("Serwer: dostalem od klienta wiadomosc typu %d\n",s-30 );
}

int main(int argc, char **argv){


	signal(SIGUSR1, obsluga);
	signal(SIGUSR2, obsluga);
	

	printf("%d\n",getpid());
				
	while(1) 
	{	
		signal(SIGUSR1, obsluga);
		signal(SIGUSR2, obsluga);
	}

	return 0;
}

