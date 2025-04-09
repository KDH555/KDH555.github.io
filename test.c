#include <stdio.h>

int main()
{
	int fd1, fd2, fd3;

	fd1 = fileno(stdin);
	fd2 = fileno(stdout);
	fd3 = fileno(stderr);

	printf("file descriptor for sidin: %d\n", fd1);
	printf("file descriptor for stdout: %d\n", fd2);

	return 0;
}
