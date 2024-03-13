#include<stdio.h>
int main ( void )
{
    const int arr[4] = { 1, 2, 3, 4};
    int * ptr = arr+3;
    (*ptr)++;
    printf("arr[3] = %d\n", arr[3] );

    const int a = 10;
    int *aptr = &a;
    printf("aptr = %d\n", a);
    *aptr = 20;
    printf("a = %d\n", a);


    return 0;

}