#include<sys/types.h>
#include<sys/socket.h>
#include<stdio.h>
#include<stdlib.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<unistd.h>
#include<string.h>
#include<sys/un.h>

/* bez pelnej obslugi bledow! */

struct my_msg{
    char name[128];
    int PIN;
    uid_t ja;
};

int main(int argc, char *argv[]) {

	int sockfd;
	struct sockaddr_un client_addr, server_addr;
	struct my_msg msg;
	int bindresult;
	ssize_t bytes;
	int kk;
	char msg1[128];

	/* przygotowanie adresu serwera */
	server_addr.sun_family      = AF_UNIX; /* IPv4 */
	

	sockfd = socket(PF_UNIX, SOCK_DGRAM, 0);


	client_addr.sun_family	    = AF_UNIX;           /* IPv4 */
//	client_addr.sin_addr.s_addr = htonl(INADDR_ANY); /* dowolny interfejs */
//	client_addr.sin_port        = htons(0);          /* dowolny port */
//	bindresult =  bind(sockfd, (struct sockaddr *)&client_addr, sizeof(client_addr));

//	printf("[Klient]: Tworze gniazdo (%s)\n", 
	//	(bindresult == 0)?"OK":"blad tworzenia gniazda");
	//
	/*
	printf("[Klient]: Podaj swoj nick:\n> "); 
	fgets(msg.name, 16, stdin);
	msg.name[strlen(msg.name)-1] = '\0';
	printf("[Klient]: Podaj wiadomosc do serwera:\n> ");
	fgets(msg.text, 255, stdin);
	msg.text[strlen(msg.text)-1] = '\0';
*/
	strcpy(msg.name,"Lukasz Wos");
	msg.PIN=5422;
	msg.ja=getuid();

	strcpy(client_addr.sun_path,"/tmp/SK.woluk");
	strcpy(server_addr.sun_path,"/tmp/SK.amroz.kolo");

/*
client_addr.sun_path[0]='p';		
client_addr.sun_path[1]='l';	
client_addr.sun_path[2]='i';	
client_addr.sun_path[3]='k';	
client_addr.sun_path[4]='\0';

server_addr.sun_path[0]='p';		
server_addr.sun_path[1]='l';	
server_addr.sun_path[2]='i';	
server_addr.sun_path[3]='k';	
server_addr.sun_path[4]='\0';	
*/


	bindresult =  bind(sockfd, (struct sockaddr *)&client_addr, sizeof(client_addr));
		if(bindresult<0)
		{
			perror("bladd");

		}
	printf("iiii\n");
	system("chmod 777 /tmp/SK.woluk");

	printf("[Klient]: wysylam...");

	bytes = sendto(sockfd, &msg, sizeof(msg), 0, 
				(struct sockaddr *)&server_addr, sizeof(server_addr));
	
	//printf(" (%s %zd bajtow)\n", (bytes > 0)?"OK":"c, bytes);

	if(bytes<0)
	{
		perror("Bload");
	}

//	while(1)
//	{
		kk=recvfrom(sockfd, &msg1,sizeof(msg1),0,NULL,NULL);
		
		printf("\n%s \n",msg1);
		//printf("Wiadomosc: %s \n",msg1.text);
/*
		if(kk>0)
		{
			break;
		}
*/
//	}


	close(sockfd);
	return 0;

}

