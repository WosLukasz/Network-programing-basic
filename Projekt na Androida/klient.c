#define _WITH_GETLINE
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <stdio.h>
#include <unistd.h>
#include<stdlib.h>
#include<string.h>
#define SUCCESS 0
#define ERROR 1
#define END_LINE 0x0
#define SERVER_PORT 1500
#define MAX_MSG 2048
char line[MAX_MSG];

int main (int argc, char *argv[]) {

	

	if(argc!=3)
	{
		printf("Uzycie programu: ./klient [IP] [parametr getprop] \n");
		exit(1);
	}


	int sd, rc, i,n;
	struct sockaddr_in localAddr, servAddr;
	struct hostent* h;

	/*tworzenie gnazda*/

	sd = socket(AF_INET, SOCK_STREAM, 0);

	if ( sd < 0 ) 
	{

		perror("Blad socket ");
		exit(1);
	}

	/* klient używa adresu IP serwera */
	memset( &servAddr, 0, sizeof(servAddr) );
	servAddr.sin_family = AF_INET;
	servAddr.sin_addr.s_addr = inet_addr(argv[1]);
	servAddr.sin_port = htons(SERVER_PORT);

	/* klient używa nazwy serwera */
	h = gethostbyname(argv[1]);
	
	if( h == NULL ) 
	{

		printf("Nieznany host '%s'\n", argv[1]);
		exit(1);

	}

	servAddr.sin_family = h->h_addrtype;
	memcpy ( (char *) &servAddr.sin_addr.s_addr,h->h_addr_list[0], h->h_length );
	servAddr.sin_port = htons(SERVER_PORT);

	
	/*laczenie sie z serwerem*/

	rc = connect( sd,(struct sockaddr *) &servAddr,sizeof(servAddr) );

	if( rc < 0 ) 
	{

		perror("Blad connect ");
		exit(1);
	}

	/*wysylanie wiadomosci do serwera*/
	
	rc = send(sd, argv[2], strlen(argv[2]) + 1, 0);

	if( rc < 0 ) 
	{

		perror("Blad send ");
		exit(1);
	}

	memset( line, 0x0, MAX_MSG);

	/*odbieranie wiadomosci z serwera*/

	n = recv(sd, line, MAX_MSG, 0 );

	printf("Wynik:\n%s\n",line);

	if ( n < 0 ) 
	{
		perror (" Blad czytania z gniazda");
		return ERROR;
	}

	shutdown ( sd, 1 );

return 0;
}
