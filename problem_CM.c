#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#define structura 0

#if structura
struct triple {
    int x, y, z;
};
#endif

/*
void swap_sizes(int *sizes, int first, int second)
{
    int swap_elt;

    swap_elt = sizes[first];
    sizes[first] = sizes[second];
    sizes[second] = swap_elt;

}
*/


int cmp(void *lhs, int lsz, void *rhs, int rsz)
{
    int i = 0;
    const int *lhsi = (const int *) lhs;
    const int *rhsi = (const int *) rhs;

/*
    if (*lhsi < *rhsi)
        return 1;
    else
        return 0;
*/

    for (i = 0; i < 4; ++i)
        if (*((char *) lhsi + i) < *((char *) rhsi + i))
            return 1;

    return 0;
}

#if structura
int cmp(void *lhs, int lsz, void *rhs, int rsz)
{
    struct triple const *lstr = (struct triple const *) lhs;
    struct triple const *rstr = (struct triple const *) rhs;

    if (lstr->x == rstr->x && lstr->y == rstr->y)
        return (lstr->z < rstr->z);
    if (lstr->x == rstr->x)
        return (lstr->y < rstr->y);
    return (lstr->x < rstr->x);
}

*
#endif

typedef int (*xcmp_t)(void *lhs, int lsz, void *rhs, int rsz);

int count_number_byte(int *sizes, int start_byte, int end_byte, int byte)
{
    int index = 0;

    for (index = start_byte; index < end_byte; ++index)
        byte += sizes[index];

    return byte;
}

void my_merge(void *mem, int *sizes, int l, int m, int r, xcmp_t cmp)
{

    int i = 0;
    int ptr_sizes = 0;
    int j = 0;
    int memory = 0;
    int place = 0;
    int index = 0;

    int first_byte = 0;         //<=> i
    int first_byte_saved;
    int middle_byte = 0;        //<=> j
    int byte_ptr = 0;           //<=> in mem_new

    int *sizes_new;
    char *mem_new;
    ptr_sizes = 0;              //index for sizes_new
    j = m + 1;
    i = l;

    for (index = l; index <= r; ++index)
        memory += sizes[index];

    sizes_new = calloc(r - l + 1, sizeof(int));
    mem_new = calloc(memory, sizeof(char));

    first_byte = count_number_byte(sizes, 0, l, 0);
    first_byte_saved = first_byte;

    middle_byte = count_number_byte(sizes, l, m + 1, first_byte);

    for (; i <= m; i++) {
        //while (mem[j] <= mem[i] && j <= r)
        while (cmp((mem + middle_byte), sizes[j], (mem + first_byte), sizes[i]) && j <= r) {    //here comparer
            for (place = 0; place < sizes[j]; byte_ptr++, place++)
                *(mem_new + byte_ptr) =
                    *((char *) mem + middle_byte + place);
            middle_byte += sizes[j];
            sizes_new[ptr_sizes] = sizes[j];
            ++ptr_sizes;
            ++j;
        }

        //arr_new[k++] = arr[i];
        for (place = 0; place < sizes[i]; byte_ptr++, place++)
            *(mem_new + byte_ptr) = *((char *) mem + first_byte + place);
        first_byte += sizes[i];
        sizes_new[ptr_sizes] = sizes[i];
        ++ptr_sizes;
    }

    while (j <= r) {
        //arr_new[k++] = arr[j++];
        for (place = 0; place < sizes[j]; byte_ptr++, place++)
            *(mem_new + byte_ptr) = *((char *) mem + middle_byte + place);
        middle_byte += sizes[j];
        sizes_new[ptr_sizes] = sizes[j];
        ++ptr_sizes;
        ++j;
    }

    for (i = 0; i < memory; i++)
        *((char *) mem + first_byte_saved + i) = *(mem_new + i);        //for bytes from first element to last element in this case

    for (i = l, j = 0; i <= r; i++, j++)
        sizes[i] = sizes_new[j];

    free(mem_new);
    free(sizes_new);

}

void merge_sort_imp(void *mem, int *sizes, int l, int r, xcmp_t cmp)
{
    int m;

    if (l >= r)
        return;
    m = (r + l) / 2;

    merge_sort_imp(mem, sizes, l, m, cmp);
    merge_sort_imp(mem, sizes, m + 1, r, cmp);
    my_merge(mem, sizes, l, m, r, cmp);

}

void xmsort(void *mem, int *sizes, int nelts, xcmp_t cmp)
{
    merge_sort_imp(mem, sizes, 0, nelts - 1, cmp);
}

int main()
{
    int i = 0;
    int nelts = 5;
    //int res = 0;
    int mem[] = { 8, 1, 5, 6, 4, 7, 9, 9, 9, 1, 9, 9, 9 };
    int sizes[] = { 8, 12, 4, 12, 16 };

#if structura
    struct triple *mem;
    int *sizes;
    int nelts;

    res = scanf("%d\n", &nelts);
    assert(res == 1);

    mem = calloc(nelts, sizeof(struct triple));
    sizes = calloc(nelts, sizeof(int));

    for (i = 0; i < nelts; ++i) {
        res = scanf("%d %d %d", &mem[i].x, &mem[i].y, &mem[i].z);
        assert(res == 3);
        sizes[i] = sizeof(mem[i]);
    }

    xmsort((void *) mem, sizes, nelts, cmp);

    printf("\n");

    for (i = 0; i < nelts; ++i) {
        printf("%d %d %d", mem[i].x, mem[i].y, mem[i].z);
        printf("\n");
    }
#endif

#if (1 - structura)
    xmsort((void *) mem, sizes, nelts, cmp);

    for (i = 0; i < 13; ++i)
        printf("%d ", mem[i]);

    printf("\n");
    for (i = 0; i < 5; ++i)
        printf("%d ", sizes[i]);
    printf("\n");

    return 0;
#endif

}
