#include<stdio.h>
int global;
int main ( void )
{
	printf("%d\n", global);
	return 0;
}
int global = 10000000;
