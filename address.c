#include<stdio.h>
int main ( void )
{
	char a;
	int b;
	float c;
	char d;
	short int e;
	double f;
	char g;
	int h;
	double i;
	printf(" a = %p\n b = %p\n c = %p\n d = %p\n e = %p\n f = %p\n g = %p\n h = %p\n i = %p\n", &a, &b, &c, &d, &e, &f, &g, &h, &i);
	printf(" a = %lld\n b = %lld\n c = %lld\n d = %lld\n e = %lld\n f = %lld\n g = %lld\n h = %lld i = %lld\n\n", &a, &b, &c, &d, &e, &f, &g, &h, &i);
	return 0;
}
