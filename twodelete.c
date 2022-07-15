#include<stdio.h>
#include<stdlib.h>
int main ( void )
{
	int * ptr = (int *)malloc(4);
	int *ptr1 = ptr;
	int *ptr2 = ptr;
	free(ptr1);
	free(ptr2);
	return 0;
}
