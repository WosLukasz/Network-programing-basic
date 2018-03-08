#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/stat.h>

/* Brak obslugi bledow! */

int main() {

	int    f1,f2;
	char   buf[1024];
	int    chars;

	mkfifo("fifo1", 0777);
	mkfifo("fifo2", 0777);
	printf("Serwer: czekam na komunikaty klientow...\n");

	f1 = open("fifo1", O_RDONLY);
	f2 = open("fifo2", O_WRONLY);

	if(f1 != -1) {
	
		while(1) {
			chars = read(f1, &buf, sizeof(buf));
			if(chars > 0) {
				buf[chars] = '\0';
				printf("Klient przyslal %2d bajtow: %s\n", chars-1, buf);
				
				
				int m;

				sscanf(buf,"%d",&m);

				m=m*2;

				sprintf(buf,"%d",m);

			//	printf("%s\n",buf);

				write(f2,buf,sizeof(buf));

			}
		}

		close(f1);
		close(f2);

	}

	return 0;

}
