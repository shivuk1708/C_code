#include<stdio.h>
void fun2( void )
{
	printf("in fun2 \n");
	int *ptr = NULL;
	*ptr = 10;
}
void fun( void )
{
	printf(" in fun1\n");
	fun2();
}
int main ( void )
{
	fun();
	return 0;
}
