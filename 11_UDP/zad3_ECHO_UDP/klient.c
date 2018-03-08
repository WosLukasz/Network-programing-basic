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
	struct my_msg msg,msg1;
	int bindresult;
	ssize_t bytes;
	int kk;

	/* przygotowanie adresu serwera */
	server_addr.sin_family      = AF_INET; /* IPv4 */
	 /* 1 argument = adres IP serwera */
	server_addr.sin_addr.s_addr = (inet_addr(argv[1])); 
	 /* 2 argument = port serwera*/
	server_addr.sin_port        = htons((u_short)atoi(argv[2]));  

	/* towrze gniazdo - na razie tylko czesc "protokol" */
	sockfd = socket(AF_INET, SOCK_DGRAM, 0);

	/* podpinam gniazdo pod  "adres-lokalny" 
	   i "proces-lokalny" (= port) */
	client_addr.sin_family	    = AF_INET;           /* IPv4 */
	client_addr.sin_addr.s_addr = htonl(INADDR_ANY); /* dowolny interfejs */
	client_addr.sin_port        = htons(0);          /* dowolny port */
	bindresult =  bind(sockfd, (struct sockaddr *)&client_addr, sizeof(client_addr));

	printf("[Klient]: Tworze gniazdo (%s)\n", 
		(bindresult == 0)?"OK":"blad tworzenia gniazda");
	printf("[Klient]: Podaj swoj nick:\n> "); 
	fgets(msg.name, 16, stdin);
	msg.name[strlen(msg.name)-1] = '\0';
	printf("[Klient]: Podaj wiadomosc do serwera:\n> ");
	fgets(msg.text, 255, stdin);
	msg.text[strlen(msg.text)-1] = '\0';

	
	printf("[Klient]: wysylam...");

	bytes = sendto(sockfd, &msg, sizeof(msg), 0, 
				(struct sockaddr *)&server_addr, sizeof(server_addr));
	
	printf(" (%s %zd bajtow)\n", (bytes > 0)?"OK":"cos nie tak!", bytes);

	while(1)
	{
		kk=recvfrom(sockfd, &msg1,sizeof(msg1),0,NULL,NULL);
		
		printf("Nick: %s \n",msg1.name);
		printf("Wiadomosc: %s \n",msg1.text);

		if(kk>0)
		{
			break;
		}

	}
	



	close(sockfd);
	return 0;

}

