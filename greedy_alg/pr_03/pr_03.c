#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

struct intvl_t {
    int number;
    int start;
    int fin;
};

int input_func(struct intvl_t **reqs) {

    int nreqs = 0;
    int index = 0;

    scanf("%d", &nreqs);

    *reqs = (struct intvl_t *)calloc(nreqs, sizeof(struct intvl_t));

    for (index = 0; index < nreqs; ++index) {
        scanf("%d", &((*reqs + index)->number));
        scanf("%d", &((*reqs + index)->start));
        scanf("%d", &((*reqs + index)->fin));
    }

    return nreqs;

}

int partition(struct intvl_t **reqs, int start, int end) {

    int index = 0;
    int pivot = 0;
    int piv_index = 0;

    struct intvl_t tmp;

    pivot = (*reqs + end)->fin;
    piv_index = start;

    for (index = start; index < end; ++index)
        if ((*reqs + index)->fin <= pivot) {
            //swap(*(*reqs + index), *(*reqs + piv_index));
            tmp = *(*reqs + index);
            *(*reqs + index) = *(*reqs + piv_index);
            *(*reqs + piv_index) = tmp;
            piv_index++;
        }

    //swap(*(*reqs + piv_index), *(*reqs + end));
    tmp = *(*reqs + piv_index);
    *(*reqs + piv_index) = *(*reqs + end);
    *(*reqs + end) = tmp;

    return piv_index;

}

void sort_reqs(struct intvl_t **reqs, int start, int end) {

    if (start >= end)
        return;

    int pivot = partition(reqs, start, end);

    //less pivot
    sort_reqs(reqs, start, pivot - 1);

    //more pivot
    sort_reqs(reqs, pivot + 1, end);

}

int schedulemax (struct intvl_t *reqs, int nreqs) {

    int index = 0;
    int count = 0;
    int last_fin = INT_MIN;

    sort_reqs(&reqs, 0, nreqs - 1);

    for (index = 0; index < nreqs; index++) {
        if ((reqs + index)->start > last_fin) {
            ++count;
            last_fin = (reqs + index)->fin;
            //printf("%d ", (reqs + index)->number);
        }
    }

    return count;

}

int main()
{
    int nreqs = 0;
    struct intvl_t *reqs = NULL;

    nreqs = input_func(&reqs);
    printf("count: %d \n", nreqs);

    for (int i = 0; i < nreqs; ++i) {
        printf("%d ", (reqs + i)->number);
        printf("%d ", (reqs + i)->start);
        printf("%d ", (reqs + i)->fin);
        printf("\n");
    }

    printf("\n");
    printf("answer: %d \n", schedulemax(reqs, nreqs));


    return 0;
}
