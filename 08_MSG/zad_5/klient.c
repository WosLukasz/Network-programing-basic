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
	int a;
	int b;
	char znak;
	int wynik;
	pid_t ja;
}	msg;

char   *buf = NULL;
size_t bufsize = MY_MSG_SIZE;
size_t chars;
int    result;
int nn;

int main(int argc, char * argv[]) {


	msg.ja=getpid();

	printf("[Klient]: tworze klucz...");
	msqkey = ftok(argv[1], 1);
	printf(" OK (klucz:  %ld)\n", msqkey);

	printf("[Klient]: otwieram kolejke...");
	if( (msqid = msgget(msqkey, 0)) == -1 ) {
		printf("Problem z otwarciem kolejki!\n");
		exit(1);
	}
	printf(" OK (id: %d)\n", msqid);

	printf("Podaj dwie liczby calkowite:\n");
	scanf("%d %d",&msg.a,&msg.b);
	printf("Podaj jakie dzialanie chcesz wykonac (+/*):\n");
	scanf("\n%c",&msg.znak);

	//printf("[Klient]: podaj komunikat ktory chcesz przeslac do serwera:\n");
	//chars = getline(&buf, &bufsize, stdin);
	
	/* przygotowanie paczki do wyslania */
	msg.mtype = 1;
	//strcpy(msg.txt, buf);
	msg.wynik=0;
	result =  msgsnd(msqid, (void *)&msg, MY_MSG_SIZE, 0);
	printf("[Klient]: wyslalem komunikat (%s), koncze.\n", 
			(result==-1)?"cos poszlo nie tak":"OK");

	nn=-100;
	while(1)
	{
		msg.mtype=2;
		nn = msgrcv(msqid, (void *) &msg,MY_MSG_SIZE,msg.ja,0);
		printf("%d\n",msg.wynik);
	
		if(nn!=-100)
		{break;}
	}


	return 0;

}
