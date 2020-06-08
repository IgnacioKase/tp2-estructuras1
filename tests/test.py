from subprocess import check_output
import sys
import time
import os
import errno


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
    fbfs(file)
    fsalir(file)


def test_overlap(file):
    max_number = 100
    for x in range(0, max_number):
        finsert(file, x, x+1)
    for x in range(0, max_number):
        foverlap(file, x, x+1)
    fbfs(file)
    fsalir(file)


def open_safe(filename, mode, encoding):
    if not os.path.exists(os.path.dirname(filename)):
        try:
            os.makedirs(os.path.dirname(filename))
        except OSError as exc:
            if exc.errno != errno.EEXIST:
                raise
    return open(filename, mode=mode, encoding=encoding)


def test_template(PATH_TEST, PATH_STDOUT, test_func):

    fTest = open_safe(PATH_TEST, mode="w+", encoding="utf-8")

    start = time.perf_counter()
    test_func(fTest)
    end = time.perf_counter()

    fTest.close()
    response = check_output(["../test_shell.exe", PATH_TEST])
    fOut = open_safe(PATH_STDOUT, mode="w+", encoding="utf-8")
    fOut.write("*** Execution time: %s seg.***\n\n" % (end - start))
    fOut.write(response.decode())
    fOut.close()


def main():
    test_list = [
        # ("test_cases/test_insert.txt", "test_cases/out_test_insert.txt", test_insert),
        # ("test_cases/test_delete.txt", "test_cases/out_test_delete.txt", test_delete),
        ("test_cases/test_overlap.txt",
         "test_cases/out_test_overlap.txt", test_overlap),
        # ("test_cases/test_size.txt", "test_cases/out_test_size.txt", test_size),
    ]

    for test in test_list:
        test_template(test[0], test[1], test[2])


if __name__ == "__main__":
    main()
