#include<stdlib.h>
#include<stdio.h>
#include<unistd.h>

int main(){

	for(int i=0;i<60;i++)
	{
		printf("Dzialam od %d sek.\n",i+1);
		sleep(1);

	}


return 0;
}
