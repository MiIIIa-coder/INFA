#include <assert.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

#define ent 1

#if 1
void strrev(char *beginn, char *endd)
{

    int i = 0;
    char swapp;
    int len_str = endd - beginn;

    for (i = 0; (i < len_str / 2); ++i) {
        swapp = *(beginn + i);
        *(beginn + i) = *(endd - i - 1);
        *(endd - i - 1) = swapp;
    }

}
#endif

int main()
{
#if ent
    int i = 0;
    int res = -1;
    int len_str = 0, len_text = 0;
    char unused;

    char *word, *text, *pos;


    res = scanf("%d\n", &len_str);
    assert(res == 1);

    unused = ' ';
    while (isspace(unused))
        scanf("%c", &unused);

    word = calloc(len_str + 1, sizeof(char));
    assert(word != NULL);

    word[0] = unused;

    for (i = 1; i < len_str; ++i)
        scanf("%c", word + i);
    word[len_str] = '\0';

    res = scanf("%d\n", &len_text);
    assert(res == 1);

    unused = ' ';
    while (isspace(unused))
        scanf("%c", &unused);

    text = calloc(len_text + 1, sizeof(char));
    assert(text != NULL);

    text[0] = unused;

    for (i = 1; i < len_text; ++i)
        scanf("%c", text + i);
    text[len_text] = '\0';

    pos = strstr(text, word);

    for (; ; )
        if (pos != NULL) {
            strrev(pos, pos + len_str);
            pos = strstr(pos + len_str, word);
        } else
            break;
#endif

#if 1 - ent
    int i = 0;
    int len_text = 19;
    int len_str = 2;

    char hello[20] = "Hello, world!";

    //while (strstr(hello, "lo") != NULL)
    char *pos;
    pos = strstr(hello, "world");

    for (; ; )
        if (pos != NULL) {
            strrev(pos, pos + len_str, hello);
            pos = strstr(pos + len_str, "world");
        } else
            break;

    //printf("%ld\n", strstr(hello, "ol") - hello);


#endif

    for (i = 0; i < len_text; ++i)
        printf("%c", text[i]);

    return 0;

}
