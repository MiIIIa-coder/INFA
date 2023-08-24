#include <stdio.h>
#include <stdlib.h>

struct intvl_t {
    int number;
    int start;
    int fin;
};


int input_func(struct intvl_t **intervs)
{

    int nintervs = 0;
    int index = 0;

    scanf("%d", &nintervs);

    *intervs = (struct intvl_t *)calloc(nintervs, sizeof(struct intvl_t));

    for (index = 0; index < nintervs; ++index) {
        scanf("%d", &((*intervs + index)->number));
        scanf("%d", &((*intervs + index)->start));
        scanf("%d", &((*intervs + index)->fin));
    }

    return nintervs;

}

int partition(struct intvl_t **intervs, int start, int end)
{

    int index = 0;
    int pivot = 0;
    int piv_index = 0;

    struct intvl_t tmp;

    pivot = (*intervs + end)->start;
    piv_index = start;

    for (index = start; index < end; ++index)
        if ((*intervs + index)->start <= pivot) {
            //swap(*(*intervs + index), *(*intervs + piv_index));
            tmp = *(*intervs + index);
            *(*intervs + index) = *(*intervs + piv_index);
            *(*intervs + piv_index) = tmp;
            piv_index++;
        }
    //swap(*(*intervs + piv_index), *(*intervs + end));
    tmp = *(*intervs + piv_index);
    *(*intervs + piv_index) = *(*intervs + end);
    *(*intervs + end) = tmp;

    return piv_index;

}

void sort_intervs(struct intvl_t **intervs, int start, int end)
{
    int pivot = 0;

    if (start >= end)
        return;

    pivot = partition(intervs, start, end);

    //less pivot
    sort_intervs(intervs, start, pivot - 1);

    //more pivot
    sort_intervs(intervs, pivot + 1, end);

}

int covermin(int L, int R, struct intvl_t *intervs, int nintervs) {

    int count = 0;
    int index = 0;
    int left_min  = 0;
    int right_max = 0;

    sort_intervs(&intervs, 0, nintervs - 1);

    left_min = L;
    right_max = -1;
    for (index = 0; index < nintervs; index++) {
        if ((intervs + index)->start <= left_min && (intervs + index)->fin > right_max) {
            right_max = (intervs + index)->fin;
        } else if((intervs + index)->start > left_min) {
            ++count;
            printf("%d ", right_max);
            left_min = right_max;
            if ((intervs + index)->start <= left_min && (intervs + index)->fin > right_max) {
                right_max = (intervs + index)->fin;
            }
        }

        if (right_max >= R) {
            ++count;
            printf("%d ", right_max);
            break;
        }
    }

    printf("\n");

    return count;

}

int main()
{
    int L = 0;
    int R = 0;
    int nintervs = 0;

    struct intvl_t *intervs = NULL;

    scanf("%d", &L);
    scanf("%d", &R);

    nintervs = input_func(&intervs);

    printf("answer: %d \n", covermin(L, R, intervs, nintervs));

    return 0;
}


