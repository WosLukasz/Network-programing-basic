#define _WITH_GETLINE
#include<sys/types.h>
#include<sys/socket.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<unistd.h>
#include<signal.h>
#include<netdb.h>
#define PORT 15112

/* -----------------------FUNKCJOALNOSCI--------------------------------
 * 1. MOZNA WPISYWAC ZAROWNO NAZWE DOMENOWA ORAZ ADRES IP
 * 2. MOZNA PODAWAC NICK JAKO TRZECI PARAMETR					 */


struct my_msg{
	char text[255];
};


	int sockfd , bytes;
	struct sockaddr_in server_addr,wysylany;
	struct my_msg msg,buf;
	struct hostent *h;
	pid_t potomek;
	size_t bufsize = 255;
	int info;
	int pipedesc[2];
	char *adres;
	char *nick;

void koniec();
int sprawdz(char *arg);
void obsluga()
{
	//printf("###\n");
	fflush(stdin);
	fflush(stdout);
	sleep(30);

}

int main(int argc, char *argv[]) {


	pipe(pipedesc);

	/* towrze gniazdo - na razie tylko czesc "protokol" */
	sockfd = socket(AF_INET, SOCK_DGRAM, 0);

	if(sockfd<0)
	{
		perror(" Blad funkcji socket");
		exit(-1);
	}

	if(argc==3)
	{
		nick=argv[2];
	}
	else
	{
		nick="ja";
	}

	/* podpinam gniazdo pod  konkretny "adres-lokalny" 
	   i "proces-lokalny" (= port) */
	server_addr.sin_family	    = AF_INET;           /* IPv4 */
	server_addr.sin_addr.s_addr = htonl(INADDR_ANY); /* dowolny (moj) interfejs */
	server_addr.sin_port        = htons((u_short)atoi("15112"));    /* moj port */


	/*tworze dane do wyslania*/
	wysylany.sin_family = AF_INET;


	if(sprawdz(argv[1])==1)
	{
		//printf("adr\n");
		wysylany.sin_addr.s_addr =inet_addr(argv[1]);

		adres = argv[1];
	}else
	{
		//printf("nazw\n");
		struct hostent *h;
		struct in_addr *addr;

		//moja.s_addr = inet_addr(argv[1]);

		h = gethostbyname(argv[1]);
		char **bufff;

		bufff=h->h_addr_list;
		addr = (struct in_addr *) *bufff;
		
		adres = inet_ntoa(*addr);

		wysylany.sin_addr.s_addr = inet_addr(adres);

	}
	
	
	wysylany.sin_port = htons((u_short)atoi("15112")); 

	info = bind(sockfd, (struct sockaddr *)&server_addr, sizeof(server_addr));

	if ( info < 0 ) 
	{
		perror (" Blad bind");
		exit(-1);
	}


	printf("Rozpoczynam czat z %s Napisz <koniec> by zakonczyc czat.\n",adres);
	
//	printf("[%s]>",nick);
	strcpy(buf.text,"s#p#e#c#j#a#l#n#i#e#");

	bytes = sendto(sockfd, &buf, sizeof(buf), 0,(struct sockaddr *)&wysylany, sizeof(wysylany));



	potomek = fork();

	if(potomek<0)
	{
		perror(" Blad tworzenia potomka");
		exit(-1);
	}


		if(potomek==0)
		{

			while(1)
			{

				memset(&msg,0x0,bufsize);

				bytes = recvfrom(sockfd,&msg, sizeof(msg), 0, NULL, NULL);

				if ( bytes < 0 ) 
				{

					perror (" Blad recvfrom");
					exit(-1);
				}


				if(strcmp(msg.text,"s#p#e#c#j#a#l#n#i#e#")==0  )
				{
					kill(getppid(),SIGUSR1);
						
					printf("\n[%s dolaczyl do rozmowy]\n",adres);
				
	
					printf("[%s]>",nick);
					fflush(stdout);

				}else if(strcmp(msg.text,"<koniec>")==0)
				{
			
					kill(getppid(),SIGUSR1);

					printf("\n[%s zakonczyl rozmowe]\n",adres);

					fflush(stdin);
					printf("[%s]>",nick);
fflush(stdout);
				
				}else
				{
						
					kill(getppid(),SIGUSR1);

					printf("\n[%s]> %s\n",adres, msg.text);
					
					kill(getppid(),SIGUSR1);

				
					printf("[%s]>",nick);
fflush(stdout);
				
				}
			}


		}
		else
		{
			while(1)
			{
				signal(SIGUSR1,obsluga);

				memset(&buf.text,0x0,bufsize);
			

				printf("[%s]> ",nick);	
		
				fgets(buf.text,bufsize,stdin);	
					
				
				buf.text[strlen(buf.text)-1]='\0';


				if(strcmp(buf.text,"<koniec>")==0)
				{
					koniec();
				}
			
				//strcat(buf.text,"\n[ja]>");
			//	printf("::%s\n",buf.text);

				bytes = sendto(sockfd, &buf, sizeof(buf), 0,(struct sockaddr *)&wysylany, sizeof(wysylany));


				if ( bytes < 0 ) 
				{
					perror (" Blad send");
					exit(-1);
				}

			}

		}

		close(sockfd);

	

	return 0;

}


void koniec()
{
	strcpy(buf.text,"<koniec>");
	bytes = sendto(sockfd, &buf, sizeof(buf), 0,(struct sockaddr *)&wysylany, sizeof(wysylany));
//	shutdown(sockfd,0);
	close(sockfd);
	kill(potomek,SIGKILL);

	exit(0);



}

int sprawdz(char *arg)
{
	int licz=0;
	for(int i=0;i<strlen(arg);i++)
	{
		if(arg[i]=='.')
		{
		//	printf(".");
			licz++;
		}
		else if((char)arg[i]>47 && (char)arg[i]<58)
		{
		//	printf("<c>");
		}
		else if(arg[i]!='\0' ||arg[i]!='\n' )
		{
			return 0;
		}

	}

	if(licz==3)
	{
		return 1;
	}else
	{
		return 0;
	}

}

