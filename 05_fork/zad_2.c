#include<sys/wait.h>
#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
int main(){

	int status;
	pid_t potomek;
	if((potomek=fork())==0)
	{
		printf("(Potomek PID: %d): podaj liczbe:",getpid());
		scanf("%d",&status);
		/*potomek =getpid();*/
		exit(status);
	}
	else
	{
		wait(&status);
		printf("(Macierz PID: 62721): potomek o PID %d przekazal mi %d\n",potomek,WEXITSTATUS(status));
	}




	return 0;
}
