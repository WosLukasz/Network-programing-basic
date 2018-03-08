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
	pid_t myid;
	char txt[MY_MSG_SIZE];
}	msg;

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
	msqkey = ftok(argv[1], 1);
	printf(" OK (klucz:  %ld)\n", msqkey);

	printf("[Klient]: otwieram kolejke...");
	if( (msqid = msgget(msqkey, 0)) == -1 ) {
		printf("Problem z otwarciem kolejki!\n");
		exit(1);
	}
	printf(" OK (id: %d)\n", msqid);

	printf("MOJE PID [%d]\n",myid);
	printf("[Klient]: podaj komunikat ktory chcesz przeslac do serwera:\n");
	chars = getline(&buf, &bufsize, stdin);
	
	/* przygotowanie paczki do wyslania */
	msg.mtype = 1;
	strcpy(msg.txt, buf);
	
	result =  msgsnd(msqid, (void *)&msg, MY_MSG_SIZE, 0);
	printf("[Klient]: wyslalem komunikat (%s), koncze.\n", 
			(result==-1)?"cos poszlo nie tak":"OK");

	nn=-100;
	while(1)
	{
		nn = msgrcv(msqid, (void *) &msg,MY_MSG_SIZE,myid,0);
		printf("%s\n",msg.txt);
	
		if(nn!=-100)
		{break;}
	}


	return 0;

}
