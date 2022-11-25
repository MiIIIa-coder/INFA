#include <stdio.h>
#include <stdlib.h>

typedef int (*cmp_t)(void const *lhs, void const *rhs);

void my_swap(void *a, void *b, size_t eltsize)
{

    char sw;
    size_t i;

    for (i = 0; i < eltsize; i++) {
        sw = *((char *) b + i);
        *((char *) b + i) = *((char *) a + i);
        *((char *) a + i) = sw;
    }

}

int cmp(void const *lhs, void const *rhs)
{
    int const *lhsi = (int const *) lhs;
    int const *rhsi = (int const *) rhs;

    if (*lhsi < *rhsi)
        return 1;
    else
        return 0;
}

int selstep(void *parr, int eltsize, int numelts, int nsorted, cmp_t cmp)
{

    char const *i;
    int compare = -1;
    int j, k, p, j1;
    int small_id;
    char *small;
    small = (char *) malloc(eltsize);

    for (j = nsorted; j < (numelts - 1); j++) {

        for (j1 = 0; j1 < eltsize; j1++)
            small[j1] = *((char *) (parr + eltsize * j) + j1);
        small_id = j;

        for (i = (char const *) parr + (j + 1) * eltsize, k = j + 1;
             k < (numelts); i += eltsize, k++) {
            compare = cmp((void const *) i, (void const *) small);
            if (compare == 1) {
                for (p = 0; p < eltsize; p++)
                    small[p] = *((char *) i + p);
                small_id = k;
            }
        }

        my_swap((void *) small, (parr + eltsize * (j)), sizeof(int));
        my_swap((void *) small, (parr + eltsize * (small_id)), sizeof(int));

    }

    return 0;

}

int main()
{
    int i;
    int numelts = 11;
    int eltsize = sizeof(int);
    int nsorted = 0;

    //int parr[9] = { 2, 3, 4, 7, 5, 16, 9, 4, 5 };

    int parr[11] = {9, 7, 8, 9, 4, 5, 6, 1, 2, 3, 0 };

    if (selstep(parr, eltsize, numelts, nsorted, cmp) == 0)
        printf("VSO\n");

    for (i = 0; i < numelts; ++i)
        printf("%d ", parr[i]);


    return 0;
}
