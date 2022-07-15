#include<stdio.h>
#include<string.h>
#include<dirent.h>
int main ( void )
{
	DIR *dir = opendir(".");
	if( dir ==NULL)
	{
		printf(" not opened\n");
		return ;
	}
	struct dirent *entity ;
	entity = readdir(dir);
	while(entity != NULL)
	{
		printf("%hhd   %s\n", entity->d_type, entity->d_name);
		entity = readdir(dir);
	}
	
	close(dir);
	return 0;
}
