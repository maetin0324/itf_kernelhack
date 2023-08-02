#ifndef __LINUX_NEW_SYSCALL_H
#define __LINUX_NEW_SYSCALL_H
#include "unistd_64.h"
#include <unistd.h>
#include <asm/unistd.h>
#define new_syscall(x, hoge, len) syscall(335, x, hoge, len)
#endif
