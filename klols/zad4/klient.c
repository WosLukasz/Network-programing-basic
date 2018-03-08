#define _WITH_GETLINE
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

key_t msqkey;
int   msqid;
struct my_msg {
	long mtype;
	char txt[64];
	pid_t myid;

}	msg;

struct my_msg1{
	long mtype;
	int kod;
} msg1;

char   *buf = NULL;
size_t bufsize = MY_MSG_SIZE;
size_t chars;
int    result;
int nn;
pid_t myid;

int main(int argc, char * argv[]) {

	myid = getpid();
	msg.myid = myid;
	printf("[Klient]: tworze klucz...");
	msqkey = ftok(argv[1], 7);
	printf(" OK (klucz:  %ld)\n", msqkey);

	printf("[Klient]: otwieram kolejke...");
	if( (msqid = msgget(msqkey, 0)) == -1 ) {
		printf("Problem z otwarciem kolejki!\n");
		exit(1);
	}
	printf(" OK (id: %d)\n", msqid);

	printf("MOJE PID [%d]\n",myid);
//	printf("[Klient]: podaj komunikat ktory chcesz przeslac do serwera:\n");
//	chars = getline(&buf, &bufsize, stdin);
	
	/* przygotowanie paczki do wyslania */

	msg.mtype = 61;
	strcpy(msg.txt, "Lukasz Wos");
	
	result =  msgsnd(msqid, (void *)&msg, sizeof(msg)-sizeof(long int), 0);
	printf("[Klient]: wyslalem komunikat (%s), koncze.\n", 
			(result==-1)?"cos poszlo nie tak":"OK");

	nn=-100;
	while(1)
	{
		nn = msgrcv(msqid, (void *) &msg1,sizeof(msg1)-sizeof(long int),myid,0);
		printf("%d\n",msg1.kod);
	
		if(nn!=-100)
		{break;}
	}


	return 0;

}
