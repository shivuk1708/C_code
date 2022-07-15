#include<stdio.h>
struct st
{	
	int i;
	float j;
	char * ptr;
};
void main( void )
{
	struct st s = {1};
	struct st y = {1, 2.2, "hello"};
	printf(" i = %d, j = %f, ptr = %s\n", s.i, s.j, s.ptr);
	printf(" i = %d, j = %f, ptr = %s\n", y.i, y.j, y.ptr);
}
