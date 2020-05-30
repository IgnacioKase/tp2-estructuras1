PROG = interprete

all: shell.c itree.c itree.h cola.c cola.h
	gcc -Wall -Werror -std=c99 -Wextra shell.c itree.c cola.c -o $(PROG)