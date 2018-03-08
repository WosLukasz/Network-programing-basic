#include<stdio.h>
#include<netdb.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>


/* brak obslugi bledow! */

int main(int argc, char * argv[]) {

	struct hostent *host;
	char   **bufs;
	struct in_addr *addr;
	struct in_addr  moja;
	

	//host = gethostbyname(argv[1]);
	
			
	moja.s_addr =  inet_addr (argv[1]);	
	
	
	
	host = gethostbyaddr(&moja,4,AF_INET);
	
	
	
	printf("Pola struktury in_addr:\n");
	printf("h_name: %s\n", host->h_name);
	printf("h_aliases: ");
	for(bufs = host->h_aliases; *bufs != NULL; ++bufs)
		printf("%s; ", *bufs);
	
	printf("\nh_addrtype: %d(%s)\n", host->h_addrtype, 
			(host->h_addrtype == AF_INET)?"AF_INET":"nieznany typ adresu");
	
	printf("h_length: %d\n", host->h_length);
	printf("h_addr_list: ");
	for(bufs = host->h_addr_list; *bufs != NULL; ++bufs) {
		addr = (struct in_addr *) *bufs;
		printf("%s; ", inet_ntoa(*addr));
	}

	printf("\n");
	return 0;

}
