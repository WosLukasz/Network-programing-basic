#include<stdio.h>
#include<errno.h>
#include<string.h>
#include<stdlib.h>
#include<fcntl.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<pwd.h>
#include<grp.h>

void mysyserr(char *mymsg)
{
	fprintf(stderr,"ERROR: %s (errno: %d, %s) \n",mymsg,errno,strerror(errno));
	exit(-1);
}


int main(int argc, char **argv){


	uid_t uid = getuid();
	uid_t euid = geteuid();
	gid_t gid = getgid();
	gid_t egid = getegid();

	extern char **environ;
	
	struct passwd *uinfo;
	uinfo = getpwuid(uid);
	struct passwd *euinfo;
	euinfo = getpwuid(euid);
	struct group *grinfo;
	grinfo = getgrgid(gid);
	struct group *egrinfo;
	egrinfo = getgrgid(egid);
	pid_t p_pid = getpid();
	pid_t ppid = getppid();
	pid_t p_pgrp = getpgrp();
	pid_t p_pgid = getpgid(p_pid);



	printf("Rzeczywisty uzytkownik (id , nazwa):	%u, %s\n",uid,uinfo->pw_name);
	printf("Rzeczywista grupa (id, nazwa):		%d, %s\n",gid,grinfo->gr_name);
	printf("Obowiazujacy uzytkownik (id, nazwa): 	%d, %s\n",euid,euinfo->pw_name);
	printf("Obowiazujaca grupa (id, nazwa):		%d, %s\n",egid,egrinfo->gr_name);
	printf("PID: %d, PPID: %d, PGRP: %d\n",p_pid,ppid,p_pgrp);
	printf("Zmienne srodowiskowe: \n");
	
	int i=0;

	while(environ[i]!=NULL)
	{	
		printf("%s ",environ[i]);
		i++;

	}



return 0;
}
