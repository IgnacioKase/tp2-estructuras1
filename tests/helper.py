test_file = open("test_cases/valen_all_tests_info.txt", mode="r", encoding="utf-8")

line = test_file.readline()

test_list = [
    ("test_dummy", []),
    ("test_insert", []),
    ("test_delete", []),
    ("test_overlap", []),
    ("test_negative", []),
    ("test_real_number", []),
    ("test_random_numbers", []),
    ("test_random_valid_numbers", []),
    ("test_valgrind", []),
    ("test_size", []),
]

while line:
    for test in test_list:
        if line.strip() == "# Start test: %s" % test[0]:
            line = test_file.readline()
            time = test_file.readline().split()[3]
            test[1].append((time))
    line = test_file.readline()

for test in test_list:
    print(test[0])
    for time in test[1]:
        print(time)
    print("\n")
