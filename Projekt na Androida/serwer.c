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

	int sd, rc, newSd, cliLen,n ;
	struct sockaddr_in cliAddr, servAddr;
	FILE   *descpipe;
	char   buf[MAX_MSG];
	size_t chars = 2048;
	
	/*tworzy gniazdo*/

	sd = socket ( AF_INET, SOCK_STREAM, 0);

	if ( sd < 0 ) 
	{

		perror("Blad socket ");

		return ERROR;
	}
	
	/*ustawia dane struktury */

	servAddr.sin_family = AF_INET;
	servAddr.sin_addr.s_addr = htonl(INADDR_ANY);
	servAddr.sin_port = htons(SERVER_PORT);

	/*naklada adres na gniazo*/

	if( bind ( sd, (struct sockaddr *) &servAddr,sizeof(servAddr ) ) <0 )
	{

		perror("Blad bind ");
		return ERROR;
	}


	listen(sd,5);

	while(1) 
	{
		/*akceptuje polaczenia klientow*/

		printf("\n%s: Czekam na dane na porcie TCP %u\n",
		argv[0],SERVER_PORT);
		cliLen = sizeof(cliAddr);
		newSd = accept( sd, (struct sockaddr *)
					&cliAddr, &cliLen );

		if ( newSd < 0 ) 
		{

			perror("Blad accept ");
			return ERROR;
		}


		pid_t potomek = fork();

		if(potomek==0)
		{	

			memset(line,0x0,MAX_MSG);
		
			/* przyjmuje zlecenie od klienta */
			
			n = recv( newSd, line, MAX_MSG, 0 );

			if ( n < 0 ) 
			{

				perror (" Blad czytania z gniazda");
				return ERROR;
			}
	
			/*potomek przygotowuje komende*/
			memset(buf,0x0,MAX_MSG);
	
			char command[2048];

			strcpy(command , "getprop ");
			strcat(command,line); 
			printf("%s\n",command);
			descpipe = popen(command,"r");
		
			if(descpipe != NULL) 
			{
				fread(buf, sizeof(char), MAX_MSG, descpipe);

				printf("Wynik: %s\n",buf);			
				fclose(descpipe);
			}

			/*wysyła odpowiedź i konczy swoje dzialanie*/

			rc = send ( newSd, buf , sizeof(buf)+1, 0 );
			close(newSd);
			exit(0);

		}else
		{
			/*serwer wraca do czekanai na nastepnego klienta*/
			continue;
			close(newSd);
		}
	}

return 0;
}
