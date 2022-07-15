#include<stdio.h>
int main ( void )
{
	int i = 0;
	int j;
	int a = 0;
	int b;
	j = i++;
	b = ++a;
	printf(" i = %d, j = %d\n", i, j);
	printf(" a = %d, b = %d\n", a, b);
	return 0;
}
