#include <stdio.h>
#include <stdlib.h>

int main()
{
	char * x = malloc(10);
	char * y =NULL;
	x[20] = 'a';
	printf("hello world\n");
	printf(" char %c \n", x[20]);
	printf(" char %c \n", y[1000]);
	return 0;
}

