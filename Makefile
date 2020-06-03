PROG = interprete

all: shell

shell: shell.c itree.o cola.o
	gcc -Wextra -o $(PROG) shell.c itree.o cola.o

test: tests/test.c itree.o cola.o
	gcc -Wextra -o test tests/test.c itree.o cola.o

itree.o: libs/itree.c libs/itree.h cola.o
	gcc -Wextra -c libs/itree.c

cola.o: libs/cola.c libs/cola.h
	gcc -Wextra -c libs/cola.c

clean:
	rm *.o 
