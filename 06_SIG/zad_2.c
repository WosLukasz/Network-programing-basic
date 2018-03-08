#include<stdlib.h>
#include<stdio.h>
#include<unistd.h>
#include<signal.h>

void obsluga(int signal) {

		printf("  Przechwytuje sygnal nr %d\n", signal);
}


int main(){

	signal(SIGINT, obsluga);
	signal(SIGTSTP, SIG_IGN);	
	signal(SIGQUIT, obsluga);

		
	signal(SIGKILL, obsluga); /* nie mozna przechwycic */

	signal(SIGUSR1, obsluga);


	for(int i=0;i<60;i++)
	{
		printf("Dzialam od %d sek.\n",i+1);
		sleep(1);

	}


return 0;
}
