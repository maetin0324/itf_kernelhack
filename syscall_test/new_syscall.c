

#include <stdio.h>
#include <string.h>
#include "new_syscall.h"

int main()
{
	char hoge[256];
	scanf("%s", hoge);
  printf("new_syscall(530) -> %d\n", new_syscall(530,hoge,sizeof(hoge)));
  return 0;
}

