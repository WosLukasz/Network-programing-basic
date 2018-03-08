#include <sys/ipc.h>
#include <sys/msg.h>
#include <stdio.h>
#include <sys/types.h>
#include <string.h>

/* Brak pelnej obslugi bledow! */

int main() {
	int   msqid;
	key_t msqkey;
	struct msqid_ds buf;
	struct my_msg {
	    long mtype;
		char txt[10];
	}  msg;

	msqkey = ftok("statystyki.c", 1);
		  
	if( (msqid = msgget(msqkey, 0666 | IPC_CREAT)) == -1) {
		printf("Funkcja msgget zwrocila blad!\n");
		return -1;
	}

	printf("Utworzona/otwarta kolejka, klucz: %ld, id: %d\n", msqkey, msqid);


	msg.mtype  = 9;
	strcpy(msg.txt, "Test");

	printf("Wysylam testowy komunikat... (%s)\n", 
		 (msgsnd(msqid, &msg, sizeof(msg.txt), 0)==-1)?"Blad!":"OK");

	//msgrcv(msqid, &msg2, 10, 0, 0);
	//printf("[[%lu, %s]]\n", msg2.mtype, msg2.txt);

	msgctl(msqid, IPC_STAT, &buf);
			

	printf("Pojemnosc kolejki: %lu bajtow\n", buf.msg_qbytes);
	printf("Biezaca liczba bajtow w kolejce:      %lu\n", buf.msg_cbytes);
	printf("Biezaca liczba komunikatow w kolejce: %lu\n", buf.msg_qnum);
	printf("PID ostatnio wywolujacego msgsnd:     %d\n",  buf.msg_lspid);
	printf("PID ostatnio wywolujacego msgrcv:     %d\n",  buf.msg_lrpid);

	//msgctl(msqid, IPC_RMID, 0);
	return 0;
}
