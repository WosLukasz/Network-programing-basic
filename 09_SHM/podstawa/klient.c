#define _WITH_GETLINE
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/types.h>
#include<sys/ipc.h>
#include<sys/shm.h>


/* Brak pelnej obslugi bledow! */

#define MY_MSG_SIZE 64

key_t shmkey;
int   shmid;
struct my_data {
    int  typ;
	char txt[MY_MSG_SIZE];
} *shared_data;

char   *buf = NULL;
size_t bufsize = MY_MSG_SIZE;


int main(int argc, char * argv[]) {


	printf("[Klient]: tworze klucz...");
	shmkey = ftok(argv[1], 1);
	printf(" OK (klucz:  %ld)\n", shmkey);

	printf("[Klient]: otwieram segment pamieci wspolnej...");
	if( (shmid = shmget(shmkey, 0, 0)) == -1 ) {
		printf(" blad shmget\n");
		exit(1);
	}
	printf(" OK (id: %d)\n", shmid);
	printf("[Klient]: dolaczam pamiec wspolna...");
	shared_data = (struct my_data *) shmat(shmid, (void *)0, 0);
	if(shared_data == (struct my_data *)-1) {
		printf(" blad shmat!\n");
		exit(1);
	}
	printf(" OK (adres: %lX)\n", (long int)shared_data);
	printf("[Klient]: biezaca zawartosc pamieci wspolnej: ");
	if(shared_data->typ == 0) printf("PUSTO\n");
	else printf("\n%s\n", shared_data->txt);


	printf("[Klient]: podaj komunikat ktory chcesz wpisac do pamieci wspolnej:\n");
	getline(&buf, &bufsize, stdin);
	
	/* wpisywanie do pamieci dzielonej */
	shared_data->typ = 1;
	buf[strlen(buf)-1] = '\0'; /* techniczne: usuwam koniec linii */
	strcpy(shared_data->txt, buf);
	
	
	printf("[Klient]: wpisalem komunikat do pamieci wspolnej\n");

	shmdt(shared_data);

	return 0;

}
