cmd_/home/tsukubataro/emoji_dev/EmojiDeviceModule.o := ld -m elf_x86_64 -z noexecstack   -r -o /home/tsukubataro/emoji_dev/EmojiDeviceModule.o @/home/tsukubataro/emoji_dev/EmojiDeviceModule.mod  ; ./tools/objtool/objtool --hacks=jump_label --hacks=noinstr --hacks=skylake --ibt --orc --retpoline --rethunk --static-call --uaccess --prefix=16  --link  --module /home/tsukubataro/emoji_dev/EmojiDeviceModule.o

/home/tsukubataro/emoji_dev/EmojiDeviceModule.o: $(wildcard ./tools/objtool/objtool)
