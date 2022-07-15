#include<stdio.h>
#include<unistd.h>
#include<time.h>
#include<stdlib.h>

#define STACK_FULL 10
#define STACK_EMPTY 0

void PUSH( int *ptr, int value, int *count)
{
	if( *count != STACK_FULL )
	{
		ptr[*count] = value;
		(*count)++;
		printf("thhe  pushed value in stack = %d\n", value);
	}
	else
	{
		printf(" ***** STACK IS FULL ******\n");
	}
}
void print( int * ptr, int count)
{
	int i;
	for (i = STACK_EMPTY; i < count; i++)
	{
		printf("[%d] = %d\n", i, ptr[i]);
	}
}
int  POP(int *ptr, int* count)
{
	if ( *count >= STACK_EMPTY)
	{
		int ret =  ptr[*count];
		ptr[*count] = 0;
		(*count)--;
		return ret;
	}
	else
	{
		printf(" ***** STACK IS EMPTY ****\n");
		return 0xFF;
	}
}
int main ( void )
{
	int arr[5] = {0};
	int count = STACK_EMPTY;;
	int op = 0;
	while(1)
	{
		printf("Enter the value to perform operation\n\n" "1) PUSH\n" "2) POP\n" "3) print\n" "4) count\n" "exit\n");
		scanf("%d", &op);
		switch(op)
		{
			case 1:
			{
				int value = (rand() % 100);
				PUSH(arr, value, &count);
				break;
			}

			case 2:
			{
				int pop = POP(arr, &count);
				if( 0xFF == pop)
					break;
				
				printf("pooped value is = %d\n", pop);
				break;
			}

			case 3:
				print(arr, count);
				break;
			case 4 :
			{
				printf("Total count is %d\n", count);
				break;
			}
			default :
			{
				exit(0);
				printf("***** Invalid Operation *****\n");
				break;
			}
		}
	}
	return 0;
}
