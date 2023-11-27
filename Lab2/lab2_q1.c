#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>

int main()
{
	int pid;
//	pid = fork() && fork();
	pid = fork() || fork();
	
	if(!pid)
		printf("A\n");
	else
		printf("B\n");
		
	exit(0);	
}
