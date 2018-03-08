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

struct shmid_ds buf;

	char  *nnn;

	int nn ;

	//struct my_data **shared_data;



struct my_data {
	int  typ;
	char txt[MY_MSG_SIZE];
};

void sgnhandle(int signal) {
	printf("\n[Serwer]: dostalem SIGINT => koncze i sprzatam...");
	for(int i=0;i<nn;i++)
	{
	printf(" (odlaczenie: %s, usuniecie: %s)\n", 
			(shmdt(*shared_data[i]) == 0)        ?"OK":"blad shmdt",
			(shmctl(shmid, IPC_RMID, 0) == 0)?"OK":"blad shmctl");
	}
	exit(0);
}
/*
void obsluga()
{
	for(int i=0;i<nn;i++)
	{

		if(shared_data[i]->typ != 0)
		{
			printf("%s\n\n",shared_data[i]->txt);
		}


	}	


}
*/

int main(int argc, char * argv[]) {

	
//	struct my_data *shared_data[nn];

	nnn = argv[2];

	printf("%s\n",nnn);

	 nn = (int)nnn;

	struct my_data *shared_data[nn];

//	*shared_data = malloc(sizeof(*shared_data)*nn);


	signal(SIGINT, sgnhandle);
	signal(SIGTSTP, obsluga);

	printf("[Serwer]: tworze klucz...");
	shmkey = ftok(argv[1], 1);
	printf(" OK (klucz: %ld)\n", shmkey);

	printf("[Serwer]: tworze segment pamieci wspolnej...");
	if( (shmid = shmget(shmkey, sizeof(struct my_data)*nn, 
						0600 | IPC_CREAT | IPC_EXCL)) == -1) {
		printf(" blad shmget!\n");
		exit(1);
	}
	shmctl(shmid, IPC_STAT, &buf);
	printf(" OK (id: %d, rozmiar: %zub)\n", shmid, buf.shm_segsz);
	printf("[Serwer]: dolaczam pamiec wspolna...");
	
	for(int i=0;i<nn;i++)
	{
		shared_data[i] = (struct my_data *) shmat(shmid, (void *)0, 0);
		if(shared_data[i] == (struct my_data *)-1) {
			printf(" blad shmat!\n");
			exit(1);
		}
	

//		printf(" OK (adres: %lX)\n", (long int)shared_data[i]);
	

	printf("[Serwer]: zawartosc pamieci wspolnej:\n");
	shared_data[i]->typ = 0; /* umowa: typ == 0 oznacza: 
				 						 jeszcze nic nie ma */
	}
	int j=0;


	while(8) {	
		if(shared_data[j]->typ != 0) { 
			printf("\33[2K\r%s\n\n", shared_data[j]->txt);
			//fflush(stdout); /* trik by nadpisywanie sie udalo */

			j++;
		}
		sleep(1);
	}
	
	return 0;

}

