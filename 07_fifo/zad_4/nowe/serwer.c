#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/stat.h>
#include<string.h>
/* Brak obslugi bledow! */

struct moja{

pid_t pid;
char buff[1024];


};


int main() {

	int    fifodesc;
	char   buf[1024];
	int    chars;
	struct moja o;

	mkfifo("mojafifo", 0777);
	printf("Serwer: czekam na komunikaty klientow...\n");

	fifodesc = open("mojafifo", O_RDONLY);

	if(fifodesc != -1) {
	
		while(1) {
			chars = read(fifodesc, &o, sizeof(o));
			if(chars > 0) {
				o.buff[strlen(o.buff)] = '\0';
				
			printf("Pid: %d: %s",o.pid,o.buff);			
	
			
			
			}
		}

		close(fifodesc);

	}

	return 0;

}
