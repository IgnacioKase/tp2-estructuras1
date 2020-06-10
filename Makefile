INTERPRETE = interprete
TEST_SHELL = test_shell
TEST = test_dummy
REPEAT = 1

CFLAGS = -Wall -Wextra -Werror -std=c99 -g
OSFLAG 				:=
ifeq ($(OS),Windows_NT)
	OSFLAG +=WIN32
else
	UNAME_S := $(shell uname -s)
ifeq ($(UNAME_S),Linux)
		OSFLAG +=LINUX
endif
ifeq ($(UNAME_S),Darwin)
		OSFLAG +=OSX
endif
endif

OSFLAG := $(firstword $(subst :, ,$(OSFLAG)))

all: interprete clean

test: test_shell unit_test_python clean

test_shell: test_shell_comp clean

test_dummy: test_dummy_comp clean

interprete: source/interprete.c itree.o intervalo.o cola.o shell.o
	gcc $(CFLAGS) -o $(INTERPRETE) source/interprete.c itree.o intervalo.o cola.o shell.o

test_shell_comp: source/test_shell.c itree.o cola.o intervalo.o cola.o shell.o
	gcc $(CFLAGS) -o $(TEST_SHELL) source/test_shell.c itree.o cola.o intervalo.o shell.o

test_dummy_comp: tests/test_dummy.c itree.o cola.o intervalo.o cola.o
	gcc $(CFLAGS) -o $(TEST) tests/test_dummy.c itree.o cola.o intervalo.o

unit_test_python:
ifeq ($(OSFLAG), WIN32)
	python tests/test.py $(OSFLAG) $(REPEAT)
endif
ifeq ($(OSFLAG), LINUX)
	python3 tests/test.py $(OSFLAG) $(REPEAT)
endif
ifeq ($(OSFLAG), OSX)
	python3 tests/test.py $(OSFLAG) $(REPEAT)
endif

shell.o: libs/shell.c libs/shell.h itree.o intervalo.o cola.o
	gcc $(CFLAGS) -c libs/shell.c

itree.o: libs/itree.c libs/itree.h cola.o intervalo.o
	gcc $(CFLAGS) -c libs/itree.c

cola.o: libs/cola.c libs/cola.h
	gcc $(CFLAGS) -c libs/cola.c

intervalo.o: libs/intervalo.c libs/intervalo.h
	gcc $(CFLAGS) -c libs/intervalo.c

clean:
ifeq ($(OSFLAG), WIN32)
	del *.o
endif
ifeq ($(OSFLAG), LINUX)
	rm *.o
endif
ifeq ($(OSFLAG), OSX)
	rm *.o
endif
