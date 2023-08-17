#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <error.h>
#include <sys/ioctl.h>
#include "emojiDriver.h"

int main(void) {
  char c;
  int fd;

  if ((fd = open("/dev/emoji_device", O_RDWR)) == -1) {
    perror("open");
    exit(1);
  }

  if (write(fd, ":bow:", 6) < 0) {
    perror("write");
    close(fd);
    exit(1);
  }

  while (read(fd, &c, 1) == 1) {
    printf("%c", c);
  }
  printf("\n");

  close(fd);
  return 0;
}