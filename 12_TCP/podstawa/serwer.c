#include<sys/types.h>
#include<sys/socket.h>
#include<stdio.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<unistd.h>


/* bez pelnej obslugi bledow! */

#define MY_MSG_SIZE 127

int main() {

	int sockfd, newsockfd;
	u_short my_port;
	struct sockaddr_in server_addr, client_addr;
	char msg[MY_MSG_SIZE];
	socklen_t clilen;
	int bytes;
	int clientno = 0;

	/* wybieram "unikalny" numer portu dla serwera */
	my_port = 5000 + (getpid() % 10000);

	/* tworze gniazdo i podpinam adres */
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	server_addr.sin_family	    = AF_INET;           /* IPv4 */
	server_addr.sin_addr.s_addr = htonl(INADDR_ANY); /* dowolny (moj) interfejs */
	server_addr.sin_port        = htons(my_port);    /* moj port */
	bind(sockfd, (struct sockaddr *)&server_addr, sizeof(server_addr));

	printf("[Serwer]: Utworzone gniazdo TCP, slucham na porcie: %d\n", my_port);

	listen(sockfd, 5);

	while(1) {
		++clientno;
		clilen = sizeof(client_addr);
		printf("[Serwer]: Czekam na klienta...\n");
		newsockfd = accept(sockfd, (struct sockaddr *)&client_addr, &clilen);
		printf("[Serwer]: Zglosil sie klient nr %d z IP: %s, port: %d\n", 
				clientno, inet_ntoa(client_addr.sin_addr), ntohs(client_addr.sin_port));
		bytes = read(newsockfd, msg, MY_MSG_SIZE);
		msg[bytes] = '\0';
		printf(" Komunikat klienta nr %d: %s\n", clientno, msg);
		close(newsockfd);
	}


	return 0;

}
