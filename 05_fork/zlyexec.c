#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>
#include<sys/wait.h>

int main() {

	if(fork()==0)
	{
		printf("Uruchamiam ls -l za pomoca exec\n");
		execlp("ls","ls","-l", 0);
		printf("Kiedy to sie wyswietli?\n");
		exit(0);
	}else
	{
		wait(NULL);
		printf("Wazny komunikat na koniec\n");
		exit(0);
	}
		
return 0;

}

