#include <unistd.h>
#include <stdio.h>
#include <signal.h>
#include<sys/types.h>
#include<stdlib.h>

int main(int argc, char **argv) {

	int pid,i;


	printf("Podaj PID serwera:");
	scanf("%d",&pid);

	while(1)
	{
		printf("Podaj typ akcji:");
		scanf("%d",&i);

		if(i==0)
		{
			exit(0);
		}
		else if(i==1)
		{
			kill(pid,SIGUSR1);
		}
		else if(i==2)
		{
			kill(pid,SIGUSR2);
		}


	}


					

return 0;
}
