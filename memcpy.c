#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<memory.h>
void print(char* str)
{
	int i = 0;
	for( i ; i < 7 ;i++)
	{
		printf(" str[%d] = %c",i, *str);
		printf(" %x", *str);
		str++;
	}
	printf("\n");

}
int main( void )
{
	char a[7] = { 'a', 'b', 'c', '\0', 'd', 'e', 'f'};
	char * b = (char *)malloc(sizeof(a));
	char * c = (char *)malloc(sizeof(a));
	char * d = (char *)malloc(sizeof(a));
	
	printf(" printing a = %s\n", a);
	strcpy(b, a);
	strncpy(c, a, 7);
	memcpy(d, a, 7);
	printf(" strcpy b = %s\n", b);
	print(b);
	printf(" strncpy c = %s\n", c);
	print(c);
	printf(" memcpy d = %s\n", d);
	print(d);
	return 0;

}
