from random import randint

for num_test in range(4):
    test_file = open('pr_3_test' + str(num_test) + '.txt', 'w')

    nreqs = randint(0, 20)
    test_file.write(str(nreqs) + " ")
    test_file.write('\n')

    for number in range(1, nreqs+1):
        test_file.write(str(number) + " ")

        start = randint(1, 39)
        test_file.write(str(start) + " ")

        fin = randint(2, 40)
        while  fin <= start:
            fin = randint(2, 40)
        test_file.write(str(fin) + " ")

        test_file.write('\n')


