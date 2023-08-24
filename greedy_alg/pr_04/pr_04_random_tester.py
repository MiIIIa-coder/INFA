from random import randint

for num_test in range(4):
    test_file = open('pr_4_test' + str(num_test) + '.txt', 'w')

    L = randint(0, 40)
    test_file.write(str(L))
    test_file.write('\n')

    R = randint(0, 40)
    while R <= L:
        R = randint(0, 40)
    test_file.write(str(R))
    test_file.write('\n')

    nintervs = randint(1, 20)
    test_file.write(str(nintervs) + " ")
    test_file.write('\n')

    for number in range(1, nintervs+1):
        test_file.write(str(number) + " ")

        start = randint(0, 40)
        test_file.write(str(start) + " ")

        fin = randint(1, 50)
        while  fin <= start:
            fin = randint(1, 50)
        test_file.write(str(fin) + " ")

        test_file.write('\n')


