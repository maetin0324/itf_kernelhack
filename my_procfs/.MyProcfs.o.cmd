cmd_/home/tsukubataro/my_procfs/MyProcfs.o := ld -m elf_x86_64 -z noexecstack   -r -o /home/tsukubataro/my_procfs/MyProcfs.o @/home/tsukubataro/my_procfs/MyProcfs.mod  ; ./tools/objtool/objtool --hacks=jump_label --hacks=noinstr --hacks=skylake --ibt --orc --retpoline --rethunk --static-call --uaccess --prefix=16  --link  --module /home/tsukubataro/my_procfs/MyProcfs.o

/home/tsukubataro/my_procfs/MyProcfs.o: $(wildcard ./tools/objtool/objtool)
