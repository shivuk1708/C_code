#include<stdio.h>
#include<stdlib.h>
void fun( int * ptr)
{
	printf("**inside  fun ptr = %p\n", ptr); 
	ptr = (int *)malloc(sizeof(int));
	printf("**inside  fun ptr = %p\n", ptr); 
}
int main ( void )
{
	int i = 10;
	int *ptr = &i;
	printf("before fun ptr = %p\n", ptr); 
	fun(ptr);
	printf("after fun ptr = %p\n", ptr); 
	*ptr = 8;
	printf("*ptr = %d\n", *ptr); 
	return 0;
}
