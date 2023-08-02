cmd_/home/tsukubataro/kthread/KthreadModule.o := ld -m elf_x86_64 -z noexecstack   -r -o /home/tsukubataro/kthread/KthreadModule.o @/home/tsukubataro/kthread/KthreadModule.mod  ; ./tools/objtool/objtool --hacks=jump_label --hacks=noinstr --hacks=skylake --ibt --orc --retpoline --rethunk --static-call --uaccess --prefix=16  --link  --module /home/tsukubataro/kthread/KthreadModule.o

/home/tsukubataro/kthread/KthreadModule.o: $(wildcard ./tools/objtool/objtool)
