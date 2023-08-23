#include <stdio.h>
#include <stdlib.h>

unsigned count_del_of_four(unsigned exponent) {

    unsigned del = 1;

    if (exponent == 0)
        return del;
    else if (exponent > 0) {
        while (exponent != 0) {
            del *= 4;
            exponent -= 1;
        }
        return del;
    } else return 0u;

}

unsigned powers_of_four(unsigned n, unsigned m) {

    unsigned count = 0;
    unsigned del = 0;

    if (n == 0)
        return 0u;

    while (m >= 0) {
        del = count_del_of_four(m);
        if (del == 0) {
            fprintf(stderr, "ERROR_LINE %d\n", __LINE__);
            abort();
        }

        count += n/del;
        n %= del;

        if (m == 0)
            break;
        m -= 1;
    }

    return count;

}

int main()
{
    unsigned m = 0;
    unsigned n = 0;

    scanf("%u \n", &m);
    scanf("%u \n", &n);

    printf("answer: %u \n", powers_of_four(n,m));

    return 0;

}
