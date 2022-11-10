#include <stdio.h>
#include <stdlib.h>
struct sieve_t {
    int n;
    char *mod1;
    char *mod5;
};

struct sieve_t init_sieve(int n)
{
    char *mod1 = calloc(n, sizeof(char));
    char *mod5 = calloc(n, sizeof(char));
    struct sieve_t sv = { n, mod1, mod5 };
    return sv;
}

void fill_sieve(struct sieve_t *sv)
{
    unsigned long long n = 0;
    unsigned long long k = 0;
    unsigned long long number = 0;

    for (n = 1; n < (unsigned long long) sv->n; ++n) {
        for (k = 0; k < (unsigned long long) sv->n; ++k) {
            number = (6 * n + 1) * (6 * k + 5);
            if ((number / 48) >= (unsigned long long) sv->n)
                break;
            else
                sv->mod5[number / 48] |= ((unsigned char) 1 << (((number - 5) / 6) % 8));

            number = (6 * (n - 1) + 5) * (6 * k + 5);
            if ((number / 48) >= (unsigned long long) sv->n)
                break;
            else
                sv->mod1[number / 48] |= ((unsigned char) 1 << (((number - 1) / 6) % 8));
        }

        for (k = 1; k < (unsigned long long) sv->n; ++k) {
            number = (6 * n + 1) * (6 * k + 1);
            if ((number / 48) <= (unsigned long long) sv->n)
                sv->mod1[number / 48] |= ((unsigned char) 1 << (((number - 1) / 6) % 8));
            else
                break;
        }
    }

}

int is_prime(struct sieve_t *sv, unsigned n)
{
    unsigned k = 0;
    if (n % 6 == 1) {
        k = (n - 1) / 6;
        return 1 - ((sv->mod1[k / 8]) >> (k % 8) & (unsigned char) 1);
    }
    if (n % 6 == 5) {
        k = (n - 5) / 6;
        return 1 - ((sv->mod5[k / 8]) >> (k % 8) & (unsigned char) 1);
    }
    if (n == 2 || n == 3) {
        return 1;
    }

    else
        return 0;
}


void free_sieve(struct sieve_t *sv)
{
    free(sv->mod1);
    free(sv->mod5);
    sv->n = 0;
}

int main()
{
    unsigned n = 0;

    scanf("%d", &n);
    struct sieve_t sv = init_sieve(n);
    fill_sieve(&sv);
    printf("%d", is_prime(&sv, n));
    free_sieve(&sv);
    return 0;
}
