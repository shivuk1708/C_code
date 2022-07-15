#include<stdio.h>
#include<stdlib.h>
int main ( void )
{
	int j;
	char *ch = ( char * ) malloc( sizeof(char)*100);
	printf("%d\n", scanf("%s%d", ch, &j));
	return 0;
}
