#include <stdio.h>
#include <ctype.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>

const unsigned A = 256u;
const unsigned B = 519u;
const unsigned P = 256u;         //Power of hash-table
const unsigned M = 919u;
const unsigned R = 19u;

struct node_t {
    struct node_t *next;
    char *word;
    unsigned count_w;
};

unsigned h__a_b__(unsigned n)
{
    return ((A * n + B) % P);
}

unsigned get_hash(const char *pat, const char *end)
{
    unsigned p = 0;
    unsigned r = 1;

    for (; pat != end; ++pat, r *= R)
        p += ((*pat) * r) % P;
    return h__a_b__(p);
}

char *get_word(const char *beg, const char *end)
{
    unsigned i = 0;
    unsigned len = 0;
    char *word;

    len = (end - beg) + 1;

    word = calloc(len + 1, sizeof(char));

    for (i = 0; i < len; ++i)
        *(word + i) = *(beg + i);

    word[len] = '\0';

    return word;

}

struct node_t *creat_list()
{
    struct node_t *l = malloc(sizeof(struct node_t));
    l->next = NULL;
    l->word = NULL;
    l->count_w = 0u;

    return l;
}

void put_word_in_b(struct node_t *top, const char *text, unsigned start,
                   unsigned len)
{
    unsigned i = 0;
    unsigned j = 0;
    top->word = calloc(len + 1, sizeof(char));

    for (j = 0, i = start; j < len; ++i, ++j) {
        *(top->word + j) = *(text + i);
    }

    *(top->word + j) = '\0';
}

struct node_t *find_last(struct node_t *top)
{
    struct node_t *ptr = NULL;

    for (ptr = top; ptr->next != NULL; ptr = ptr->next) {
    }

    return ptr;
}

void add_to_list(struct node_t *last, const char *text, unsigned start,
                 unsigned len)
{
    struct node_t *tmp;

    if (last == NULL)
        return;

    tmp = (struct node_t *) malloc(sizeof(struct node_t));
    assert(last->next == NULL);

    put_word_in_b(tmp, text, start, len);
    tmp->count_w = 1u;
    tmp->next = NULL;

    if (last->next == NULL)
        last->next = tmp;
}

void create_hash_table(const char *text, unsigned len_text,
                       struct node_t **hash_t)
{
    unsigned i = 0;
    unsigned j = 0;
    unsigned hash = 0;
    unsigned was_found = 0;

    char *word = NULL;

    struct node_t *last = NULL;
    struct node_t *bucket = NULL;

    //in all places of hash-table put pointer of list
    for (i = 0; i < P; ++i) {   //P - is a const
        hash_t[i] = creat_list();
    }

    //in hash-table put finding words with their hashes
    for (i = 0; i < len_text; ) {
        j = i;
        while (!(isspace(*(text + i))) && *(text + i) != '\0') {
            ++i;
        }
        hash = get_hash(text + j, text + i - 1);
        word = get_word(text + j, text + i - 1);

        was_found = 0;
        if (hash_t[hash]->word == NULL) {       //if first in bucket
            ++(hash_t[hash]->count_w);
            put_word_in_b(hash_t[hash], text, j, i - j);
            //add_to_list(hash_t[hash], text, j, i-j);
            was_found = 1;
        } else {
            bucket = hash_t[hash];
            while (bucket != NULL) {
                if (strcmp(bucket->word, word) == 0) {
                    ++(bucket->count_w);        //add count of word
                    was_found = 1;
                    break;
                }
                bucket = bucket->next;  //step to next el of list
            }
        }

        if (!(was_found)) {
            last = find_last(hash_t[hash]);
            add_to_list(last, text, j, i - j);
        }

        ++i;                    //miss space
    }

    free(word);

}

unsigned count_f_w(const char *find_word, unsigned len,
                   struct node_t **hash_t)
{
    unsigned hash = 0;

    struct node_t *f_bucket = NULL;

    hash = get_hash(find_word, find_word + len - 1);

    if (hash_t[hash]->word != NULL) {   //if ->word != NULL, then ->next != NULL
        f_bucket = hash_t[hash];
        do {
            if (strcmp(f_bucket->word, find_word) == 0) {
                return f_bucket->count_w;
            } else {
                f_bucket = f_bucket->next;
            }
        } while (f_bucket != NULL);
    }

    return 0u;
}

void delete_hash_t(struct node_t **hash_t)
{
    unsigned i = 0;
    struct node_t *new_top = NULL;

    for (i = 0; i < P; ++i) {
        while (hash_t[i]->next != NULL) {
            new_top = hash_t[i]->next;
            free(hash_t[i]);
            hash_t[i] = new_top;
        }
    }

    free(hash_t);
}

int main()
{
    unsigned i = 0;
    unsigned j = 0;
    int res = 0;
    unsigned c_ans = 0;         //count  of answers
    unsigned len_text = 0;      //length of text
    unsigned len_f_w = 0;       //length of finding words

    struct node_t **hash_t;

    char unused;
    char *text, *f_words, *find_word;

    res = scanf("%d\n", &c_ans);
    assert(res == 1);
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

    res = scanf("%d\n", &len_f_w);
    assert(res == 1);

    unused = ' ';
    while (isspace(unused))
        scanf("%c", &unused);

    f_words = calloc(len_f_w + 1, sizeof(char));
    assert(f_words != NULL);

    f_words[0] = unused;

    for (i = 1; i < len_f_w; ++i)
        scanf("%c", f_words + i);
    f_words[len_f_w] = '\0';

    ///////////////////

    hash_t = calloc(P, sizeof(struct node_t *));
    create_hash_table(text, len_text, hash_t);

    for (i = 0; i < len_f_w; ) {
        j = i;
        while (!(isspace(*(f_words + i))) && *(f_words + i) != '\0') {
            ++i;
        }

        find_word = calloc(i-j + 1, sizeof(char));
        find_word = get_word(f_words + j, f_words + i - 1);
        printf("%u ", count_f_w(find_word, i - j, hash_t));

        ++i;                    //miss space
        free(find_word);
    }

    free(text);
    free(f_words);

    delete_hash_t(hash_t);
}
