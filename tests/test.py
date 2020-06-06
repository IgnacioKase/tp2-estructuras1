from subprocess import check_output
import sys
import time
import os
import errno


def test_size(file):
    max_number = 1000
    for x in range(0, max_number):
        file.write("i [%s,%s]\n" % (x, x+1))
    file.write("? [%s,%s]\n" % (max_number + 2, max_number + 3))
    file.write("bfs\n")
    file.write("salir\n")


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
        ("test_cases/test.txt", "test_cases/out_test.txt", test_size)
    ]

    for test in test_list:
        test_template(test[0], test[1], test[2])


if __name__ == "__main__":
    main()
