#include <stdio.h>
#include <stdlib.h>

struct denom_array_t {
    unsigned *arr;
    unsigned sz;
};

unsigned gcd_func(unsigned num1, unsigned num2) {

    if (num1 == 0 || num2 == 0)
        return 0u;

    while (num1*num2 != 0) {
        if (num1 > num2)
            num1 %= num2;
        else
            num2 %= num1;
    }

    return num1 + num2;

}

unsigned lcm_func(unsigned num1, unsigned num2) {

    return (num1*num2/gcd_func(num1, num2));
}

struct denom_array_t egyptian_fractions(unsigned num, unsigned den) {

    struct denom_array_t struct_ans;

    unsigned index_den = 0;
    unsigned index = 0;  //for array of den
    unsigned lcm = 0;
    unsigned gcd = 0;


    struct_ans.sz  = 10u;
    struct_ans.arr = (unsigned *)calloc(struct_ans.sz, sizeof(unsigned));

    for (index_den = 2, index = 0; num != 0; ++index_den) {

        if (index_den * num >= den) {
            lcm = lcm_func(index_den, den);
            num = num*(lcm/den) - (lcm/index_den);   //new num
            den = lcm;                               //new den

            //shorten the fraction
            if (num != 0) {
                gcd = gcd_func(lcm, num);
                num /= gcd;
                den /= gcd;
            }

            //write new den in array
            if (index > struct_ans.sz) {
                struct_ans.sz += 100;
                struct_ans.arr = (unsigned *)realloc(struct_ans.arr, struct_ans.sz*sizeof(unsigned));
            }
            struct_ans.arr[index++] = index_den;
        }

    }

    struct_ans.sz = index;

    return struct_ans;

}


int main ()
{
    int index = 0;

    struct denom_array_t ans;

    //printf("%u \n", gcd_func(439u, 468u));
    //printf("%u \n", lcm_func(252u, 105u));

    ans = egyptian_fractions(1023u, 1024u);

    printf("%u \n", ans.sz);
    printf("\n");

    for (index = 0; index < ans.sz; ++index)
        printf("%u \n", ans.arr[index]);

    return 0;
}
