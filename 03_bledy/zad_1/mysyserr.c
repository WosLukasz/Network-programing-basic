#include<stdio.h>
#include<errno.h>
#include<string.h>
#include<stdlib.h>
#include<fcntl.h>

void mysyserr(char *mymsg)
{
	fprintf(stderr,"ERROR: %s (errno: %d, %s)\n)",mymsg,errno,strerror(errno));

	exit(-1);



}

int main()
{
	char buf[128];

	int ile;

	if((ile = read(77,buf,128)) == -1)
		mysyserr("blad funkcji read");



	return 0;
}
