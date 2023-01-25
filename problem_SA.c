#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include <ctype.h>

char *input(char *src, int *len_src)
{

    int res = 0;
    int i = 0;
    char unused;

    printf("Enter new word's length\n");
    res = scanf("%d\n", len_src);
    assert(res == 1);

    unused = ' ';
    while (isspace(unused))
        scanf("%c", &unused);

    src = calloc(*len_src + 1, sizeof(char));
    assert(src != NULL);

    src[0] = unused;
    for (i = 1; i < *len_src; ++i)
        scanf("%c", src + i);
    src[i] = '\0';

    return src;
}

char *strcat_r(char *dest, const char *src, int *bufsz)
{

    int plus_step = 0;
    int len_dest = strlen(dest);
    int len_src = strlen(src);

    if ((*bufsz - (len_dest + len_src) - 1) >= 0) {
        for (plus_step = 0; plus_step < (len_src); ++plus_step)
            *(dest + len_dest + plus_step) = *(src + plus_step);
        *(dest + len_dest + plus_step) = '\0';

        return dest;
    } else {
        dest = (char *) realloc(dest, len_dest + len_src + 1);
        for (plus_step = 0; plus_step < (len_src); ++plus_step)
            *(dest + len_dest + plus_step) = *(src + plus_step);
        *(dest + len_dest + plus_step) = '\0';
        return dest;
    }
}

int main()
{
    int len_dest = 0;
    int len_src = 0;
    int number = 0;
    int bufsz = 0;
    int res = 0;
    int i = 0;

    char *dest, *src;
    char unused;

    res = scanf("%d\n", &number);
    assert(number >= 1);
    assert(res == 1);

    res = scanf("%d\n", &bufsz);
    assert(res == 1);
    res = scanf("%d\n", &len_dest);
    assert(res == 1);

    if (bufsz < len_dest) {
        printf("ERROR: buffer smaller array's length!");
        return 1;
    }

    unused = ' ';
    while (isspace(unused))
        scanf("%c", &unused);

    dest = calloc(bufsz + 1, sizeof(char));
    assert(dest != NULL);

    dest[0] = unused;
    for (i = 1; i < len_dest; ++i)
        scanf("%c", dest + i);
    dest[i] = '\0';

    for (i = 1; number - i > 0; ++i) {
        src = input(src, &len_src);
        dest = strcat_r(dest, src, &bufsz);
        len_dest += len_src;
    }

    printf("\n");

    for (i = 0; i <= len_dest; ++i)
        printf("%c", dest[i]);

    return 0;

}
