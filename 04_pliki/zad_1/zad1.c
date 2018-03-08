#include <stdio.h>
#include <dirent.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>

void mysyserr(char *mymsg)
{
	fprintf(stderr,"ERROR: %s (errno: %d, %s)\n",mymsg,errno,strerror(errno));
	exit(-1);


}


 int main(int argc, char **argv) {

	DIR* dirp;
 	struct dirent* direntp;
	
	dirp = opendir(argv[1]);

	if(dirp ==-1)
	{
		mysyserr("blad funkcji opendir");

	}

	
 for(;;) {
 	direntp = readdir(dirp);
 	if(direntp == NULL) break;
	
 	if(0!= strcmp(direntp->d_name,".") && 0!=strcmp(direntp->d_name,".."))
	{		
	printf( "%s\n", direntp->d_name);
	}
	/*
	printf("%s \n",direntp->d_name);
	*/ 
	}
closedir(dirp);
												return 0;
 }
