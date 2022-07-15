#include <stdio.h> 
#include <string.h> 
#include <unistd.h> 
#include <stdlib.h> 
int main() 
{
	//char *str = "Hello World";
	//char *ptr = (char *)malloc(strlen(str));
	int i = 0;
	//strcpy(ptr, str);
	char *ptr = (char *)malloc(50*sizeof(char));
	scanf("%s", ptr);
	printf("%s\n", ptr);
	for( i = 0; i< strlen(ptr); i++)
	{
		char ch = ptr[i];
		int j = i+1;
		for ( ; j < strlen(ptr); j++)
		{
	    	if( ptr[i] == ptr[j])
	    	{
		    	memmove(&ptr[j], &ptr[j]+1, strlen(&ptr[j]));
		    }
		}
	}
	printf("%s\n", ptr);
	return 0;
}  
