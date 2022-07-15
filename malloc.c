#include <stdlib.h>

int main(int argc, char **argv)
{
		
#if defined(__GNUC__)
# if defined(__i386__)
		__asm__("pushf\norl $0x40000,(%esp)\npopf");
# elif defined(__x86_64__)
			__asm__("pushf\norl $0x40000,(%rsp)\npopf");
# endif
#endif

				char *cptr = malloc(sizeof(int) + 1);
					
					int *iptr = (int *) ++cptr;

						*iptr = 42;

/*							short *sptr;
								int i;

									sptr = (short *)&i;

										sptr = (short *)(((char *)sptr) + 1);
											*sptr = 100; 
*/
												return 0;
}

