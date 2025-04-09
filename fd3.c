#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>

int main()
{
	int fd;
	char buf[20];
	ssize_t read_sz;

	fd = open("hello.txt", O_RDONLY);
	if (fd < 0) {
		perror("could not open");
		exit(1);
	}
	read_sz = read(fd, buf, sizeof(buf));
	if (read_sz < 0) {
		perror("failed to read from file");
		exit(1);
	}
	printf("Read from file: %s\n", buf);

	close(fd);
}
