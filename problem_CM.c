#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

void swap_sizes(int *sizes, int first, int second)
{
    int swap_elt;

    swap_elt = sizes[first];
    sizes[first] = sizes[second];
    sizes[second] = swap_elt;

}

int cmp(void *lhs, int lsz, void *rhs, int rsz)
{
    const int *lhsi = (const int *) lhs;
    const int *rhsi = (const int *) rhs;

    if (*lhsi < *rhsi)
        return 1;
    else
        return 0;
}

typedef int (*xcmp_t)(void *lhs, int lsz, void *rhs, int rsz);

void my_merge(void *mem, int *sizes, int l, int m, int r, xcmp_t cmp)
{

    int i;
    int ptr_sizes;
    int j;
    int memory = 0;
    int place;
    int index;

    int first_byte = 0;         //<=> i
    int first_byte_saved;
    int middle_byte = 0;        //<=> j
    int counter_byte;
    int byte_ptr = 0;           //<=> in mem_new

    char *mem_new;
    ptr_sizes = l;
    j = m + 1;
    i = l;

    for (index = l; index <= r; ++index)
        memory += sizes[index];

    mem_new = calloc(memory, sizeof(char));
    //printf("%d %d\n", memory, l);

    for (counter_byte = 0; counter_byte < l; ++counter_byte)
        first_byte += sizes[counter_byte];
    first_byte_saved = first_byte;

    middle_byte = first_byte;
    for (counter_byte = l; counter_byte <= m; ++counter_byte)
        middle_byte += sizes[counter_byte];

    for (; i <= m; i++) {
        //while (mem[j] <= mem[i] && j <= r)
        while (cmp((mem + middle_byte), sizes[j], (mem + first_byte), sizes[i]) && j <= r) {    //here comparer
            for (place = 0; place < sizes[j]; byte_ptr++, place++)
                *(mem_new + byte_ptr) =
                    *((char *) mem + middle_byte + place);
            middle_byte += sizes[j];
            swap_sizes(sizes, ptr_sizes, j);
            ++ptr_sizes;
            ++j;
        }

        //arr_new[k++] = arr[i];
        for (place = 0; place < sizes[i]; byte_ptr++, place++)
            *(mem_new + byte_ptr) = *((char *) mem + first_byte + place);
        first_byte += sizes[i];
        swap_sizes(sizes, ptr_sizes, i);
        ++ptr_sizes;
    }

    while (j <= r) {
        //arr_new[k++] = arr[j++];
        for (place = 0; place < sizes[j]; byte_ptr++, place++)
            *(mem_new + byte_ptr) = *((char *) mem + middle_byte + place);
        middle_byte += sizes[j];
        swap_sizes(sizes, ptr_sizes, j);
        ++ptr_sizes;
        ++j;
    }

    for (i = 0; i < memory; i++)
        *((char *) mem + first_byte_saved + i) = *(mem_new + i);        //for bytes from first element to last element in this case

    free(mem_new);

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
    int i;
    int nelts = 10;
    int mem[] = { 8, 9, 9, 7, 1, 7, 9, 9, 1, 8 };
    int sizes[] = { 4, 4, 4, 4, 4, 4, 4, 4, 4, 4 };
#if 0
    int *mem;
    int *sizes;

    res = scanf("%d\n", &len);
    assert(res == 1);

    for (i = 0; i < len; ++i) {
        res = scanf("%d ", &mem);
        assert(res == 1);
    }
#endif

    xmsort((void *) mem, sizes, nelts, cmp);

    printf("\n");

    for (i = 0; i < nelts; ++i)
        printf("%d ", mem[i]);

    return 0;
}
