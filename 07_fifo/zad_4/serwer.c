#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/stat.h>

/* Brak obslugi bledow! */

int main() {

	int    fifodesc;
	char   buf[1024];
	int    chars;

	mkfifo("mojafifo", 0777);
	printf("Serwer: czekam na komunikaty klientow...\n");

	fifodesc = open("mojafifo", O_RDONLY);

	if(fifodesc != -1) {
	
		while(1) {
			chars = read(fifodesc, &buf, sizeof(buf));
			if(chars > 0) {
				buf[chars] = '\0';
				
				
				printf("Klient (PID %c%c%c%c%c) przyslal %2d bajtow: ",buf[0],buf[1],buf[2],buf[3],buf[4], chars-5);
			int i=5;
			while(buf[i]!='\0')
			{
				printf("%c",buf[i]);

				i++;
			}
			
			
			}
		}

		close(fifodesc);

	}

	return 0;

}
