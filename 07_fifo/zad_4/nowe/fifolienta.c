#define _WITH_GETLINE
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>

/* Brak obslugi bledow! */

struct moja{

	pid_t pid;
	char buff[1024];

};



int main() {

	int    fifodesc;
	char   *buf = NULL;
	//char buf[200];
	size_t bufsize = 1024;
	size_t chars;

	struct moja o;

//	pid_t ja=getpid();
	//int jaa=ja;
	o.pid=getpid();
//	sprintf(buff,"%d",jaa);


//	printf("%s\n",buff);


	printf("Klient: napisz komunikat ktory chcesz przeslac do serwera:\n");
	chars = getline(&buf, &bufsize, stdin);

	strcat(o.buff,buf);	

//	printf("%s\n",buff);


	fifodesc = open("mojafifo", O_WRONLY);
	if(fifodesc != -1) {
	
		write(fifodesc, &o, sizeof(o));
		close(fifodesc);

	}

	return 0;

}
