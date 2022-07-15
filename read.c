#include<stdio.h>
int main ( void )
{
	char buff[50] = {0};
	int n = 0;
	while(n = read(0, buff, 25) > 0)
		write(1,buff,n);
	return 0;
}
