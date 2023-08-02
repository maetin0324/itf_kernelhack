#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <error.h>
#include <sys/ioctl.h>
#include "emojiDriver.h"

int main()
{
	int fd;
	int emoji_state = 1;

	if ((fd = open("/dev/emoji_device0", O_RDWR)) < 0) perror("open");

	if (ioctl(fd, EMOJI_DEVICE_SET_VALUES, &emoji_state) < 0) perror("ioctl_set");
	if (ioctl(fd, EMOJI_DEVICE_GET_VALUES, &emoji_state) < 0) perror("ioctl_get");

	printf("state = %d\n", emoji_state);

	if (ioctl(fd, EMOJI_DEVICE_CLEAR_VALUES) < 0) perror("ioctl_clear");
	if (ioctl(fd, EMOJI_DEVICE_GET_VALUES, &emoji_state) < 0) perror("ioctl_get2");

	printf("state2 = %d\n", emoji_state);

	if (close(fd) != 0) perror("close");
	return 0;
}


