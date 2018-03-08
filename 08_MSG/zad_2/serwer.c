#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/ipc.h>
#include<sys/msg.h>
#include<string.h>
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

int n,nn;

void sgnhandle(int signal) {
	printf("[Serwer]: dostalem SIGINT => koncze i sprzatam...\n");
	msgctl(msqid, IPC_RMID, 0);
	exit(0);
}


int main(int argc, char * argv[]) {

	signal(SIGINT, sgnhandle);

	printf("[Serwer]: tworze klucz...");
	msqkey = ftok(argv[1], 1);
	msqkey1 = ftok(argv[1],2);

	printf(" OK (klucz1: %ld, Klucz2: %ld)\n", msqkey,msqkey1);

	printf("[Serwer]: tworze kolejke...\n");
	if( (msqid = msgget(msqkey, 0600 | IPC_CREAT | IPC_EXCL)) == -1) {
		printf("Problem z tworzeniem kolejki1!\n");
		exit(1);
	}

	
	if( (msqid1 = msgget(msqkey1, 0600 | IPC_CREAT | IPC_EXCL)) == -1) {
		printf("Problem z tworzeniem kolejki2!\n");
		exit(1);
	}

	printf(" OK (id:  %d)\n", msqid);
	printf(" OK (id1: %d)\n",msqid1);

	msg1.mtype=1;
	char *bufff="Przyjalem twoj komunikat";
	strcpy(msg1.txt,bufff);
	printf("[Serwer]: czekam na komunikaty...\n");

	while(8) {
		/* czytam komunikat dowolnego typu (4. argument = 0) */
		n = msgrcv(msqid, (void *) &msg, MY_MSG_SIZE, 0, 0);
		printf("[Serwer]: otrzymalem komunikat typy %ld rozmiaru %d(/%d): ", 
				msg.mtype,n, MY_MSG_SIZE);
		printf("%s", msg.txt);
		
		nn = msgsnd(msqid1, (void *) &msg1, MY_MSG_SIZE,0);
		if(nn==-1)
		{
			printf("Cos poszlo nie tak\n");
		}

	}
	


	return 0;

}

