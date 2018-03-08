#include<sys/types.h>
#include<sys/socket.h>
#include<stdio.h>
#include<stdlib.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<unistd.h>
#include<string.h>


/* bez pelnej obslugi bledow! */

struct my_msg{
    char name[16];
	char text[255];
};

int main(int argc, char *argv[]) {

	int sockfd;
	struct sockaddr_in client_addr, server_addr;
	struct my_msg msg;
	int bindresult;
	ssize_t bytes;
	pid_t potomek;

	/* przygotowanie adresu serwera */
	server_addr.sin_family      = AF_INET; /* IPv4 */
	 /* 1 argument = adres IP serwera */
	server_addr.sin_addr.s_addr = (inet_addr(argv[1])); 
	 /* 2 argument = port serwera*/
	server_addr.sin_port        = htons((u_short)atoi("5002"));  

	/* towrze gniazdo - na razie tylko czesc "protokol" */
	sockfd = socket(AF_INET, SOCK_DGRAM, 0);

	/* podpinam gniazdo pod  "adres-lokalny" 
	   i "proces-lokalny" (= port) 
	   Ten krok mozna pominac (dla sesji bezpolaczenioweji) */
	client_addr.sin_family	    = AF_INET;           /* IPv4 */
	client_addr.sin_addr.s_addr = htonl(INADDR_ANY); /* dowolny interfejs */
//	client_addr.sin_port        = htons(0);          /* dowolny port */
	client_addr.sin_port        = htons((u_short)atoi("5002"));  

	bindresult =  bind(sockfd, (struct sockaddr *)&client_addr, sizeof(client_addr));

	printf("[Klient]: Tworze gniazdo (%s)\n", 
		(bindresult == 0)?"OK":"blad tworzenia gniazda");

	potomek = fork();


	if(potomek == 0 )
	{
		while(1)
		{
			recvfrom(sockfd,&msg,sizeof(msg),0,NULL,NULL);

			printf("Wiadomosc od %s: %s\n", msg.name, msg.text);	
		}



	}else
	{
		while(1)
		{
			strcpy(msg.name,"costam");
			printf("[ja]>");
			fgets(msg.text, 255, stdin);
			msg.text[strlen(msg.text)-1] = '\0';

	
			printf("[Klient]: wysylam...");

			bytes = sendto(sockfd, &msg, sizeof(msg), 0, 
				(struct sockaddr *)&server_addr, sizeof(server_addr));
	
			printf(" (%s: %zd bajtow)\n", (bytes > 0)?"OK":"cos nie tak!", bytes);
		}
	}
	

	close(sockfd);
	return 0;

}
