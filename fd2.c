#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

void main()
{
	int fd;
	char str[] = "Hello socket!\n";

	fd = open("hello.txt", O_CREAT | O_WRONLY);
	if (fd < 0) {
		perror("could not open hello.txt");
		exit(1);
	}
    if (write(fd, str, strlen(str)) < 0) {
		perror("failed to write");
		exit(1);
	}
	close(fd);
}
