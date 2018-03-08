#define _WITH_GETLINE
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>

/* Brak obslugi bledow! */

int main() {

	int    fifodesc;
	char   *buf = NULL;
	char buff[200];
	size_t bufsize = 80;
	size_t chars;
	pid_t ja=getpid();
	int jaa=ja;
	sprintf(buff,"%d",jaa);


//	printf("%s\n",buff);


	printf("Klient: napisz komunikat ktory chcesz przeslac do serwera:\n");
	chars = getline(&buf, &bufsize, stdin);

	strcat(buff,buf);	

//	printf("%s\n",buff);


	fifodesc = open("mojafifo", O_WRONLY);
	if(fifodesc != -1) {
	
		write(fifodesc, buff, chars+5);
		close(fifodesc);

	}

	return 0;

}
