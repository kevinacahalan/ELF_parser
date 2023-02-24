NAME:= elf_parser_exe
.PHONY: all
all: $(NAME)

$(NAME): Makefile stuff.h main.c
	gcc -W -Wall -Wshadow -g3 -Og -o $@ main.c -rdynamic