#include<stdio.h>
#include<errno.h>
#include<string.h>
#include<stdlib.h>
#include<fcntl.h>
#include<unistd.h>
#include<sys/types.h>

void mysyserr(char *mymsg)
{
	fprintf(stderr,"ERROR: %s (errno: %d, %s) \n",mymsg,errno,strerror(errno));
	exit(-1);
}


int main(int argc, char **argv){

	char buuf[1];	
	int file=0;
	int n;

	if((file=open(argv[1],O_RDONLY)) < 0)
	{
		mysyserr("nie mozna otworzyc pliku");
	}


	while((n=read(file,buuf,1))>0)
	{
	write(1,buuf,n);
	}
close(file);
	

return 0;
}
