#include<stdio.h>
#include<unistd.h>
#include<string.h>
#include<stdlib.h>

/* Brak obslugi bledow! */

int main() {

	int pipedescs[2];
	int pipedesc2[2];
//	char msg[] = "Przychodzi baba do lekarza a lekarz tez baba\0";
	char buf[80];
	int chars;
	pipe(pipedescs);
	pipe(pipedesc2);
	pid_t potomek;
	char *n;
	int m;

	if( (potomek=fork()) == 0 ) { /* potomek  */
		close(pipedescs[1]);
		close(pipedesc2[0]);

		chars = read(pipedescs[0], buf, sizeof(buf));

		buf[chars]='\0';
		
		sscanf(buf,"%d",&m);

		m=2*m;

		sprintf(buf,"%d",m);

		write(pipedesc2[1],buf,sizeof(buf));


	}else
	{
		close(pipedescs[0]);
		close(pipedesc2[1]);
		
		printf("Podaj liczbe: ");
		scanf("%s",n);

		write(pipedescs[1],n,strlen(n));

		chars= read(pipedesc2[0],n,sizeof(n));

		n[chars]='\0';

		printf("%s\n",n);
	
	}



return 0;
}
