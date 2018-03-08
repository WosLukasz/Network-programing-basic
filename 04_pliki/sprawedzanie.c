#include<stdio.h>
#include<sys/stat.h>

int main(){

struct stat abc;

printf("%lu",sizeof(abc.st_mode));




return 0;
}
