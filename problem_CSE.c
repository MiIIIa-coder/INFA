#include <assert.h>
#include <limits.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct triple {
    int x, y, z;
};

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

int tcmp(void const *key, void const *elt)
{
    struct triple const *lhs = (struct triple const *) key;
    struct triple const *rhs = (struct triple const *) elt;
    if (lhs->x == rhs->x && lhs->y == rhs->y)
        return (lhs->z < rhs->z);
    if (lhs->x == rhs->x)
        return (lhs->y < rhs->y);
    return (lhs->x < rhs->x);
}

typedef int (*cmp_t)(const void *lhs, const void *rhs);

void assignment(void *source, char *target, int idx_begin, int eltsize)
{
    int j1;

    for (j1 = 0; j1 < eltsize; j1++)
        target[j1] = *((char *) (source + eltsize * idx_begin) + j1);

}

int selstep(void *parr, int eltsize, int numelts, int nsorted, cmp_t cmp)
{

    char *i;
    int compare = -1;
    int j, k, p;
    int small_id;
    char *small;
    small = (char *) malloc(eltsize);
    i = (char *) malloc(eltsize);

    for (j = nsorted; j < (numelts - 1); j+= 1/*(прибавлять eltsize, а множители убрать лишние)*/) {

        assignment(parr, small, j, eltsize);
        small_id = j;

        assignment(parr, i, j + 1, eltsize);

        for (k = j + 1; k < numelts; k+= 1, assignment(parr, i, k, eltsize)) {
            compare = cmp((void const *) i, (void const *) small);
            if (compare == 1) {
                for (p = 0; p < eltsize; p++)
                    small[p] = *((char *) i + p);
                small_id = k;
            }
        }

        my_swap((void *) small, (parr + eltsize * (j)),        eltsize);
        my_swap((void *) small, (parr + eltsize * (small_id)), eltsize);

    }

    return 0;

}

int main()
{
    int i, res, n, last;
    struct triple *parr;

    res = scanf("%d", &n);
    assert(res == 1);
    assert(n > 2);

    parr = (struct triple *) calloc(n / 3, sizeof(struct triple));

    for (i = 0; i < n / 3; ++i) {
        res = scanf("%d %d %d", &parr[i].x, &parr[i].y, &parr[i].z);
        assert(res == 3);
    }

    res = scanf("%d", &last);
    assert(res == 1);
    assert(last < n);

    selstep(parr, sizeof(struct triple), n / 3, last / 3, &tcmp);

    for (i = 0; i < n / 3; ++i)
        printf("%d %d %d\n", parr[i].x, parr[i].y, parr[i].z);

    free(parr);
    return 0;
}
