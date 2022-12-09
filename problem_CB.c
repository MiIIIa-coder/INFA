#include <stdio.h>
#include <stdlib.h>

typedef int (*cmp_t)(void const *lhs, void const *rhs);

int cmp(void const *lhs, void const *rhs)
{
    int const *lhsi = (int const *) lhs;
    int const *rhsi = (int const *) rhs;
    if (*lhsi == *rhsi)
        return 0;
    if (*lhsi < *rhsi)
        return -1;
    else
        return 1;
}

void *cbsearch(void const *key, void const *base, int num, int size, cmp_t cmp)
{
    char const *pivot;
    int result;

    while (num > 0) {
        pivot = (char const *) base + ((num) / 2) * size;
        result = cmp(key, (void const *) pivot);
        if (result == 0)
            return (void *) pivot;

        num = (num) / 2;

        if (result > 0) {        //key bigger
            base = pivot;
        }
    }
    return NULL;
}


int main()
{
    int k;
    int arr[8] = { 1, 2, 3, 15, 15, 26, 37, 111 };

    //int k = 8;

    scanf("%d", &k);

    const int *key = &k;

    if ((int*)cbsearch(key, arr, 8, sizeof(int), cmp) == NULL)
        printf("%d", -1);
    else
        printf("%ld\n", (int*)cbsearch(key, arr, 8, sizeof(int), cmp) - arr);

    return 0;
}
