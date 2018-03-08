#define _WITH_GETLINE
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>



int main() {
	FILE   *descpipe;
	char   *buf = NULL;
	size_t bufsize = 80;
	size_t chars;

	printf("Napisz zdanie:\n");
	chars = getline(&buf, &bufsize, stdin);
	
	printf("Uruchamiam wc by policzyc ile slow napisales:\n");
	descpipe = popen("wc -w","w");
	
	if(descpipe != NULL) {
		
		fwrite(buf, sizeof(char), chars, descpipe);
		fclose(descpipe);
					  	  
	}
	
	return 0;
}
