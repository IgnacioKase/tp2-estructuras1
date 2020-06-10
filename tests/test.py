from subprocess import check_output
import sys
import time
import os
import errno
import random

TEST_CASES_FOLDER = "tests/test_cases/"
TEST_IN_PATH = TEST_CASES_FOLDER
TEST_OUT_PATH = TEST_CASES_FOLDER + "out_"
TEST_OUT_INFO_PATH = TEST_CASES_FOLDER + "all_tests_info.txt"

def insert(a, b):
    return "i [%s,%s]\n" % (a, b)


def delete(a, b):
    return "e [%s,%s]\n" % (a, b)


def overlap(a, b):
    return "? [%s,%s]\n" % (a, b)


def bfs():
    return "bfs\n"


def dfs():
    return "dfs\n"


def salir():
    return "salir\n"


def help():
    return "help\n"

def print2D():
    return "print\n"


def finsert(file, a, b):
    return file.write(insert(a, b))


def fdelete(file, a, b):
    return file.write(delete(a, b))


def foverlap(file, a, b):
    return file.write(overlap(a, b))


def fbfs(file):
    return file.write(bfs())


def fdfs(file):
    return file.write(dfs())


def fsalir(file):
    return file.write(salir())


def fhelp(file):
    return file.write(help())


def fprint2D(file):
    return file.write(print2D())


def test_size(file):
    max_number = 100000
    for x in range(0, max_number):
        finsert(file, x, x+1)
    foverlap(file, max_number + 2, max_number + 3)
    fbfs(file)
    fsalir(file)


def test_delete(file):
    max_number = 10000
    for x in range(0, max_number):
        finsert(file, x, x+1)
    for x in range(0, max_number):
        fdelete(file, x, x+1)
    fbfs(file)
    fsalir(file)


def test_insert(file):
    max_number = 10000
    for x in range(0, max_number):
        finsert(file, x, x+1)
    fprint2D(file)
    fbfs(file)
    fdfs(file)
    fsalir(file)


def test_overlap(file):
    max_number = 100
    for x in range(0, max_number):
        finsert(file, x, x+1)
    for x in range(0, max_number):
        foverlap(file, x, x+1)
    fbfs(file)
    fsalir(file)


def test_dummy(file):
    finsert(file, 1, 2)
    finsert(file, 2, 3)
    finsert(file, 0, 1)
    finsert(file, 3, 4)
    finsert(file, 4, 5)
    fprint2D(file)
    fsalir(file)


def test_negative(file):
    max_number = 100
    for x in range(0, max_number):
        finsert(file, -1*x, -1*(x) + 1)
    fprint2D(file)
    fbfs(file)
    fdfs(file)
    fsalir(file)

def test_real_number(file):
    max_number = 10000
    number = -100
    for x in range(0, max_number):
        finsert(file, number, number+0.1)
        number += 0.1
    fprint2D(file)
    fbfs(file)
    fdfs(file)
    fsalir(file)

def test_random_valid_numbers(file):
    max_number = 10000
    for x in range(0, max_number):
        number = random.uniform(-100000, 100000)
        finsert(file, number, number + random.uniform(0, 100000))
    fprint2D(file)
    fbfs(file)
    fdfs(file)
    fsalir(file)

def test_random_numbers(file):
    max_number = 10000
    for x in range(0, max_number):
        finsert(file, random.uniform(-100000, 100000), random.uniform(-100000, 100000))
    fprint2D(file)
    fbfs(file)
    fdfs(file)
    fsalir(file)

def test_valgrind(file):
    max_number = 10000
    max_number_overlap = 1000
    interval_to_delete = []
    interval_to_overlap = []
    for x in range(0, max_number):
        x = random.uniform(-100000, 100000)
        y = random.uniform(-100000, 100000)
        finsert(file, x, y)
        if x <= y and random.random() < 0.1:
            interval_to_delete.append((x,y))
        if x <= y and random.random() < 0.5:
            interval_to_overlap.append((x,y))
    
    for interval in interval_to_delete:
        fdelete(file, interval[0], interval[1])
    for interval in interval_to_overlap:
        foverlap(file, interval[0], interval[1])
    for x in range(0, max_number_overlap):
        foverlap(file, random.uniform(-100000, 100000), random.uniform(-100000, 100000))
    
    fprint2D(file)
    fbfs(file)
    fdfs(file)
    fsalir(file)

def open_safe(filename, mode, encoding):
    if not os.path.exists(os.path.dirname(filename)):
        try:
            os.makedirs(os.path.dirname(filename))
        except OSError as exc:
            if exc.errno != errno.EEXIST:
                raise
    return open(filename, mode=mode, encoding=encoding)


def test_template(test_func, valgrind, fInfo, OS):
    test_shell = "./test_shell"
    PATH_TEST = TEST_IN_PATH + test_func.__name__ + ".txt"
    PATH_OUT = TEST_OUT_PATH + test_func.__name__ + ".txt"
    if OS == "WIN32":
        test_shell += ".exe"
    if valgrind:
        exec_list = ['valgrind', '-v', '--leak-check=full', '--show-reachable=yes', test_shell, PATH_TEST]
    else:
        exec_list = [test_shell, PATH_TEST]
    start_message = "# Start test: %s" % test_func.__name__
    print(start_message)
    fInfo.write(start_message + "\n")
    
    fTest = open_safe(PATH_TEST, mode="w+", encoding="utf-8")
    test_func(fTest)
    fTest.close()

    start = time.time()
    response = check_output(exec_list)
    end = time.time()

    fOut = open_safe(PATH_OUT, mode="w+", encoding="utf-8")
    execution_time = "*** Execution time: %s seg.***\n\n" % (end - start)
    fOut.write(execution_time)
    end_message = "# End test: %s\n%s" % (test_func.__name__, execution_time)
    print(end_message)
    fInfo.write(end_message + "\n")
    fOut.write(response.decode())
    fOut.close()


def main():
    test_list = [
        (test_dummy, False),
        (test_insert, False),
        (test_delete, False),
        (test_overlap, False),
        (test_negative, False),
        (test_real_number, False),
        (test_random_numbers, False),
        (test_random_valid_numbers, False),
        (test_valgrind, True),
        (test_size, False),
    ]
    OS = sys.argv[1]
    repeat = int(sys.argv[2])
    fInfo = open_safe(TEST_OUT_INFO_PATH, mode="w+", encoding="utf-8")
    for i in range(0, repeat):
        for test in test_list:
            test_template(test[0], test[1], fInfo, OS)
    fInfo.close()


if __name__ == "__main__":
    main()
