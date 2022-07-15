#include<stdio.h>
#include<stdlib.h>
#if 0
union U 
{
	int a;
	char b;
};
union U 
{
	int *a;
	char b;
};
int main ( void )
{
	union U obj;
	obj.a = (int *)malloc(5);
	printf("%p %d\n", obj.a, *obj.a);
	obj.b = 10;
	printf("%p %d %d\n", obj.a, *obj.a, obj.b);
	printf("%p %p \n", &obj.a, &obj.b);
	return 0;
}
#endif
union U
{
	int *a;
	char b;
};
int main ( void)
{
	union U *ptr = (union u *)malloc(sizeof(union U*));
	ptr->a= 10000;
	printf("%d , %d\n", (ptr->a)++, ptr->b);
	ptr->b = 20;
	printf("%d , %d\n", (ptr->a)++, ptr->b);
	return 0;
}
