#include<stdio.h>

struct S
{
	short int a : 10;
	char b:6;
};

int main ( void )
{
	printf(" size of s is %lu\n", sizeof(struct S));	
	return 0;
}
