#include<stdlib.h>
#include<stdio.h>
char **environ;

int main(int argc, char *argv[])
{
	int count = 0;

	printf("\n");
	
	while(environ[count] != NULL)
	{
	      printf("[%s] :: \n", environ[count]);
	      count++;
	}

	return 0;
}
