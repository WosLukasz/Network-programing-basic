#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <pwd.h>
#include <grp.h>

int main(int argc,char *argv[],char **envp){
    uid_t uid,euid;
    gid_t gid,egid;
    struct passwd* uinfo;
    struct passwd* euinfo;
    struct group* grinfo;
    struct group* egrinfo;
    pid_t p_pid,p_ppid,p_pgrp,p_pgid;

    char **env;
    char *thisEnv;

    uid = getuid();
    euid = geteuid();
    gid = getgid();
    egid = getegid();
    uinfo = getpwuid(uid);
    euinfo = getpwuid(euid);
    grinfo = getgrgid(gid);
    egrinfo = getgrgid(egid);
    p_pid = getpid();
    p_ppid = getppid();
    p_pgrp = getpgrp();
    p_pgid = getpgid(p_pid);

    printf("Rzeczywisty uzytkownik (ID,Nazwa):   %d, %s\n",uid,uinfo->pw_name);
    printf("Rzeczywista grupa (ID,Nazwa):        %d, %s\n",gid,grinfo->gr_name);
    printf("Obowiazujacy uzytkownik (ID,Nazwa):  %d, %s\n",euid,euinfo->pw_name);
    printf("Obowiazujaca grupa (ID,Nazwa):       %d, %s\n",egid,egrinfo->gr_name);
    printf("PID: %d, PPID: %d, PGRP: %d\n",p_pid,p_ppid,p_pgrp);
    printf("Zmienne strodowiskowe:\n");
    
    /*for(env = envp;*env != 0;env++){
        printf("%s, ",*env);
    }*/

    printf("\n");

    return 0;
}
