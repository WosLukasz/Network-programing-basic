#include<sys/types.h>
#include<sys/socket.h>
#include<stdio.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<unistd.h>
#include<sys/un.h>

/* bez pelnej obslugi bledow! */

struct my_msg{
    char name[16];
	char text[255];
};

int main() {

	int sockfd;
	u_short my_port,cp;
	struct sockaddr_un server_addr;
	struct my_msg msg,msgg;
	struct sockaddr_un cliAddr;
	int cliLen;
	char *str;

	/* wybieram "unikalny" numer portu dla serwera */
	//my_port = 5000 + (getpid() % 10000);

	/* towrze gniazdo - na razie tylko czesc "protokol" */
	sockfd = socket(PF_UNIX, SOCK_DGRAM, 0);

	/* podpinam gniazdo pod  konkretny "adres-lokalny" 
	   i "proces-lokalny" (= port) */
	server_addr.sun_family	    = AF_UNIX;           /* IPv4 */
//	server_addr.sin_addr.s_addr = //inet_addr("158.75.112.121"); //juliusz na sztywno
							//	htonl(INADDR_ANY); /* dowolny (moj) interfejs */
	//server_addr.sin_port        = htons(my_port);    /* moj port */
	//
	server_addr.sun_path[0]='p';		
	server_addr.sun_path[1]='l';	
server_addr.sun_path[2]='i';	
server_addr.sun_path[3]='k';	
server_addr.sun_path[4]='\0';

cliAddr.sun_path[0]='p';
cliAddr.sun_path[1]='l';
cliAddr.sun_path[2]='i';
cliAddr.sun_path[3]='k';
cliAddr.sun_path[4]='\0';





	bind(sockfd, (struct sockaddr *)&server_addr, sizeof(server_addr));

	printf("----->%s\n",server_addr.sun_path);

	//printf("[Serwer]: Utworzone gniazdo, slucham na porcie: %d\n", my_port); 

	while(1) {

		cliLen = sizeof(cliAddr);
		recvfrom(sockfd, &msg, sizeof(msg), 0,(struct sockaddr *) &cliAddr, &cliLen );	
		//str = inet_ntoa(cliAddr.sin_addr);
		//cp = ntohs(cliAddr.sin_port);
		printf("Wiadomosc od %s: %s\n", msg.name, msg.text);

		sendto(sockfd,&msg,sizeof(msg),0,(struct sockaddr *) &cliAddr,cliLen);

	}


	return 0;

}

