cmd_/home/tsukubataro/itf_kernelhack/my_procfs/TimeProcfs.o := ld -m elf_x86_64 -z noexecstack   -r -o /home/tsukubataro/itf_kernelhack/my_procfs/TimeProcfs.o @/home/tsukubataro/itf_kernelhack/my_procfs/TimeProcfs.mod  ; ./tools/objtool/objtool --hacks=jump_label --hacks=noinstr --hacks=skylake --ibt --orc --retpoline --rethunk --static-call --uaccess --prefix=16  --link  --module /home/tsukubataro/itf_kernelhack/my_procfs/TimeProcfs.o

/home/tsukubataro/itf_kernelhack/my_procfs/TimeProcfs.o: $(wildcard ./tools/objtool/objtool)
