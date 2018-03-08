#include<sys/types.h>
#include<sys/socket.h>
#include<stdio.h>
#include<stdlib.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<unistd.h>
#include<string.h>
#include<stdlib.h>
#include<netdb.h>

/* bez pelnej obslugi bledow! */

#define MY_MSG_SIZE 127

int main(int argc, char *argv[]) {

	int sockfd;
	struct sockaddr_in server_addr;
	char  msg[MY_MSG_SIZE];
	char msgg[MY_MSG_SIZE];
	int connectresult;
	int bytes;
	struct hostent *h;
	int nn;

	h = gethostbyname(argv[1]);

	printf("%s",h->h_addr);	


	/* przygotowanie adresu serwera */
	server_addr.sin_family      = AF_INET; /* IPv4 */
	 /* 1 argument = adres IP serwera */
	server_addr.sin_addr.s_addr = (inet_addr("158.75.2.22"/*h->h_addr*/)); 
	 /* 2 argument = port serwera*/
	server_addr.sin_port        = htons((u_short)atoi(argv[2]));  

	/* towrze gniazdo - na razie tylko czesc "protokol" */
	sockfd = socket(AF_INET, SOCK_STREAM, 0);

	connectresult  =  connect(sockfd, 
		(struct sockaddr *)&server_addr, sizeof(server_addr));

	printf("[Klient]: Lacze z gniazdem TCP (%s)\n", 
		(connectresult == 0)?"OK":"blad polaczenia");


	printf("[Klient]: Podaj wiadomosc do serwera:\n> ");
	//fgets(msg, MY_MSG_SIZE, stdin);

	strcpy(msg,"GET / HTTP/1.0\n\n");


	//msg[strlen(msg)-1] = '\0';

	
	printf("[Klient]: wysylam...");

	bytes = write(sockfd, msg, strlen(msg));
	
	printf(" (%s: %zd bajtow)\n", (bytes > 0)?"OK":"cos nie tak!", bytes);

	//recv(sockfd,msgg,strlen(msgg),0);
	char buf[128];

	while((nn=read(sockfd,buf,sizeof(buf)))>0)
	{
		//write(stdout,buf,nn);
		printf("%s",buf);

	}

	printf("Odp od serwera: %s\n",msgg);

	close(sockfd);

	return 0;

}

