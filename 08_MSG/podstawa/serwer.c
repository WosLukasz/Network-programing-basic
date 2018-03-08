#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/ipc.h>
#include<sys/msg.h>

#include<signal.h>
#include<unistd.h>

/* Brak obslugi bledow! */

#define MY_MSG_SIZE 32

key_t msqkey;
int   msqid;
struct my_msg {
	long mtype;
	char txt[MY_MSG_SIZE];
}	msg;

int n;

void sgnhandle(int signal) {
	printf("[Serwer]: dostalem SIGINT => koncze i sprzatam...\n");
	msgctl(msqid, IPC_RMID, 0);
	exit(0);
}


int main(int argc, char * argv[]) {

	signal(SIGINT, sgnhandle);

	printf("[Serwer]: tworze klucz...");
	msqkey = ftok(argv[1], 1);
	printf(" OK (klucz: %ld)\n", msqkey);

	printf("[Serwer]: tworze kolejke...");
	if( (msqid = msgget(msqkey, 0666 | IPC_CREAT | IPC_EXCL)) == -1) {
		printf("Problem z tworzeniem kolejki!\n");
		exit(1);
	}
	printf(" OK (id:  %d)\n", msqid);


	printf("[Serwer]: czekam na komunikaty...\n");

	while(8) {
		/* czytam komunikat dowolnego typu (4. argument = 0) */
		n = msgrcv(msqid, (void *) &msg, MY_MSG_SIZE, 0, 0);
		printf("[Serwer]: otrzymalem komunikat rozmiaru %d(/%d): ", 
				n, MY_MSG_SIZE);
		printf("%s", msg.txt);

	}
	


	return 0;

}
