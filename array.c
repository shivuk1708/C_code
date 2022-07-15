#include<stdio.h>
void fun( int * ptr)
{
	printf("inside the fun\n");
	ptr[0] = 10;
}
int main ( void )
{
	int n;
	scanf("%d", &n);
	int arr2[n];
	int arr[3] = {1,2,3};
	printf("before value = %d\n", arr[0]);
	fun(arr);
	printf("after value = %d\n", arr[0]);
	return 0;
}
