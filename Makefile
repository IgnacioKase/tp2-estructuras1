PROG = interprete

all: shell

shell: shell.c itree.o intervalo.o cola.o
	gcc -Wextra -o $(PROG) shell.c itree.o intervalo.o cola.o

test: tests/test.c itree.o cola.o
	gcc -Wextra -o test tests/test.c itree.o cola.o

itree.o: libs/itree.c libs/itree.h cola.o intervalo.o
	gcc -Wextra -c libs/itree.c

cola.o: libs/cola.c libs/cola.h
	gcc -Wextra -c libs/cola.c

intervalo.o: libs/intervalo.c libs/intervalo.h
	gcc -Wextra -c libs/intervalo.c

clean:
	rm *.o 
