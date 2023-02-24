NAME:= elf_parser_exe
.PHONY: all
all: $(NAME)

$(NAME): Makefile stuff.h main.c
	gcc -W -Wall -Wstrict-prototypes -Wmissing-prototypes -Wshadow -g3 -Og -o $@ main.c