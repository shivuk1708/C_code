#include<stdio.h>
#include <sys/types.h>
#include <unistd.h>

int main()
{
	// Create a child process	
	int pid = fork();

	if (pid > 0)
	{
		printf("in parent process");
		printf(" get pid - %d \n " , getpid());
		sleep(20);
	}
	// Note that pid is 0 in child process
	// and negative if fork() fails
	else if (pid == 0)
	{
		printf("in child process");
		printf(" before parent exit get pid - %d \n " , getppid());
		printf(" after parent exit get pid - %d \n " , getppid());
		exit(0);
	}

	return 0;
}

