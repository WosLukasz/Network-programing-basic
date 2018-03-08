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


	if(fifodesc != -1) 
	{
							
		while(1) 
		{
			chars = read(fifodesc, &buf, sizeof(buf));
			if(chars > 0) 
			{
		
				if(fork()==0)
				{
					//charz= read(desc[0],m,sizeof(m));
				
					buf[chars] = '\0';
					
				printf("Klient przyslal %2d bajtow: %s", chars-1, buf);
					sleep(10);
				}
				/*
				else
				{
					buf[chars]='\0';
					write(desc[1],buf,sizeof(buf));
				}
				*/
				
			}
		}
 
		close(fifodesc);
	}

	return 0;

}
