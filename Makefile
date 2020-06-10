INTERPRETE = interprete
INTERPRETE_SOURCE = source/interprete.c
INTERPRETE_INCLUDE = itree.o intervalo.o cola.o shell.o
TEST_SHELL = test_shell
TEST_SHELL_SOURCE = source/test_shell.c
TEST_SHELL_INCLUDE = itree.o cola.o intervalo.o shell.o
TEST_DUMMY = test_dummy
TEST_DUMMY_SOURCE = tests/test_dummy.c
TEST_DUMMY_INCLUDE = itree.o cola.o intervalo.o
SHELL_LIB = libs/shell.c
SHELL_LIB_INCLUDE = libs/shell.h itree.o intervalo.o cola.o
ITREE = libs/itree.c
ITREE_INCLUDE = libs/itree.h cola.o intervalo.o
COLA = libs/cola.c
COLA_INCLUDE = libs/cola.h
INTERVALO = libs/intervalo.c
INTERVALO_INCLUDE = libs/intervalo.h
CFLAGS = -Wall -Wextra -Werror -std=c99 -g
PYTHON_TEST = tests/test.py
PYTHON_INTERPRETE = python
PYTHON_INTERPRETE_LINUX = python3
PYTHON_INTERPRETE_DARWIN = python3

REPEAT = 1

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

ifeq ($(OSFLAG), WIN32)
PYTHON = $(PYTHON_INTERPRETE)
endif
ifeq ($(OSFLAG), LINUX)
PYTHON = $(PYTHON_INTERPRETE_LINUX)
endif
ifeq ($(OSFLAG), OSX)
PYTHON = $(PYTHON_INTERPRETE_DARWIN)
endif

all: interprete clean

test: test_shell unit_test_python clean

test_shell: test_shell_comp clean

test_dummy: test_dummy_comp clean

interprete: $(INTERPRETE_SOURCE) $(INTERPRETE_INCLUDE)
	gcc $(CFLAGS) -o $(INTERPRETE) $(INTERPRETE_SOURCE) $(INTERPRETE_INCLUDE)

test_shell_comp: $(TEST_SHELL_SOURCE) $(TEST_SHELL_INCLUDE)
	gcc $(CFLAGS) -o $(TEST_SHELL) $(TEST_SHELL_SOURCE) $(TEST_SHELL_INCLUDE)

test_dummy_comp: $(TEST_DUMMY_SOURCE) $(TEST_DUMMY_INCLUDE)
	gcc $(CFLAGS) -o $(TEST_DUMMY) $(TEST_DUMMY_SOURCE) $(TEST_DUMMY_INCLUDE)

unit_test_python:
	$(PYTHON) $(PYTHON_TEST) $(OSFLAG) $(REPEAT)

shell.o: $(SHELL_LIB) $(SHELL_LIB_INCLUDE)
	gcc $(CFLAGS) -c $(SHELL_LIB)

itree.o: $(ITREE) $(ITREE_INCLUDE)
	gcc $(CFLAGS) -c $(ITREE)

cola.o: $(COLA) $(COLA_INCLUDE)
	gcc $(CFLAGS) -c $(COLA)

intervalo.o: $(INTERVALO) $(INTERVALO_INCLUDE)
	gcc $(CFLAGS) -c $(INTERVALO)

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
