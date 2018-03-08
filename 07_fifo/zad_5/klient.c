#define _WITH_GETLINE
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>

/* Brak obslugi bledow! */

int main() {

	int    f1,f2;
	char   *buf = NULL;
	char buff[1024];
	size_t bufsize = 80;
	size_t chars;

	printf("Klient: napisz komunikat ktory chcesz przeslac do serwera:\n");
	chars = getline(&buf, &bufsize, stdin);

	f1 = open("fifo1", O_WRONLY);
	f2 = open("fifo2", O_RDONLY);
	if(f1 != -1) {
	
		write(f1, buf, chars);
		
		while(1)
		{
			chars = read(f2,&buff,sizeof(buff));
			if(chars>0)
			{
				printf("%s\n",buff);
				break;

			}
		

		
		}		

		close(f1);

	}

	return 0;

}
