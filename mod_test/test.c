#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>

int main()
{
	char buff[56];
	int fd0_A, fd0_B, fd1_A;

	if ((fd0_A = open("/dev/emoji_device0", O_RDWR)) < 0) perror("open");
	if ((fd0_B = open("/dev/emoji_device0", O_RDWR)) < 0) perror("open");
	if ((fd1_A = open("/dev/emoji_device1", O_RDWR)) < 0) perror("open");

	if (write(fd0_A, ":bow:", 16) < 0) perror("write");
	if (write(fd0_B, "0_B", 16) < 0) perror("write");
	if (write(fd1_A, "1_A", 16) < 0) perror("write");

	if (read(fd0_A, buff, 16) < 0) perror("read");
	printf("%s\n", buff);
	if (read(fd0_B, buff, 16) < 0) perror("read");
	printf("%s\n", buff);
	if (read(fd1_A, buff, 16) < 0) perror("read");
	printf("%s\n", buff);

	if (close(fd0_A) != 0) perror("close");
	if (close(fd0_B) != 0) perror("close");
	if (close(fd1_A) != 0) perror("close");

	return 0;
}


