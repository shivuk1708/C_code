#include <stdio.h>

static void print_i(void) {
	static int i = 42;

	printf("%d, %d, %d, %d\n",i++, i, ++i, i++);
}

int main(int argc, char *argv[]) {
	print_i();
	//print_i();
	//print_i();

	return 0;
}
