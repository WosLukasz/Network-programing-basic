#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/shm.h>
#include<sys/msg.h>

#include<signal.h>
#include<unistd.h>

/* Brak pelnej obslugi bledow! */

#define MY_MSG_SIZE 64


key_t shmkey;
int   shmid;
struct my_data {
	int  typ;
	char txt[MY_MSG_SIZE];
} *shared_data;

void sgnhandle(int signal) {
	printf("\n[Serwer]: dostalem SIGINT => koncze i sprzatam...");
	printf(" (odlaczenie: %s, usuniecie: %s)\n", 
			(shmdt(shared_data) == 0)        ?"OK":"blad shmdt",
			(shmctl(shmid, IPC_RMID, 0) == 0)?"OK":"blad shmctl");
	exit(0);
}


int main(int argc, char * argv[]) {

	struct shmid_ds buf;


	signal(SIGINT, sgnhandle);

	printf("[Serwer]: tworze klucz...");
	shmkey = ftok(argv[1], 1);
	printf(" OK (klucz: %ld)\n", shmkey);

	printf("[Serwer]: tworze segment pamieci wspolnej...");
	if( (shmid = shmget(shmkey, sizeof(struct my_data), 
						0600 | IPC_CREAT | IPC_EXCL)) == -1) {
		printf(" blad shmget!\n");
		exit(1);
	}
	shmctl(shmid, IPC_STAT, &buf);
	printf(" OK (id: %d, rozmiar: %zub)\n", shmid, buf.shm_segsz);
	printf("[Serwer]: dolaczam pamiec wspolna...");
	shared_data = (struct my_data *) shmat(shmid, (void *)0, 0);
	if(shared_data == (struct my_data *)-1) {
		printf(" blad shmat!\n");
		exit(1);
	}
	printf(" OK (adres: %lX)\n", (long int)shared_data);


	printf("[Serwer]: zawartosc pamieci wspolnej:\n");
	shared_data->typ = 0; /* umowa: typ == 0 oznacza: 
							 jeszcze nic nie ma */

	while(8) {	
		if(shared_data->typ != 0) { 
			printf("\33[2K\r%s", shared_data->txt);
			fflush(stdout); /* trik by nadpisywanie sie udalo */
		}
		sleep(1);
	}
	


	return 0;

}
