#include<stdio.h>
#include<errno.h>
#include<string.h>
#include<stdlib.h>
#include<fcntl.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<dirent.h>
#include<grp.h>
#include<pwd.h>
#include<time.h>
#include<limits.h>


void mysyserr(char *mymsg)/*funkcja odpowiadajaca za bledy*/
{
	fprintf(stderr,"ERROR: %s (errno: %d, %s) \n",mymsg,errno,strerror(errno));
	exit(-1);
}


int main(int argc, char **argv){

	
		DIR* dirp; /*zmienna do otwierania katalogu */
		struct dirent* direntp;
		struct stat buf;/*zmienna strukturalna plku*/
		if((dirp = opendir("."))<0)
		{
			mysyserr("blad funkcji opendir");
		}/*otwieranie aktualnego katalogu do zmiennej dirp*/
		char st[500],c;
		int i;
		struct passwd *uinfo;/*zmienna strukturalna oddpowiadajaca za info o uzytkowniku*/
		struct group *grinfo;/*zmienna strukturalna odpowiadajaca za info o gruie*/
		struct tm *inff;
		char buffer[80];/*zmienna do ktorej zapisujemy czas modyfikacji itp*/
		char buffer2[100];/*zmienna do ktorej zapisujemy sciezke */
		char *napis;/*zmienna do ktorej wpisywany jest typ pliku*/
		char pwd[1024];/*zmienna odpowiadajaca za odczytanie pwd pliku*/

	if(argc >2)
	{
		printf("Za duzo parametrow, podaj jeden parametr lub nie podawaj zadnego\n");
		exit(-1);
	}

	if(argc==1)/*jezeli nie podamy parametru do funkcji*/
	{
		for(;;)/*petla do otwierania kazdego kolejnego pliku*/
		{
			if((direntp = readdir(dirp))<0)/*czyta plik*/
			{
				mysyserr("blad funkcji readdir");
			}
			if(direntp == NULL) break;/*jesli nie ma juz wiecej plikow do przetowrzenia to wychpodzi z petli*/
			
			/* zeruje tablice*/
			for(i=0;i<500;i++)
			{
				st[i]=0;

			}


			st[0]='.';
			st[1]='/';

			strcat(st,direntp->d_name);

			
			if(lstat(st,&buf)<0)/*pobiera info o pliku*/
			{
				mysyserr("blad funkcji lstat");
			}
			 	
			if((uinfo = getpwuid(buf.st_uid))==NULL)/*pobiera info o wlascicielu plkiu*/
			{
				mysyserr("blad funkcji getpwuid");
			}
			if((grinfo = getgrgid(buf.st_gid))==NULL)/*pobiera info o grupie wlasciciela*/
			{
				mysyserr("blad funkcji getgrgid");
			}

			/*sprawdzanie jakiego typu jest plik*/
			if(S_ISDIR(buf.st_mode))
			{
				c='d';
			}else if(S_ISLNK(buf.st_mode))
			{
				c='l';
			}else if(S_ISBLK(buf.st_mode))
			{
				c='b';
			}else if(S_ISCHR(buf.st_mode))
			{
				c='c';
			}else if(S_ISFIFO(buf.st_mode))
			{
				c='p';
			}else if(S_ISSOCK(buf.st_mode))
			{
				c='s';
			}else
			{
				c='-';
			}


			inff= localtime(&buf.st_mtime);/*zapisywanie czasu*/
			strftime(buffer,80,"%d %b %H:%M",inff);/*formatowanie wydruku czasu*/



			
			printf("%c",c);

			printf( (buf.st_mode & S_IRUSR) ? "r" : "-");
			printf( (buf.st_mode & S_IWUSR) ? "w" : "-");
			if(buf.st_mode & S_ISUID)
			{
				printf("s");
			}else
			{
				printf( (buf.st_mode & S_IXUSR) ? "x" : "-");
			}
			printf( (buf.st_mode & S_IRGRP) ? "r" : "-");
			printf( (buf.st_mode & S_IWGRP) ? "w" : "-");
			if(buf.st_mode & S_ISGID)
			{
				printf("s");
			}else
			{
			printf( (buf.st_mode & S_IXGRP) ? "x" : "-");
			}
			printf( (buf.st_mode & S_IROTH) ? "r" : "-");
			printf( (buf.st_mode & S_IWOTH) ? "w" : "-");
			if(buf.st_mode & S_ISVTX)
			{
				printf("t");
			}
			else
			{
				printf( (buf.st_mode & S_IXOTH) ? "x" : "-");
			}
			printf(" %d %s %s %ld	%s ",buf.st_nlink,uinfo->pw_name,grinfo->gr_name,buf.st_size,buffer);
			
	
			printf("%s",direntp->d_name);
			

			if(c=='l')/*wykonywane w przypadku gdy plik jest dowiazaniem symbolicznym*/
			{
				if((readlink(st,buffer2,100))<0)/*czyta do buffer2 na jaki plik wskazuje dowiazanie*/
				{
					mysyserr("blad funkcji readlink");
				}
				printf(" -> %s\n",buffer2);
			}
			else
			{
				printf("\n");
			}

		}

		closedir(dirp);
	}else
	{
		
			if(lstat(argv[1],&buf)<0)/*pobiera info o pliku*/
			{
				mysyserr("blad funkcji lstat, plik ktory podajesz moze nie istniec");
			}

			if(S_ISDIR(buf.st_mode))
			{
				napis="katalog";
			}else if(S_ISLNK(buf.st_mode))
			{
				napis = "link symboliczny";
			}else if(S_ISBLK(buf.st_mode))
			{
				napis = "plik specjalny (blokowy)";
			}else if(S_ISCHR(buf.st_mode))
			{
				napis="plik specjalny (znakowy)";
			}else if(S_ISFIFO(buf.st_mode))
			{
				napis="FIFO";
			}else if(S_ISSOCK(buf.st_mode))
			{
				napis="gniazdo";
			}else
			{
				napis="zwykly plik";
			}	
		
			printf("Informacje o %s:\n",argv[1]);
			printf("Typ pliku:	%s\n",napis);
			printf("Sciezka:	%s/%s\n",getcwd(pwd,1024),argv[1]);
			
			if(S_ISLNK(buf.st_mode))
			{

			printf("Wskazuje na:	%s\n",realpath(argv[1],NULL));
			}
			
			printf("Rozmiar:	%ld bajtow\n",buf.st_size);
			printf("uprawnienia: ");
		
			printf( (buf.st_mode & S_IRUSR) ? "r" : "-");
			printf( (buf.st_mode & S_IWUSR) ? "w" : "-");
			if(buf.st_mode & S_ISUID)
			{
				printf("s");
			}else
			{
				printf( (buf.st_mode & S_IXUSR) ? "x" : "-");
			}
			printf( (buf.st_mode & S_IRGRP) ? "r" : "-");
			printf( (buf.st_mode & S_IWGRP) ? "w" : "-");
			if(buf.st_mode & S_ISGID)
			{
				printf("s");
			}else
			{
			printf( (buf.st_mode & S_IXGRP) ? "x" : "-");
			}
			printf( (buf.st_mode & S_IROTH) ? "r" : "-");
			printf( (buf.st_mode & S_IWOTH) ? "w" : "-");
			if(buf.st_mode & S_ISVTX)
			{
				printf("t");
			}
			else
			{
				printf( (buf.st_mode & S_IXOTH) ? "x" : "-");
			}
			
			
			inff= localtime(&buf.st_atime);
			strftime(buffer,80,"%d %B %Y roku o %H:%M:%S",inff);

			printf("\nOstatnio uzywany	%s",buffer);
			
			inff= localtime(&buf.st_mtime);
			strftime(buffer,80,"%d %B %Y roku o %H:%M:%S",inff);

			printf("\nOstatnio modyfikowany	%s",buffer);

			inff= localtime(&buf.st_ctime);
			strftime(buffer,80,"%d %B %Y roku o %H:%M:%S",inff);

			printf("\nOstatnio zmieniony stan	%s\n",buffer);


			if(strcmp(napis,"zwykly plik")==0 && (buf.st_mode & S_IXUSR) == 0 && (buf.st_mode & S_IXGRP) == 0 && (buf.st_mode & S_IXOTH)== 0 )
			{
				char buuuf[84];
				int file=0;
				int ile=0;

				if((file=open(argv[1],O_RDONLY)) <0)
				{
					mysyserr("nie mozna otworzyc pliku");
				}
					
				printf("Poczatek zawartosci:\n");
				ile=read(file,buuuf,84);

				write(1,buuuf,ile);
				printf("\n");
				
				close(file);


			}



	}



return 0;
}
