#include<sys/types.h>
#include<sys/socket.h>
#include<stdio.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<unistd.h>
#include<stdlib.h>
#include<signal.h>
#include<string.h>
/* bez pelnej obslugi bledow! */

#define MY_MSG_SIZE 127

int main() {

	int sockfd, newsockfd;
	u_short my_port;
	struct sockaddr_in server_addr, client_addr;
	char msg[MY_MSG_SIZE];
	char odp[MY_MSG_SIZE];
	socklen_t clilen;
	int bytes;
	int clientno = 0;
	pid_t potomek;

	signal(SIGCHLD,SIG_IGN);

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
		
		if((potomek=fork())==0)
		{
			while(1)
			{
				memset(odp,0x0,sizeof(odp));
				printf("[Serwer PID: %d ]:",getpid());	
				printf("Zglosil sie klient nr %d z IP: %s, port: %d\n", 
					clientno, inet_ntoa(client_addr.sin_addr), ntohs(client_addr.sin_port));
				bytes = read(newsockfd, msg, MY_MSG_SIZE);
				msg[bytes] = '\0';
				printf("[Serwer PID: %d ]:",getpid());	
				printf(" Komunikat klienta nr %d: %s\n", clientno, msg);
			
				if(msg[strlen(msg)-1]!='?')
				{
					strcpy(odp,"pytaj o co chcesz");
				}else if(msg[0]=='c' && msg[1]=='z' && msg[2]=='y')
				{
					strcpy(odp,"nie wiem");
				}else if(strcmp(msg,"<koniec>")==0)
				{
					printf("Klient nr %d zakonczyl polaczenie\n",clientno);
					exit(0);
				}else
				{
					strcpy(odp,"dlaczego?");
				}
				
				printf("[Serwer PID: %d ]:",getpid());	
				printf(" Odsylam klientowi nr %d: %s\n",clientno,odp);
			
				write(newsockfd,odp,sizeof(odp));
				/*
				if(send(newsockfd, &odp, sizeof(odp)+1,0)<0)
				{
					perror(" Blad send");


				}

				*/
			}
			close(newsockfd);
			exit(0);
		}else
		{
			close(newsockfd);
			continue;
		}



	}


	return 0;

}

