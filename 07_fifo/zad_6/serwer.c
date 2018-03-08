#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/stat.h>
#include<string.h>
#include<signal.h>

/* Brak obslugi bledow! */

int fifodesc, plik;

void obsluga()
{
	close(fifodesc);
	close(plik);
	unlink("/tmp/fifo_wolukasz");
	printf("Posprzatane !\n");
	exit(0);
}


int main() {

	signal(SIGINT, obsluga);

	//int    fifodesc;
	//int    plik;
	char   buf[2048];
	int    chars;

	mkfifo("/tmp/fifo_wolukasz", 0777);
	printf("Serwer: czekam na komunikaty klientow...\n");

	fifodesc = open("/tmp/fifo_wolukasz", O_RDONLY);
	plik  = open("/tmp/tablica_wolukasz", O_WRONLY | O_APPEND | O_CREAT | O_TRUNC , 0766);
	
//	printf("%d\n",fifodesc);

	if(fifodesc != -1) {
	
		while(1) {
			chars = read(fifodesc, &buf, sizeof(buf));
			if(chars > 0) {


				buf[chars] = '\0';

				char nazwa[50]={'0'}; 		
				char bufor[2048];
				int i=0;

				nazwa[0]='[';
				while(buf[i]!='#')
				{
					nazwa[i+1]=buf[i];
					i++;
				}

				nazwa[i+1]=']';
				nazwa[i+2]=':';
				nazwa[i+3]='\0';
				i++;
				int j=0;
				while(buf[i]!='\0')
				{
					bufor[j]=buf[i];
					i++;
					j++;
				}
				bufor[j]='\0';

			//	printf("%s %s\n",nazwa, bufor);
				
				write(plik,nazwa,strlen(nazwa));
				write(plik,bufor,strlen(bufor));
				



			}
		}

		close(fifodesc);
		close(plik);

	}

	return 0;

}
