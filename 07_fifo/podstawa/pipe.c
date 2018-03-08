#include<stdio.h>
#include<unistd.h>
#include<string.h>

/* Brak obslugi bledow! */

int main() {

	int pipedescs[2];
	char msg[] = "Przychodzi baba do lekarza a lekarz tez baba\0";
	char buf[80];
	int chars;

	pipe(pipedescs);

	if( fork() == 0 ) { /* potomek  */
		close(pipedescs[1]);
		chars = read(pipedescs[0], buf, sizeof(buf));
		printf("Syn:    ojciec opowiedzial mi dowcip:\n%s\n(%d bajtow w pipe)\n",
				buf, chars);

	} else { /* przodek */
		printf("Ojciec: opowiadam dowcip synowi...\n");
		close(pipedescs[0]);
		write(pipedescs[1], msg, strlen(msg));
	}

	return 0;

}
