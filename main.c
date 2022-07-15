#include<stdio.h>
#include<stdlib.h>
int fun ( void )
{
	int a = 100;
	return a;
}
void  _start()
{
	int a = fun();
	printf ("%d\n", a);
	exit(0);
}
