#define _WITH_GETLINE
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/types.h>
#include<sys/ipc.h>
#include<sys/shm.h>
#include<unistd.h>
#include<sys/sem.h>
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

	struct sembuf buff;

	union semun arg;

	arg.val=1;

	buff.sem_num=0;
	buff.sem_op = -1;
	buff.sem_flg=0;
	int semafor;
	key_t semkey;

	printf("[Klient]: tworze klucz...");
	shmkey = ftok(argv[1], 1);
	semkey = ftok(argv[1],2);
	printf(" OK (klucz:  %ld)\n", shmkey);


	semafor = semget(semkey,1,0);


//	semctl(semafor,0,SETVAL,arg);

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
	
	while(!semctl(semafor,0,GETVAL)){};
	
	
	
	semop(semafor,&buff,1);
	
	
	printf(" OK (adres: %lX)\n", (long int)shared_data);
	printf("[Klient]: biezaca zawartosc pamieci wspolnej: ");
	if(shared_data->typ == 0) printf("PUSTO\n");
	else printf("\n%s\n", shared_data->txt);


	printf("[Klient]: podaj komunikat ktory chcesz wpisac do pamieci wspolnej:\n");
//	getline(&buf, &bufsize, stdin);
	int nn;

	nn=read(0,&shared_data->txt,sizeof(shared_data->txt));

	/* wpisywanie do pamieci dzielonej */
	shared_data->typ = 1;
	shared_data->txt[nn-1] = '\0'; /* techniczne: usuwam koniec linii */
	//strcpy(shared_data->txt, buf);
	
	
	buff.sem_op=1;
	semop(semafor,&buff,1);
	
	printf("[Klient]: wpisalem komunikat do pamieci wspolnej\n");

	shmdt(shared_data);

	return 0;

}

