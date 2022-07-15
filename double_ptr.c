#include<stdio.h>
void fun( int ** ptr)
{
	printf("inside the fun\n");
	ptr[0][0] = 10;
}
int main ( void )
{
	int arr[3][3] = { {1,2,3},
			  {4,5,6},
			  {7,8,0}};
	printf("before value = %d\n", arr[0][0]);
	fun(&arr);
	printf("after value = %d\n", arr[0][0]);
	return 0;
}
