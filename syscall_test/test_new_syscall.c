

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "new_syscall.h"

int main(int argc, char *argv[])
{
  int x  = atoi(argv[1]);
	char* hoge = argv[2];
  printf("new_syscall(%d, %s) -> %ld\n", x, hoge, new_syscall(x, hoge, strlen(hoge)));
  return 0;
}

