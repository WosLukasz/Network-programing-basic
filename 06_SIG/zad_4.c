#include <unistd.h>
#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/types.h>

void obsluga(int signal) {

		printf("Ojciec: dostalem od syna wiadmosc typu %d\n", signal-29);
}

int main(int argc, char **argv) {

	pid_t potomek;

	if((potomek=fork())==0)
	{
		while(1)
		{
			sleep(1);
			kill(getppid(),SIGUSR1);
			kill(getppid(),SIGUSR2);		
		}
	}
	else
	{
	//	wait(0);

		while(1)
		{
			signal(SIGUSR1,obsluga);
			signal(SIGUSR2,obsluga);

		}



	}
	
	
	
	
	
	return 0;
}
