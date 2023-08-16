#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <error.h>
#include <sys/ioctl.h>
#include "emojiDriver.h"

int main()
{
	char buff[56];
	int fd0_A, fd0_B;
	int emoji_state;
	int emoji_state_one = 1;

	if ((fd0_A = open("/dev/emoji_device0", O_RDWR)) < 0) perror("open");
	if ((fd0_B = open("/dev/emoji_device0", O_RDWR)) < 0) perror("open");

	if (ioctl(fd0_A, EMOJI_DEVICE_GET_VALUES, &emoji_state) < 0) perror("ioctl_get");
	printf("state0 = %d\n", emoji_state);

	if (write(fd0_A, ":bow:", 6) < 0) perror("write");
	if (write(fd0_B, "0_B", 4) < 0) perror("write");

	if (read(fd0_A, buff, 16) < 0) perror("read");
	printf(":bow: > /dev/emoji_device0 ->%s\n", buff);
	if (read(fd0_B, buff, 16) < 0) perror("read");
	printf("0_B > /dev/emoji_device0 -> %s\n", buff);

	if (ioctl(fd0_A, EMOJI_DEVICE_SET_VALUES, &emoji_state_one) < 0) perror("ioctl_set");
	if (ioctl(fd0_A, EMOJI_DEVICE_GET_VALUES, &emoji_state) < 0) perror("ioctl_get");

	printf("state1 = %d\n", emoji_state);

	if (read(fd0_A, buff, 16) < 0) perror("read");
	printf(":bow: > /dev/emoji_device0 ->%s\n", buff);

	if (ioctl(fd0_A, EMOJI_DEVICE_CLEAR_VALUES) < 0) perror("ioctl_clear");
	if (ioctl(fd0_A, EMOJI_DEVICE_GET_VALUES, &emoji_state) < 0) perror("ioctl_get2");

	printf("state2 = %d\n", emoji_state);

	if (close(fd0_A) != 0) perror("close");
	if (close(fd0_B) != 0) perror("close");

	return 0;
}


