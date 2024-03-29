#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>

#define show 0

struct data_pivot {
    double val;
    int col;
    int row;
};

void eliminate(double *M, int N, int current, double val)
{
    int i = 0;
    int j = 0;
    double frac = 0;

    for (i = current + 1; i < N; ++i) {
        frac = M[i * N + current] / M[current * N + current];
        for (j = current; j < N; ++j) {
            M[i * N + j] -= (frac * M[current * N + j]);
        }
    }
}

void swap_rows(double *M, int N, int current, int row)
{
    int i = 0;
    double tmp = 0;

    for (i = current; i < N; ++i) {
        tmp = M[N * current + i];
        M[N * current + i] = M[N * row + i];
        M[N * row + i] = tmp;
    }

}

void swap_columns(double *M, int N, int current, int col)
{
    int i = 0;
    double tmp = 0;

    for (i = current; i < N; ++i) {
        tmp = M[N * i + current];
        M[N * i + current] = M[N * i + col];
        M[N * i + col] = tmp;
    }

}

struct data_pivot max_submatrix_element(double *M, int N, int current)	//N - size_matrix
{
    int i = 0;
    int j = 0;

    struct data_pivot curr_pivot;

    if (M[N * current + current] > 0)
        curr_pivot.val = M[N * current + current];
    else
        curr_pivot.val = -M[N * current + current];
    curr_pivot.col = current;
    curr_pivot.row = current;

    for (i = current; i < N; ++i) {
        for (j = current; j < N; ++j) {
            if (*(M + i * N + j) > curr_pivot.val && *(M + i * N + j) >= 0) {
                curr_pivot.val = *(M + i * N + j);
                curr_pivot.col = j;
                curr_pivot.row = i;
            } else if (-*(M + i * N + j) > curr_pivot.val
                   && *(M + i * N + j) < 0) {
                curr_pivot.val = -*(M + i * N + j);
                curr_pivot.col = j;
                curr_pivot.row = i;
            }
        }
    }

    return curr_pivot;

}

void read_matrix(int N, double *M)
{
    int i = 0;
    int j = 0;

    for (i = 0; i < N; ++i) {
        for (j = 0; j < N; ++j) {
            scanf("%lf", ((M + i * N) + j));	//M[i][j]
        }
    }

}

void pr_matrix(int N, double *M)
{
    int i = 0;
    int j = 0;

    for (i = 0; i < N; ++i) {
        for (j = 0; j < N; ++j) {
            printf("%f ", *(M + i * N + j));	//M[i][j]
        }
        printf("\n");
    }
}

int main()
{
    int current = 0;
    int N = 0;
    double det = 1;
    double *M;

    struct data_pivot pivot;

    scanf("%d", &N);
    M = (double *) calloc(N * N, sizeof(double));

    read_matrix(N, M);
#if show
    pr_matrix(N, M);
    printf("\n");
#endif

    for (current = 0; current < N - 1; ++current) {
        pivot = max_submatrix_element(M, N, current);
        #if show
        printf("%f %d %d\n", pivot.val, pivot.col + 1, pivot.row + 1);
        printf("\n");
        #endif

        if (pivot.col != current) {
            swap_columns(M, N, current, pivot.col);
            #if show
            pr_matrix(N, M);
            printf("\n");
            #endif
            det *= -1;
        }

        if (pivot.row != current) {
            swap_rows(M, N, current, pivot.row);
            #if show
            pr_matrix(N, M);
            printf("\n");
            #endif
            det *= -1;
        }

        if (M[current * N + current] == 0.0) {
            det = 0;
            break;
        } else {
            eliminate(M, N, current, pivot.val);
            #if show
            pr_matrix(N, M);
            printf("\n");
            #endif
            det *= M[current * N + current];
        }
    }

    det *= M[(N - 1) * N + (N - 1)];
    printf("%f \n", det);


    return 0;
}
