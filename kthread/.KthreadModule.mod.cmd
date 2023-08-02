cmd_/home/tsukubataro/kthread/KthreadModule.mod := printf '%s\n'   kthread.o | awk '!x[$$0]++ { print("/home/tsukubataro/kthread/"$$0) }' > /home/tsukubataro/kthread/KthreadModule.mod
