#define _wiTH_GETLINE
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/types.h>
#include<sys/ipc.h>
#include<sys/msg.h>

#include<signal.h>
#include<unistd.h>

/* Brak obslugi bledow! */

#define MY_MSG_SIZE 32

key_t msqkey, msqkey1;
int   msqid,msqid1;
struct my_msg {
	long mtype;
	char txt[MY_MSG_SIZE];
}	msg,msg1;

char   *buf = NULL;
size_t bufsize = MY_MSG_SIZE;
size_t chars;
int    result;
int nn;


int main(int argc, char * argv[]) {


	printf("[Klient]: tworze klucz...");
	msqkey = ftok(argv[1], 1);
	msqkey1 = ftok(argv[1],2);

	printf(" OK (klucz1:  %ld, Klucz2: %ld)\n", msqkey,msqkey1);

	printf("[Klient]: otwieram kolejke...\n");
	if( (msqid = msgget(msqkey, 0)) == -1 ) {
		printf("Problem z otwarciem kolejki!\n");
		exit(1);
	}

	if( (msqid1 = msgget(msqkey1, 0)) == -1 ) {
		printf("Problem z otwarciem kolejki!\n");
		exit(1);
	}

	printf(" OK (id1: %d)\n", msqid);
	printf(" OK (id2: %d)\n", msqid1);

	printf("[Klient]: podaj komunikat ktory chcesz przeslac do serwera:\n");
	chars = getline(&buf, &bufsize, stdin);
/*
	printf("[Klient]: jaki ma byc typ komunikatu (liczba calkowita dodatnia):");
	scanf("%ld",&msg.mtype);
*/
	/* przygotowanie paczki do wyslania */
	msg.mtype = 1;
	strcpy(msg.txt, buf);
	
	result =  msgsnd(msqid, (void *)&msg, MY_MSG_SIZE, 0);
	printf("[Klient]: wyslalem komunikat (%s), koncze.\n", 
			(result==-1)?"cos poszlo nie tak":"OK");
	
	nn=-100;
	while(1)
	{
		nn = msgrcv(msqid1, (void *) &msg1,MY_MSG_SIZE,0,0);
		printf("%s\n",msg1.txt);
		if(nn!=-100)
		{break;}
	}


	return 0;

}
