#include<sys/types.h>
#include<sys/socket.h>
#include<stdio.h>
#include<stdlib.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<unistd.h>
#include<string.h>


/* bez pelnej obslugi bledow! */

#define MY_MSG_SIZE 127

int main(int argc, char *argv[]) {

	int sockfd;
	struct sockaddr_in server_addr;
	char  msg[MY_MSG_SIZE];
	char msg1[MY_MSG_SIZE];
	int connectresult;
	int bytes;

	/* przygotowanie adresu serwera */
	server_addr.sin_family      = AF_INET; /* IPv4 */
	 /* 1 argument = adres IP serwera */
	server_addr.sin_addr.s_addr = (inet_addr(argv[1])); 
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
	//msg[strlen(msg)-1] = '\0';

	strcpy(msg,"Lukasz Wos");
	printf("[Klient]: wysylam...");

	bytes = write(sockfd, msg, strlen(msg));
	
	printf(" (%s: %zd bajtow)\n", (bytes > 0)?"OK":"cos nie tak!", bytes);

	//recv(sockfd,msgg,strlen(msgg),0);

	read(sockfd,msg1,sizeof(msg1));

	printf("Odp od serwera: %s\n",msg1);

	memset(msg,0x0,sizeof(msg));
	memset(msg1,0x0,sizeof(msg1));

	strcpy(msg,"zielone jablko");

	write(sockfd,msg,strlen(msg));


	read(sockfd,msg1,sizeof(msg1));
	printf("Odp od serwera: %s\n",msg1);
	close(sockfd);

	return 0;

}

