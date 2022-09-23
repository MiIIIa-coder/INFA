#include <stdio.h>
#include <stdlib.h>

void greetings(void);

int next_turn(int total, int possible)
{
    int idx = 0;
    int first = 0;
    int second = 1;
    int fib[60] = {0};

    int t = total;

    //заполняем массив fib числами Фибоначчи меньших total
    for(idx = 0; second < total;)
    {
        int tmp = second;
        second = first + second;
        first = tmp;
        if (second <= total)
            fib[++idx] = second;
    }

    //разложим на сумму чисел Фибоначчи и выберем наименьшее возможное или 1

    while(t > 0)
    {
        if (t >= fib[idx])
            t -= fib[idx];

        --idx;
    }

    return (fib[++idx] <= possible) ? fib[idx] : 1;
}

int main()
{
    int total = 0;
    int possible = 0;
    int first_player = 0;
    int count_mathes = 0;
    int count_mathes_comp = 0;

    printf("Enter initial number of matches\n");

    if (scanf("%d", &total) != 1)
    {
        printf("ERROR: invalid data\n");
        return 1;
    }

    possible = total - 1;

    printf("Who begins game\n");
    printf("1 - you\n");
    printf("2 - computer\n");

    if (scanf("%d", &first_player) != 1)
    {
        printf("ERROR: invalid data\n");
        return 1;
    }

    if (first_player == 1)
    {
        printf("Your turn:\n");
        scanf("%d", &count_mathes);

        if (count_mathes >= total)    //if first player took all matches
        {
            printf("ERROR: invalid data\n");
            return 1;
        }

        total -= count_mathes;
        possible = 2*count_mathes;
    }

    while(total > 0)
    {
        count_mathes_comp = next_turn(total, possible);

        total -= count_mathes_comp;
        possible = 2*count_mathes_comp;

        printf("computer took %d\n", count_mathes_comp);

        if (total <= 0)
        {
            printf("Computer wins!\n");
            break;
        }

        printf("there are matches left: %d\n",total);
        printf("you can take less than %d\n", possible+1);

        printf("Your turn:\n");
        scanf("%d", &count_mathes);

        if (count_mathes > possible)
        {
            printf("ERROR: invalid data\n");
            return 1;
        }

        total -= count_mathes;
        possible = 2*count_mathes;

        if (total <= 0)
        {
            printf("You win!\n");
            break;
        }
    }

    return 0;

}
