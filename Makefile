INTERPRETE = interprete
TEST_SHELL = test_shell
TEST = test

OSFLAG 				:=
ifeq ($(OS),Windows_NT)
	OSFLAG += WIN32
else
	UNAME_S := $(shell uname -s)
	ifeq ($(UNAME_S),Linux)
		OSFLAG += LINUX
	endif
	ifeq ($(UNAME_S),Darwin)
		OSFLAG += OSX
	endif
endif

all: interprete clean

test_shell: test_shell_comp clean

test: test_comp clean

interprete: source/interprete.c itree.o intervalo.o cola.o shell.o
	gcc -Wextra -o $(INTERPRETE) source/interprete.c itree.o intervalo.o cola.o shell.o

test_shell_comp: source/test_shell.c itree.o cola.o intervalo.o cola.o shell.o
	gcc -Wextra -o $(TEST_SHELL) source/test_shell.c itree.o cola.o intervalo.o shell.o

test_comp: tests/test.c itree.o cola.o intervalo.o cola.o
	gcc -Wextra -o $(TEST) tests/test.c itree.o cola.o intervalo.o

shell.o: libs/shell.c libs/shell.h itree.o intervalo.o cola.o
	gcc -Wextra -c libs/shell.c

itree.o: libs/itree.c libs/itree.h cola.o intervalo.o
	gcc -Wextra -c libs/itree.c

cola.o: libs/cola.c libs/cola.h
	gcc -Wextra -c libs/cola.c

intervalo.o: libs/intervalo.c libs/intervalo.h
	gcc -Wextra -c libs/intervalo.c

clean:= $(OSFLAG)
ifeq ($(OSFLAG),WIN32)
	del *.o
else ifeq ($(OSFLAG),LINUX)
	rm *.o
	echo $(OSFLAG)
else ifeq ($(OSFLAG),OSX)
	rm *.o
endif
	
