#include <stdio.h>
#include "unistd_64.h"
#include <asm/unistd.h>

int main(void) {
	printf("ret = %d\n", syscall(309) );
	return 0;
}

