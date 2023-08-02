cmd_/home/tsukubataro/my_procfs/MyProcfs.mod := printf '%s\n'   my_procfs.o | awk '!x[$$0]++ { print("/home/tsukubataro/my_procfs/"$$0) }' > /home/tsukubataro/my_procfs/MyProcfs.mod
