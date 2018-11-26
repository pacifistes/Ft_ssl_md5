#include <stdio.h>

int main()
{
	char *str = "lil\0";
	printf("size = %ld", sizeof(&str));
	return (0);
}

