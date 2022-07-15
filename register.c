#include<stdio.h>
int main ( void )
{
	register int a = 100;
	printf("%d %p\n", a, &a);
	return 0;
}
